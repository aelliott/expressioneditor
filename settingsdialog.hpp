/*!
 * \file
 * \author Alex Elliott <alex@alex-elliott.co.uk>
 * \version 0.1pre
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009,2010 Alex Elliott <alex@alex-elliott.co.uk>
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
/*!
 * \brief   The settings dialog for the application, communicates with QSettings
 *          to produce application-wide settings
 */

#ifndef SETTINGSDIALOG_HPP
#define SETTINGSDIALOG_HPP

#include <QSettings>
#include "regexfactory.hpp"
#include "ui_settingsdialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT;

public:
    SettingsDialog(QWidget *parent = 0);

public slots:
    void apply();
    void accept();

private:
    void addRegexSettings();

    Ui::SettingsDialog ui;
    QSettings settings;

};

#endif // SETTINGSDIALOG_HPP
