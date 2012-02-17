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
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

/*!
 * Create a new Expression Editor main window
 *
 * \param parent    This widget's parent widget (typically none)
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
    , _filePath("")
    , _expression("")
    , _edited(false)
    , _visualisation(0)
{
    QSettings settings;
    _ui->setupUi(this);

    QFile css(":/css/main.css");
    css.open(QFile::ReadOnly);
    QString stylesheet = css.readAll();
    setStyleSheet(stylesheet);

    _errorLabel = new QLabel;
    _formatLabel = new QLabel("Qt Format");

    statusBar()->showMessage("Ready");
    statusBar()->addPermanentWidget(_errorLabel);
    statusBar()->addPermanentWidget(_formatLabel);

    _ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    _ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    _ui->menuOpenRecent->setIcon(QIcon::fromTheme("document-open-recent"));
    _ui->menuOpenCommon->setIcon(QIcon::fromTheme("document-open-recent"));
    _ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
    _ui->actionSaveAs->setIcon(QIcon::fromTheme("document-save-as"));
    _ui->actionQuit->setIcon(QIcon::fromTheme("application-exit"));
    _ui->actionPreferences->setIcon(QIcon::fromTheme("configure"));

    updateRecentFiles();
    updateCommonFiles();
    updateRegexpFormats();

    _factory = new RegexFactory(RegexFactory::Qt);

    ExpressionGraphicsScene *scene = new ExpressionGraphicsScene();
    _ui->expressionView->setScene(scene);
    _ui->expressionView->setRenderHint(QPainter::Antialiasing, true);
    _ui->expressionView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    scene->setSceneRect(scene->itemsBoundingRect());
    _ui->expressionView->setSceneRect(scene->itemsBoundingRect());

    _ui->expressionEdit->setRegexFactory(_factory);
    _ui->testInputsTable->setRegexFactory(_factory);
    _ui->textBlockEdit->setRegexFactory(_factory);

    newExpression();
}

/*!
 * Exit the application and clean up memory in the process
 */
MainWindow::~MainWindow()
{
    delete _ui;
    delete _factory;
}

