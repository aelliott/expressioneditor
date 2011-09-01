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
#include <QtGui/QApplication>
#include "mainwindow.hpp"

/*!
 * Program entry point, set up the QApplication and then launch the main window
 *
 * \param   argc    The number of arguments passed in
 * \param   argv    A vector of the arguments passed in
 * \return  Program exit status
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("AElliott");
    app.setOrganizationDomain("alex-elliott.co.uk");
    app.setApplicationName("Expression Editor");

    MainWindow w;
    w.show();

    return app.exec();
}
