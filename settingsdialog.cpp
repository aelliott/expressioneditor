/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Expression editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Expression editor.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "settingsdialog.hpp"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , _ui(new Ui::SettingsDialog)
    , _accepted(false)
{
    _ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene();
    _ui->exampleExpressionView->setScene(scene);

    readValues();

    _ui->literalSettings->setType("Literal");
    connect(_ui->literalSettings, SIGNAL(valueChanged()), this, SLOT(rehash()));
    _ui->groupingSettings->setType("Grouping");
    connect(_ui->groupingSettings, SIGNAL(valueChanged()), this, SLOT(rehash()));
    _ui->alternationSettings->setType("Alternation");
    connect(_ui->groupingSettings, SIGNAL(valueChanged()), this, SLOT(rehash()));
    _ui->bracketExpressionSettings->setType("BracketExpression");
    connect(_ui->groupingSettings, SIGNAL(valueChanged()), this, SLOT(rehash()));

    visualisationTabChanged(0);

    resetDialog();
}

SettingsDialog::~SettingsDialog()
{
    delete _ui;
}

void SettingsDialog::closeEvent(QCloseEvent *e)
{
    if(!_accepted)
        reject();

    QDialog::closeEvent(e);
}

void SettingsDialog::setValues()
{
    _settings.setValue("Editor/Highlighting",
                       _ui->expressionHighlightingCheckBox->isChecked());
    _settings.setValue("Editor/Autocompletion",
                       _ui->autocompletionCheckBox->isChecked());

    _settings.setValue("Visualisation/HorizontalSpacing",
                       _ui->horizontalSpacingSpinBox->value());
    _settings.setValue("Visualisation/VerticalSpacing",
                       _ui->verticalSpacingSpinBox->value());

    int displayOptions = 0;
    if(_ui->showNamedGroupsCheckBox->isChecked())
        displayOptions |= GroupingGraphicsItem::DisplayNamed;
    if(_ui->showCapturingGroupsCheckBox->isChecked())
        displayOptions |= GroupingGraphicsItem::DisplayCapturing;
    if(_ui->showNoncapturingGroupsCheckBox->isChecked())
        displayOptions |= GroupingGraphicsItem::DisplayNonCapturing;
    _settings.setValue("Visualisation/Grouping/DisplayOptions", displayOptions);
}

void SettingsDialog::readValues()
{
    _expressionHighlighting = _settings.value("Editor/Highlighting", true).toBool();
    _autocompletion = _settings.value("Editor/Autocompletion", false).toBool();

    _horizontalSpacing = _settings.value("Visualisation/HorizontalSpacing", 8).toInt();
    _verticalSpacing = _settings.value("Visualisation/VerticalSpacing", 12).toInt();
    _groupingDisplayOptions = _settings.value(
                "Visualisation/Grouping/DisplayOptions",
                GroupingGraphicsItem::DisplayCapturing
                | GroupingGraphicsItem::DisplayNamed
                ).toInt();
}

void SettingsDialog::handleButtonPress(QAbstractButton *button)
{
    if(button->text() == "Reset")
        resetDialog();
    if(button->text() == "Apply")
        apply();
}

void SettingsDialog::resetDialog()
{
    _ui->expressionHighlightingCheckBox->setChecked(_expressionHighlighting);
    _ui->autocompletionCheckBox->setChecked(_autocompletion);

    _ui->horizontalSpacingSpinBox->setValue(_horizontalSpacing);
    _ui->verticalSpacingSpinBox->setValue(_verticalSpacing);

    _ui->showNamedGroupsCheckBox->setChecked(
                _groupingDisplayOptions & GroupingGraphicsItem::DisplayNamed
                );
    _ui->showCapturingGroupsCheckBox->setChecked(
                _groupingDisplayOptions & GroupingGraphicsItem::DisplayCapturing
                );
    _ui->showNoncapturingGroupsCheckBox->setChecked(
                _groupingDisplayOptions & GroupingGraphicsItem::DisplayNonCapturing
                );
}

