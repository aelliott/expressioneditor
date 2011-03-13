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

#include "settingsdialog.hpp"

/*!
 * Create a new settings dialog
 *
 * \param   parent  This widget's parent widget
 */
SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , settings()
{
    ui.setupUi(this);

    // Conditional dialog elements
#ifndef NO_PCRE
    ui.defaultBackendCombo->addItem(tr("PCRE"));
    ui.defaultBackendCombo->setCurrentIndex(1);
    ui.defaultBackendCombo->addItem(tr("Perl-emulation"));
#endif // NO_PCRE
#ifndef NO_ICU
    ui.defaultBackendCombo->addItem(tr("ICU"));
#endif // NO_ICU
#ifndef NO_POSIX
    ui.defaultBackendCombo->addItem(tr("POSIX"));
#endif // NO_POSIX
#ifdef WITH_CPP0X
    ui.defaultBackendCombo->addItem(tr("C++0x"));
#endif // WITH_CPP0X
}

/*!
 * Apply the current settings to our stored settings
 */
void SettingsDialog::apply()
{
}

/*!
 * Apply the current settings and then exit the current dialog
 */
void SettingsDialog::accept()
{
    apply();

    close();
}
