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
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <QSignalMapper>
#include <QCloseEvent>
#include <QMessageBox>
#include <QGraphicsView>
#include <QPainter>

#include "regexfactory.hpp"
#include "GraphicsItems/expressiongraphicsitem.hpp"
#include "GraphicsItems/placeholdergraphicsitem.hpp"
#include "expressiongraphicsscene.hpp"

namespace Ui {
    class MainWindow;
}

/*!
 * \brief The main window of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newExpression();
    void open();
    void open(QString path);
    void save();
    void saveAs();
    void save(QString path);
    void quit();

    void exportAsImage();
    void setRegexpFormat(int format);
    void showPreferences();

    void regexpHelp();
    void applicationHelp();
    void applicationAbout();

    void updateExpression();
    void updateExpression(QString expression);

    void closeEvent(QCloseEvent *event);

private:
    void updateRecentFiles();
    void updateCommonFiles();
    void updateRegexpFormats();

    Ui::MainWindow *_ui;
    QLabel *_formatLabel;
    QLabel *_errorLabel;
    QString _filePath;
    QString _expression;
    bool _edited;
    RegexFactory *_factory;
    ExpressionGraphicsItem *_visualisation;
    PlaceholderGraphicsItem *_placeholder;
};

#endif // MAINWINDOW_HPP