void MainWindow::newExpression()
{
    if(_edited || !_expression.isEmpty())
    {

    }

    // Restore window state
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::open()
{
    if(_edited || !_expression.isEmpty())
    {

    }

}

void MainWindow::open(QString path)
{

}

void MainWindow::save()
{

}

void MainWindow::saveAs()
{

}

void MainWindow::save(QString path)
{

}

void MainWindow::quit()
{
    if(_edited || !_expression.isEmpty())
    {

    }

    close();
}

void MainWindow::exportAsImage()
{

}

void MainWindow::setRegexpFormat(int format)
{
    RegexFactory::RegexFormat type = static_cast<RegexFactory::RegexFormat>(format);
    _factory->setRegexpFormat(type);

    switch(type)
    {
    case RegexFactory::Qt:
        _formatLabel->setText(tr("Qt Format"));
        break;
#ifndef NO_PCRE
    case RegexFactory::PCRE:
        _formatLabel->setText(tr("PCRE Format"));
        break;
    case RegexFactory::PerlEmulation:
        _formatLabel->setText(tr("Perl Emulation Format"));
        break;
#endif // NO_PCRE
#ifndef NO_POSIX
    case RegexFactory::C_POSIX_ERE:
        _formatLabel->setText(tr("POSIX ERE Format"));
        break;
    case RegexFactory::C_POSIX_BRE:
        _formatLabel->setText(tr("POSIX BRE Format"));
        break;
#endif // NO_PCRE
#ifndef NO_ICU
    case RegexFactory::ICU:
        _formatLabel->setText(tr("ICU Format"));
        break;
#endif // NO_ICU
#ifndef NO_CPP11
    case RegexFactory::CPP11_ECMASCRIPT:
        _formatLabel->setText(tr("C++11 (ECMAScript) Format"));
        break;
    case RegexFactory::CPP11_BASIC:
        _formatLabel->setText(tr("C++11 (Basic) Format"));
        break;
    case RegexFactory::CPP11_EXTENDED:
        _formatLabel->setText(tr("C++11 (Extended) Format"));
        break;
    case RegexFactory::CPP11_AWK:
        _formatLabel->setText(tr("C++11 (AWK) Format"));
        break;
    case RegexFactory::CPP11_GREP:
        _formatLabel->setText(tr("C++11 (Grep) Format"));
        break;
    case RegexFactory::CPP11_EGREP:
        _formatLabel->setText(tr("C++11 (EGrep) Format"));
        break;
#endif // NO_CPP11
    }

    updateExpression(_expression);
}

void MainWindow::showPreferences()
{
    SettingsDialog settings;
    settings.exec();
}

void MainWindow::regexpHelp()
{

}

void MainWindow::applicationHelp()
{
    QMessageBox::information(this
                             , tr("Expression Editor Help")
                             , tr("<p>Documentation for Expression Editor is "
                                  "located on its project page at "
                                  "<a href=\"https://github.com/aelliott/expressioneditor/wiki\">https://github.com/aelliott/expressioneditor/wiki</a>")
                             , QMessageBox::Ok
                             );
}

void MainWindow::applicationAbout()
{
    QMessageBox::about(this
                             , tr("About Expression Editor")
                             , tr("<p>Expression Editor is a Regular Expression "
                                  "editing tool intended to aid programmers in "
                                  "writing and troubleshooting regular "
                                  "expressions."
                                  "<p>Expression Editor is free software "
                                  "available under the terms of the GPLv3")
                             );
}

void MainWindow::updateExpression()
{
    _expression = _ui->expressionEdit->toPlainText();
    updateExpression(_expression);
}

void MainWindow::updateExpression(QString expression)
{
    _expression = expression;

    Parser *parser = _factory->regexpParser();
    parser->parse(expression);

    QGraphicsScene *scene = _ui->expressionView->scene();
    if(_visualisation != 0)
    {
        scene->removeItem(_visualisation);
        delete _visualisation;
    }
    _visualisation = new ExpressionGraphicsItem(_expression, _factory->format());
    scene->addItem(_visualisation);
    scene->setSceneRect(scene->itemsBoundingRect());
    _ui->expressionView->setSceneRect(scene->itemsBoundingRect());

    RegexBase *engine = _factory->regexpEngine(_expression);
    if(engine->isValid())
    {
        _ui->validLabel->setPixmap(QPixmap(":/images/valid.png"));
        _ui->validLabel->setToolTip(tr("This expression is valid"));
        _errorLabel->setText(tr("This expression is valid"));
    }
    else
    {
        _ui->validLabel->setPixmap(QPixmap(":/images/invalid.png"));
        _ui->validLabel->setToolTip(engine->getErrorString());
        _errorLabel->setText(QString("Error: ") + engine->getErrorString());
    }

    _ui->testInputsTable->updateExpression(_expression);
    _ui->textBlockEdit->updateExpression(_expression);
}

void MainWindow::updateRecentFiles()
{

}

void MainWindow::updateCommonFiles()
{

}

void MainWindow::updateRegexpFormats()
{
    QActionGroup *formatGroup = new QActionGroup(_ui->menuExpressionFormat);
    QSignalMapper *map = new QSignalMapper(this);

#ifndef NO_PCRE
    // [Edit -> Format] PCRE Style Action:
    QAction *actionPCREFormat = new QAction("PCRE", this);
    actionPCREFormat->setCheckable(true);
    actionPCREFormat->setActionGroup(formatGroup);
    actionPCREFormat->setStatusTip("Use PCRE Format Expressions");
    connect(actionPCREFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionPCREFormat, RegexFactory::PCRE);
    _ui->menuExpressionFormat->addAction(actionPCREFormat);

    // [Edit -> Format] Perl Style Action
    QAction *actionPerlFormat = new QAction(tr("Perl Emulation"), this);
    actionPerlFormat->setCheckable(true);
    actionPerlFormat->setActionGroup(formatGroup);
    actionPerlFormat->setStatusTip(tr("Use Perl Emulation Mode"));
    connect(actionPerlFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionPerlFormat, RegexFactory::PerlEmulation);
    _ui->menuExpressionFormat->addAction(actionPerlFormat);
#endif // NO_PCRE

    // [Edit -> Format] Qt4 Style Action:
    _ui->actionQtFormat->setActionGroup(formatGroup);
    connect(_ui->actionQtFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(_ui->actionQtFormat, RegexFactory::Qt);

#ifndef NO_POSIX
    // [Edit -> Format] regex.h Menu:
    QMenu *regexhMenu = new QMenu(tr("POSIX (regex.h)"), this);
    _ui->menuExpressionFormat->addMenu(regexhMenu);

    // [Edit -> Format -> regex.h] POSIX ERE Style Action:
    QAction *actionPosixEREFormat = new QAction(tr("POSIX (Extended)"), this);
    actionPosixEREFormat->setCheckable(true);
    actionPosixEREFormat->setActionGroup(formatGroup);
    actionPosixEREFormat->setStatusTip("Use POSIX Extended Format Expressions");
    connect(actionPosixEREFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionPosixEREFormat, RegexFactory::C_POSIX_ERE);
    regexhMenu->addAction(actionPosixEREFormat);

    // [Edit -> Format -> regex.h] POSIX BRE Style Action:
    QAction *actionPosixBREFormat = new QAction(tr("POSIX (Basic)"), this);
    actionPosixBREFormat->setCheckable(true);
    actionPosixBREFormat->setActionGroup(formatGroup);
    actionPosixBREFormat->setStatusTip("Use POSIX Basic Format Expressions");
    connect(actionPosixBREFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionPosixBREFormat, RegexFactory::C_POSIX_BRE);
    regexhMenu->addAction(actionPosixBREFormat);
#endif // NO_POSIX

#ifndef NO_ICU
    // [Edit -> Format] ICU Style Action
    QAction *actionICUFormat = new QAction(tr("ICU Format"), this);
    actionICUFormat->setCheckable(true);
    actionICUFormat->setActionGroup(formatGroup);
    actionICUFormat->setStatusTip(tr("Use ICU Format Expressions"));
    connect(actionICUFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionICUFormat, RegexFactory::ICU);
    _ui->menuExpressionFormat->addAction(actionICUFormat);
#endif // NO_ICU

#ifndef NO_CPP11
    // [Edit -> Format] C++11 Menu
    QMenu *cpp11Menu = new QMenu(tr("C++11"), this);
    _ui->menuExpressionFormat->addMenu(cpp11Menu);

    // [Edit -> Format -> C++11] C++11 ECMAScript Style Action
    QAction *actionCpp11ECMAScriptFormat = new QAction(tr("ECMAScript"), this);
    actionCpp11ECMAScriptFormat->setCheckable(true);
    actionCpp11ECMAScriptFormat->setActionGroup(formatGroup);
    actionCpp11ECMAScriptFormat->setStatusTip(tr("Use C++11 ECMAScript Format Expressions"));
    connect(actionCpp11ECMAScriptFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp11ECMAScriptFormat, RegexFactory::CPP11_ECMASCRIPT);
    cpp11Menu->addAction(actionCpp11ECMAScriptFormat);

    // [Edit -> Format -> C++11] C++11 Basic Style Action
    QAction *actionCpp11BasicFormat = new QAction(tr("Basic"), this);
    actionCpp11BasicFormat->setCheckable(true);
    actionCpp11BasicFormat->setActionGroup(formatGroup);
    actionCpp11BasicFormat->setStatusTip(tr("Use C++11 Basic Format Expressions"));
    connect(actionCpp11BasicFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp11BasicFormat, RegexFactory::CPP11_BASIC);
    cpp11Menu->addAction(actionCpp11BasicFormat);

    // [Edit -> Format -> C++11] C++11 Extended Style Action
    QAction *actionCpp11ExtendedFormat = new QAction(tr("Extended"), this);
    actionCpp11ExtendedFormat->setCheckable(true);
    actionCpp11ExtendedFormat->setActionGroup(formatGroup);
    actionCpp11ExtendedFormat->setStatusTip(tr("Use C++11 Extended Format Expressions"));
    connect(actionCpp11ExtendedFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp11ExtendedFormat, RegexFactory::CPP11_EXTENDED);
    cpp11Menu->addAction(actionCpp11ExtendedFormat);

    // [Edit -> Format -> C++11] C++11 AWK Style Action
    QAction *actionCpp11AWKFormat = new QAction(tr("AWK"), this);
    actionCpp11AWKFormat->setCheckable(true);
    actionCpp11AWKFormat->setActionGroup(formatGroup);
    actionCpp11AWKFormat->setStatusTip(tr("Use C++11 AWK Format Expressions"));
    connect(actionCpp11AWKFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp11AWKFormat, RegexFactory::CPP11_AWK);
    cpp11Menu->addAction(actionCpp11AWKFormat);

    // [Edit -> Format -> C++11] C++11 Grep Style Action
    QAction *actionCpp11GrepFormat = new QAction(tr("Grep"), this);
    actionCpp11GrepFormat->setCheckable(true);
    actionCpp11GrepFormat->setActionGroup(formatGroup);
    actionCpp11GrepFormat->setStatusTip(tr("Use C++11 Grep Format Expressions"));
    connect(actionCpp11GrepFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp11GrepFormat, RegexFactory::CPP11_GREP);
    cpp11Menu->addAction(actionCpp11GrepFormat);

    // [Edit -> Format -> C++11] C++11 EGrep Style Action
    QAction *actionCpp11EGrepFormat = new QAction(tr("EGrep"), this);
    actionCpp11EGrepFormat->setCheckable(true);
    actionCpp11EGrepFormat->setActionGroup(formatGroup);
    actionCpp11EGrepFormat->setStatusTip(tr("Use C++11 EGrep Format Expressions"));
    connect(actionCpp11EGrepFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp11EGrepFormat, RegexFactory::CPP11_EGREP);
    cpp11Menu->addAction(actionCpp11EGrepFormat);
#endif // NO_CPP11

    connect(map, SIGNAL(mapped(int)), this, SLOT(setRegexpFormat(int)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
