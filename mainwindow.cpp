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

    _visualisation = new ExpressionGraphicsItem("", RegexFactory::Qt);

    _ui->expressionView->setScene(new QGraphicsScene());
    QGraphicsScene *scene = _ui->expressionView->scene();
    scene->addItem(_visualisation);
    scene->setSceneRect(scene->itemsBoundingRect());
    _ui->expressionView->setSceneRect(scene->itemsBoundingRect());

    _blockHighlighter = new BlockHighlighter(_ui->textBlockEdit);

    _ui->testInputsTable->setRegexFactory(_factory);
}

/*!
 * Exit the application and clean up memory in the process
 */
MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::newExpression()
{
    if(_edited || !_expression.isEmpty())
    {

    }

    _ui->stackedWidget->setCurrentIndex(1);

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
        _blockHighlighter->setRegexpFormat(RegexFactory::Qt);
        break;
#ifndef NO_PCRE
    case RegexFactory::PCRE:
        _formatLabel->setText(tr("PCRE Format"));
        _blockHighlighter->setRegexpFormat(RegexFactory::PCRE);
        break;
    case RegexFactory::PerlEmulation:
        _formatLabel->setText(tr("Perl Emulation Format"));
        _blockHighlighter->setRegexpFormat(RegexFactory::PerlEmulation);
        break;
#endif // NO_PCRE
#ifndef NO_POSIX
    case RegexFactory::POSIX:
        _formatLabel->setText(tr("POSIX ERE Format"));
        _blockHighlighter->setRegexpFormat(RegexFactory::POSIX);
        break;
#endif // NO_PCRE
#ifndef NO_ICU
    case RegexFactory::ICU:
        _formatLabel->setText(tr("ICU Format"));
        _blockHighlighter->setRegexpFormat(RegexFactory::ICU);
        break;
#endif // NO_ICU
#ifdef WITH_CPP0X
    case RegexFactory::CPP0X:
        _formatLabel->setText(tr("C++0x Format");
        _blockHighlighter->setRegexpFormat(RegexFactory::CPP0X);
        break;
#endif // WITH_CPP0X
    }
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

}

void MainWindow::applicationAbout()
{

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
    scene->removeItem(_visualisation);
    delete _visualisation;
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

    _blockHighlighter->updateExpression(_expression);
    _ui->testInputsTable->updateExpression(_expression);
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
    // [Edit -> Format] POSIX Style Action:
    QAction *actionPosixEREFormat = new QAction(tr("POSIX (Extended)"), this);
    actionPosixEREFormat->setCheckable(true);
    actionPosixEREFormat->setActionGroup(formatGroup);
    actionPosixEREFormat->setStatusTip("Use POSIX Extended Format Expressions");
    connect(actionPosixEREFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionPosixEREFormat, RegexFactory::POSIX);
    _ui->menuExpressionFormat->addAction(actionPosixEREFormat);
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

#ifdef WITH_CPP0X
    // [Edit -> Format] C++0x Style Action
    QAction *actionCpp0xFormat = new QAction(tr("C++0x Format"), this);
    actionCpp0xFormat->setCheckable(true);
    actionCpp0xFormat->setActionGroup(formatGroup);
    actionCpp0xFormat->setStatusTip(tr("Use C++0x Format Expressions"));
    connect(actionCpp0xFormat, SIGNAL(triggered()), map, SLOT(map()));
    map->setMapping(actionCpp0xFormat, RegexFactory::CPP0X);
    _ui->menuExpressionFormat->addAction(cpp0xStyleAction);
#endif // WITH_CPP0X

    connect(map, SIGNAL(mapped(int)), this, SLOT(setRegexpFormat(int)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