void SettingsDialog::apply()
{
    setValues();
    readValues();
}

void SettingsDialog::accept()
{
    _accepted = true;
    apply();
    QDialog::accept();
}

void SettingsDialog::reject()
{
    resetDialog();
    apply();
    QDialog::reject();
}

void SettingsDialog::settingsTabChanged(int page)
{
    switch(page)
    {
    case 1:
        // Visualisation
        _ui->titleLabel->setText(tr("Visualisation Settings"));
        break;
    default:
        // Editor
        _ui->titleLabel->setText(tr("Editor Settings"));
    }
}

void SettingsDialog::visualisationTabChanged(int page)
{
    switch(page)
    {
    case 1:
        // Literal
        _exampleExpression = "foobar";
        break;
    case 2:
        // Grouping
        _exampleExpression = "(foo)(?:bar)";
        break;
    case 3:
        // Alternation
        _exampleExpression = "foo|bar";
        break;
    case 4:
        // Bracket Expression
        _exampleExpression = "[]][0-9\\w-][^bar]";
        break;
    default:
        // General, page 0
        // Grouping, page 2
        _exampleExpression = "^(?:(foobar)|bork)[^]\\wa-z]\\d$";
    }

    rehash();
}

void SettingsDialog::expressionHighlightingChanged(bool highlighting)
{
    _settings.setValue("Editor/Highlighting", highlighting);

    rehash();
}

void SettingsDialog::autocompletionChanged(bool autocomplete)
{
    _settings.setValue("Editor/Autocompletion", autocomplete);

    rehash();
}

void SettingsDialog::horizontalSpacingChanged(int spacing)
{
    _settings.setValue("Visualisation/HorizontalSpacing", spacing);

    rehash();
}

void SettingsDialog::verticalSpacingChanged(int spacing)
{
    _settings.setValue("Visualisation/VerticalSpacing", spacing);

    rehash();
}

void SettingsDialog::showNamedGroupsChanged(bool show)
{
    int options = _settings.value("Visualisation/Grouping/DisplayOptions",
                                  GroupingGraphicsItem::DisplayCapturing
                                  | GroupingGraphicsItem::DisplayNamed
                                  ).toInt();
    if(show)
        options |= GroupingGraphicsItem::DisplayNamed;
    else
        options ^= GroupingGraphicsItem::DisplayNamed;

    _settings.setValue("Visualisation/Grouping/DisplayOptions", options);

    rehash();
}

void SettingsDialog::showCapturingGroupsChanged(bool show)
{
    int options = _settings.value("Visualisation/Grouping/DisplayOptions",
                                  GroupingGraphicsItem::DisplayCapturing
                                  | GroupingGraphicsItem::DisplayNamed
                                  ).toInt();
    if(show)
        options |= GroupingGraphicsItem::DisplayCapturing;
    else
        options ^= GroupingGraphicsItem::DisplayCapturing;

    _settings.setValue("Visualisation/Grouping/DisplayOptions", options);

    rehash();
}

void SettingsDialog::showNoncapturingGroupsChanged(bool show)
{
    int options = _settings.value("Visualisation/Grouping/DisplayOptions",
                                  GroupingGraphicsItem::DisplayCapturing
                                  | GroupingGraphicsItem::DisplayNamed
                                  ).toInt();
    if(show)
        options |= GroupingGraphicsItem::DisplayNonCapturing;
    else
        options ^= GroupingGraphicsItem::DisplayNonCapturing;

    _settings.setValue("Visualisation/Grouping/DisplayOptions", options);

    rehash();
}

void SettingsDialog::rehash()
{
    _ui->exampleExpressionEdit->setText(_exampleExpression);

    QGraphicsScene *scene = _ui->exampleExpressionView->scene();
    scene->clear();
    _exampleVisualisation = new ExpressionGraphicsItem(_exampleExpression, RegexFactory::Qt);
    scene->addItem(_exampleVisualisation);
}
