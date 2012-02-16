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
#ifndef SETTINGSDIALOG_HPP
#define SETTINGSDIALOG_HPP

#include <QDialog>
#include <QAbstractButton>
#include <QSettings>

#include "GraphicsItems/expressiongraphicsitem.hpp"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    void closeEvent(QCloseEvent *e);

    void setValues();
    void readValues();

public slots:
    void handleButtonPress(QAbstractButton *button);
    void resetDialog();
    void apply();
    void accept();
    void reject();

    void settingsTabChanged(int page);
    void visualisationTabChanged(int page);

    void expressionHighlightingChanged(bool highlighting);
    void autocompletionChanged(bool autocomplete);

    void selectVisualisationFont();
    void horizontalSpacingChanged(int spacing);
    void verticalSpacingChanged(int spacing);

    void showNamedGroupsChanged(bool show);
    void showCapturingGroupsChanged(bool show);
    void showNoncapturingGroupsChanged(bool show);

    void rehash();

private:
    QSettings _settings;
    Ui::SettingsDialog *_ui;
    QString _exampleExpression;
    ExpressionGraphicsItem *_exampleVisualisation;
    bool _accepted;

    bool _expressionHighlighting;
    bool _autocompletion;

    int _horizontalSpacing;
    int _verticalSpacing;
    int _groupingDisplayOptions;
    QFont _visualisationFont;
};

#endif // SETTINGSDIALOG_HPP
