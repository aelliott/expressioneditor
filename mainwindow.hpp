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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QListWidgetItem>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>
#include <QSignalMapper>
#include "welcome.hpp"
#include "expressioneditor.hpp"
#include "regexfactory.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow();
    QStringList getRecentFiles();

public slots:
    void newFile();
    void openFile();
    void openFile(QListWidgetItem *item);
    void openFile(QString fileName, bool warnOnOpen = true);
    void saveFile();
    void saveFile(QString fileName);
    void saveFileAs();
    void addRecentFile(QString fileName);
    void showRegexHelp();
    void showAppHelp();
    void showAboutApp();
    void exportToImage();
    void setFormatPcre();
    void setFormatQt();
    void setFormatPosix();

private:
    QMenu *fileMenu;
        QAction *newAction;
        // ----
        QAction *openAction;
        QMenu   *recentMenu;
        QSignalMapper *recentMap;
        QMenu   *commonMenu;
        QSignalMapper *commonMap;
        // ----
        QAction *saveAction;
        QAction *saveAsAction;
        // ----
        QAction *quitAction;
    QMenu *editMenu;
        QAction *exportToImageAction;
        // ----
        QMenu *formatMenu;
            QAction *pcreStyleAction;
            QAction *qt4StyleAction;
            QAction *posixStyleAction;
    QMenu *helpMenu;
        QAction *regexHelpAction;
        QAction *appHelpAction;
        // ----
        QAction *aboutAction;
    QLabel *formatLabel;
    Welcome *welcome;
    ExpressionEditor *editor;
    bool fileOpen;
    QString openFilePath;
    QStringList recentFiles;
    QStringList commonFiles;
    static const int maximumRecentFiles = 10;

    void updateSettings();
    void importSettings();
    void createMenuBar();
};

#endif // MAINWINDOW_HPP
