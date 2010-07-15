/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009 Alex Elliott <alex@alex-elliott.co.uk>
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
 *
 */

#include "settingsdialog.hpp"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), settings()
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    addRegexSettings();
}

void SettingsDialog::addRegexSettings()
{
    regexSettings = new QWidget(tabWidget);
    tabWidget->addTab(regexSettings, tr("Regex Settings"));

    regexLayout = new QGridLayout(regexSettings);
    regexSettings->setLayout(regexLayout);

    defaultLabel = new QLabel(tr("Default Regex Backend: "), regexSettings);
    defaultCombo = new QComboBox(regexSettings);

    defaultCombo->addItem("PCRE");
    defaultCombo->addItem("Qt4");
    defaultCombo->addItem("POSIX ERE");

    QString curType = settings.value("regex/defaultBackend", "pcre").toString();
    if(curType == "qt4")
        defaultCombo->setCurrentIndex(1);
    else if(curType == "posix")
        defaultCombo->setCurrentIndex(2);
    settings.setValue("regex/defaultBackend", curType);

    regexLayout->addWidget(defaultLabel, 0, 0);
    regexLayout->addWidget(defaultCombo, 0, 1);

    caseLabel = new QLabel(tr("Case Sensitive: "), regexSettings);
    caseCheck = new QCheckBox(regexSettings);

    if(settings.value("regex/caseSensitivity", true).toBool() == true)
        caseCheck->setDown(true);
    settings.setValue("regex/caseSensitivity", settings.value("regex/caseSensitivity", true));

    regexLayout->addWidget(caseLabel, 1, 0);
    regexLayout->addWidget(caseCheck, 1, 1);

    buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply
                                   | QDialogButtonBox::Cancel, Qt::Horizontal, regexSettings);

    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

    regexLayout->addWidget(buttons, 2, 0, 1, 2, Qt::AlignRight);
}
