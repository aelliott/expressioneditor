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

#include "mainwindow.hpp"

/*!
 * Create a new MainWindow
 */
MainWindow::MainWindow()
{
    importSettings();

    statusBar()->showMessage("Ready");
    formatLabel = new QLabel;
    statusBar()->addPermanentWidget(formatLabel);

    createMenuBar();

    setWindowIcon(QIcon::fromTheme("expressioneditor", QIcon(":/images/expressioneditor.png")));
    setWindowTitle(tr("Expression Editor - Regex Editing Utility"));
    openFilePath = "";

    fileOpen = false;
    welcome = new Welcome(recentFiles, commonFiles, this);
    setCentralWidget(welcome);
}

/*!
 * Get the list of recently used files
 *
 * \return  The list of recently open files
 */
QStringList MainWindow::getRecentFiles()
{
    return recentFiles;
}

/*!
 * Read in the application's settings such as recently open files and the
 * provided common files
 */
void MainWindow::importSettings()
{
    // Check if we have a home dir folder
    QString settingsDirname = ".expressioneditor";
#ifdef Q_OS_WIN32
    settingsDirname = "expressioneditor";
#endif
    QDir settingsDirectory(QDir::homePath() + "/" + settingsDirname);
    if(settingsDirectory.exists())
    {
        // Read in recent files
        recentFiles.clear();

        QFile recentFile(settingsDirectory.path() + "/recentfiles");
        recentFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QDomDocument recent;
        recent.setContent(recentFile.readAll());

        QDomNodeList recentList = recent.elementsByTagName("file");
        for(int i = 0; i < recentList.size(); ++i)
        {
            QDomElement recentElem = recentList.at(i).toElement();
            recentFiles.push_back(recentElem.text());
        }

        // Read in all common regular expressions present
        commonFiles.clear();

        QDir commonDir(settingsDirectory.path() +"/common");
        QStringList filter;
        filter << "*.regex";
        QFileInfoList fileInfo = commonDir.entryInfoList(filter);
        for(int i = 0; i < fileInfo.size(); ++i)
            commonFiles.push_back(fileInfo.at(i).absoluteFilePath());
    }
    else
    {
        QDir homeDir(QDir::homePath());
        homeDir.mkdir(settingsDirname);

        if(settingsDirectory.exists())
        {
            QDomDocument recent("recentFiles");
            QDomElement root = recent.createElement("root");
            recent.appendChild(root);

            QFile recentFile(settingsDirectory.path() + "/recentfiles");
            recentFile.open(QIODevice::WriteOnly | QIODevice::Text);
            recentFile.write(recent.toByteArray());
        }

        settingsDirectory.mkdir("common");

        recentFiles.clear();
    }
}

/*!
 * Update the settings
 */
void MainWindow::updateSettings()
{
    QString settingsDirname = ".expressioneditor";
#ifdef Q_OS_WIN32
    settingsDirname = "expressioneditor";
#endif

    // Update recent files
    QDomDocument recent("recentFiles");
    QDomElement root = recent.createElement("root");
    recent.appendChild(root);

    for(int i = 0; i < recentFiles.size(); ++i)
    {
        QDomElement file = recent.createElement("file");
        root.appendChild(file);

        QDomCDATASection filePath = recent.createCDATASection(recentFiles.at(i));
        file.appendChild(filePath);
    }

    QFile recentFile(QDir::homePath() + "/" + settingsDirname + "/recentfiles");
    recentFile.open(QIODevice::WriteOnly | QIODevice::Text);
    recentFile.write(recent.toByteArray());
}

/*!
 * Create the application's menu bar
 */
void MainWindow::createMenuBar()
{
    // Start from a clean slate in case we're updating the menu bar
    menuBar()->clear();

    // File Menu:
    fileMenu = menuBar()->addMenu(tr("&File"));

    // [File] New Action:
    newAction = new QAction(QIcon::fromTheme("document-new", QIcon(":/images/document-new.png")), tr("&New Expression"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new expression"));
        connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    fileMenu->addAction(newAction);

    // [File] ----------------
    fileMenu->addSeparator();

    // [File] Open Action:
    openAction = new QAction(QIcon::fromTheme("document-open", QIcon(":/images/document-open.png")), tr("&Open Expression"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("Open an existing expression");
        connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    fileMenu->addAction(openAction);

    // [File] Open Recent Menu:
    recentMenu = fileMenu->addMenu(QIcon::fromTheme("document-open-recent", QIcon(":/images/document-open-recent.png")), tr("Open Recent Expression"));
    recentMap = new QSignalMapper(this);
    if(recentFiles.size() > 0)
        for(int i = 0; i < recentFiles.size(); ++i)
        {
            QFile file(recentFiles.at(i));
            QAction *recentFileAction = new QAction(file.fileName(), this);
            recentFileAction->setStatusTip("Open " + file.fileName());
                connect(recentFileAction, SIGNAL(triggered()), recentMap, SLOT(map()));
            recentMap->setMapping(recentFileAction, recentFiles.at(i));
            recentMenu->addAction(recentFileAction);
        }
    else
        recentMenu->setDisabled(true);
    connect(recentMap, SIGNAL(mapped(QString)), this, SLOT(openFile(QString)));

    // [File] Open Common Menu:
    commonMenu = fileMenu->addMenu(QIcon::fromTheme("document-open-recent", QIcon(":/images/document-open-recent.png")), tr("Open Common Expression"));
    commonMap = new QSignalMapper(this);
    if(commonFiles.size() > 0)
        for(int i = 0; i < commonFiles.size(); ++i)
        {
            QFile file(commonFiles.at(i));
            QAction *commonFileAction = new QAction(file.fileName(), this);
            commonFileAction->setStatusTip("Open " + file.fileName());
                connect(commonFileAction, SIGNAL(triggered()), commonMap, SLOT(map()));
            commonMap->setMapping(commonFileAction, commonFiles.at(i));
            commonMenu->addAction(commonFileAction);
        }
    else
        commonMenu->setDisabled(true);
    connect(commonMap, SIGNAL(mapped(QString)), this, SLOT(openFile(QString)));

    // [File] ----------------
    fileMenu->addSeparator();

    // [File] Save Action:
    saveAction = new QAction(QIcon::fromTheme("document-save", QIcon(":/images/document-save.png")), tr("&Save Expression"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save the current expression");
    if(fileOpen == false)
        saveAction->setDisabled(true);
        connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    fileMenu->addAction(saveAction);

    // [File] Save As Action
    saveAsAction = new QAction(QIcon::fromTheme("document-save-as", QIcon(":/images/document-save-as.png")), tr("Save Expression As..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Save the current expression in a new file");
    if(fileOpen == false)
        saveAsAction->setDisabled(true);
        connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    fileMenu->addAction(saveAsAction);

    // [File] ----------------
    fileMenu->addSeparator();

    // [File] Quit Action
    quitAction = new QAction(QIcon::fromTheme("application-exit", QIcon(":/images/application-exit.png")), tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    quitAction->setStatusTip("Exit the application");
        connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(quitAction);

    // Edit Menu:
    editMenu = menuBar()->addMenu(tr("Edit"));

    // [Edit] Export to Image Action
    exportToImageAction = new QAction(tr("Export Expression as Image"), this);
    exportToImageAction->setStatusTip("Export Visualisation as PNG");
    if(fileOpen == false)
        exportToImageAction->setDisabled(true);
        connect(exportToImageAction, SIGNAL(triggered()), this, SLOT(exportToImage()));
    editMenu->addAction(exportToImageAction);

    // [Edit] ----------------
    editMenu->addSeparator();

    // [Edit] Format Menu:
    formatMenu = editMenu->addMenu(tr("Expression Format"));
    if(fileOpen == false)
        formatMenu->setDisabled(true);
    QActionGroup *formatGroup = new QActionGroup(formatMenu);

#ifndef NO_PCRE
    // [Edit -> Format] PCRE Style Action:
    pcreStyleAction = new QAction("PCRE", this);
    pcreStyleAction->setCheckable(true);
    pcreStyleAction->setChecked(true);
    pcreStyleAction->setActionGroup(formatGroup);
    pcreStyleAction->setStatusTip("Use PCRE Format Expressions");
        connect(pcreStyleAction, SIGNAL(triggered()), this, SLOT(setFormatPcre()));
    formatMenu->addAction(pcreStyleAction);

    // [Edit -> Format] Perl Style Action
    perlStyleAction = new QAction(tr("Perl Emulation"), this);
    perlStyleAction->setCheckable(true);
    perlStyleAction->setActionGroup(formatGroup);
    perlStyleAction->setStatusTip(tr("Use Perl Emulation Mode"));
        connect(perlStyleAction, SIGNAL(triggered()), this, SLOT(setFormatPerlEmulation()));
    formatMenu->addAction(perlStyleAction);
#endif // NO_PCRE

    // [Edit -> Format] Qt4 Style Action:
    qt4StyleAction = new QAction(tr("Qt4 Style"), this);
    qt4StyleAction->setCheckable(true);
    qt4StyleAction->setActionGroup(formatGroup);
    qt4StyleAction->setStatusTip("Use Qt4 Format Expressions");
        connect(qt4StyleAction, SIGNAL(triggered()), this, SLOT(setFormatQt()));
    formatMenu->addAction(qt4StyleAction);

#ifndef NO_POSIX
    // [Edit -> Format] POSIX Style Action:
    posixStyleAction = new QAction(tr("POSIX (Extended)"), this);
    posixStyleAction->setCheckable(true);
    posixStyleAction->setActionGroup(formatGroup);
    posixStyleAction->setStatusTip("Use POSIX Extended Format Expressions");
        connect(posixStyleAction, SIGNAL(triggered()), this, SLOT(setFormatPosix()));
    formatMenu->addAction(posixStyleAction);
#endif // NO_POSIX

#ifndef NO_ICU
    // [Edit -> Format] ICU Style Action
    icuStyleAction = new QAction(tr("ICU Format"), this);
    icuStyleAction->setCheckable(true);
    icuStyleAction->setActionGroup(formatGroup);
    icuStyleAction->setStatusTip(tr("Use ICU Format Expressions"));
        connect(icuStyleAction, SIGNAL(triggered()), this, SLOT(setFormatIcu()));
    formatMenu->addAction(icuStyleAction);
#endif // NO_ICU

#ifdef WITH_CPP0X
    // [Edit -> Format] C++0x Style Action
    cpp0xStyleAction = new QAction(tr("C++0x Format"), this);
    cpp0xStyleAction->setCheckable(true);
    cpp0xStyleAction->setActionGroup(formatGroup);
    cpp0xStyleAction->setStatusTip(tr("Use C++0x Format Expressions"));
        connect(cpp0xStyleAction, SIGNAL(triggered()), this, SLOT(setFormatCpp0x()));
    formatMenu->addAction(cpp0xStyleAction);
#endif // WITH_CPP0X

    // [Edit] ----------------
    editMenu->addSeparator();

    // [Edit] Preferences
    preferencesAction = new QAction(QIcon::fromTheme("configure"), tr("Preferences"), this);
    preferencesAction->setStatusTip(tr("Edit the Application Settings"));
        connect(preferencesAction, SIGNAL(triggered()), this, SLOT(showSettings()));
    editMenu->addAction(preferencesAction);

    // Help Menu:
    helpMenu = menuBar()->addMenu(tr("&Help"));

    // [Help] Regex Help Action:
    regexHelpAction = new QAction(tr("Regular Expression Reference"), this);
    regexHelpAction->setStatusTip("View regular expression help");
        connect(regexHelpAction, SIGNAL(triggered()), this, SLOT(showRegexHelp()));
    helpMenu->addAction(regexHelpAction);

    // [Help] App Help Action:
    appHelpAction = new QAction(tr("Expression Editor Manual"), this);
    appHelpAction->setShortcut(QKeySequence::HelpContents);
    appHelpAction->setStatusTip("View application documentation");
        connect(appHelpAction, SIGNAL(triggered()), this, SLOT(showAppHelp()));
    helpMenu->addAction(appHelpAction);

    // [Help] ----------------
    helpMenu->addSeparator();

    // [Help] About Application:
    aboutAction = new QAction(QIcon::fromTheme("expressioneditor", QIcon(":/images/expressioneditor.png")), tr("About Expression Editor"), this);
    aboutAction->setStatusTip("About this application");
        connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutApp()));
    helpMenu->addAction(aboutAction);
}

/*!
 * Create a new expression
 */
void MainWindow::newFile()
{
    // If there is already a file open ask if they want to discard changes
    if(fileOpen)
    {
        int response = QMessageBox::question(this, tr("Open a New File?"),
                                          tr("Are you sure you wish to open a new expression and leave the old one?"),
                                          QMessageBox::Ok | QMessageBox::Cancel);

        if(response == QMessageBox::Cancel)
            return;
    }

    // Update the application status and refresh the menu bar to reflect this
    fileOpen = true;
    createMenuBar();

    openFilePath = "";

    // Set the application up to create a new expression
    editor = new ExpressionEditor(this);
    setCentralWidget(editor);
#ifndef NO_PCRE
    setFormatPcre();
#else
    setFormatQt();
#endif
}

/*!
 * Open an existing expression
 */
void MainWindow::openFile()
{
    // If there is already a file open ask if they want to discard changes
    if(fileOpen)
    {
        int response = QMessageBox::question(this, tr("Open a New File?"),
                                          tr("Are you sure you wish to open a new expression and leave the old one?"),
                                          QMessageBox::Ok | QMessageBox::Cancel);

        if(response == QMessageBox::Cancel)
            return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Regular Expression"), QDir::homePath(), tr("Expression Files (*.regex)"));
    if(!fileName.isEmpty())
        openFile(fileName, false);
}

/*!
 * Open the existing file specified
 *
 * \param   item    The file to open (taken from a list)
 */
void MainWindow::openFile(QListWidgetItem *item)
{
    openFile(item->data(Qt::UserRole).toString());
}

/*!
 * Open the existing file specified
 *
 * \param   fileName    The file to open
 * \param   warnOnOpen  Whether to warn the user about discarding changes or not
 *                      as they may have been warned previously.  Default to
 *                      true (display a warning)
 */
void MainWindow::openFile(QString fileName, bool warnOnOpen)
{
    // If there is already a file open ask if they want to discard changes
    if(fileOpen && warnOnOpen)
    {
        int response = QMessageBox::question(this, tr("Open a New File?"),
                                          tr("Are you sure you wish to open a new expression and leave the old one?"),
                                          QMessageBox::Ok | QMessageBox::Cancel);

        if(response == QMessageBox::Cancel)
            return;
    }

    if(QFile::exists(fileName))
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString fileContents(file.readAll());
        fileContents = fileContents.trimmed();

        QDomDocument document("expression");
        document.setContent(fileContents);

        editor = new ExpressionEditor(this);
        setCentralWidget(editor);

        QDomNodeList formatList = document.elementsByTagName("format");
        if(formatList.size() > 0)
        {
            QString format = formatList.at(0).toElement().text();
            if(format.contains("qt"))
                setFormatQt();
            else if(format.contains("posix"))
            {
#ifndef NO_POSIX
                setFormatPosix();
#else
                QMessageBox errorMessage(QMessageBox::Critical, tr("Error Opening File"), tr("Error opening file.  ExpressionEditor was built without support for POSIX, falling back to Qt4 mode"));
                errorMessage.show();
#endif
            }
            else
            {
#ifndef NO_PCRE
                setFormatPcre();
#else
                QMessageBox errorMessage(QMessageBox::Critical, tr("Error Opening File"), tr("Error opening file.  ExpressionEditor was built without support for PCRE, falling back to Qt4 mode"));
                errorMessage.show();
#endif // NO_PCRE
            }
        }
        else
#ifndef NO_PCRE
            setFormatPcre();
#else
            setFormatQt();
#endif // NO_PCRE

        QDomNodeList expressionList = document.elementsByTagName("expression");
        QDomNode expressionNode = expressionList.at(0);
        editor->updateExpression(expressionNode.toElement().text());

        QDomNodeList testsList = document.elementsByTagName("test");
        for(int i = 0; i < testsList.size(); ++i)
        {
            QDomElement testElem = testsList.at(i).toElement();
            editor->addTestString(testElem.text());
        }

        fileOpen = true;
        createMenuBar();
        openFilePath = fileName;
        addRecentFile(fileName);
    }
    else
        QMessageBox::warning(this, tr("File Not Found"), tr("The requested file: \"")+fileName+tr("\" was not found."));
}

/*!
 * Save the current file, to the existing file if one exists
 */
void MainWindow::saveFile()
{
    QString fileName;
    if(openFilePath.isEmpty())
        fileName = QFileDialog::getSaveFileName(this, tr("Save Expression"), QDir::homePath(), tr("Expression files (*.regex)"));
    else
        fileName = openFilePath;
    if(!fileName.isEmpty())
        saveFile(fileName);
}

/*!
 * Perform the save method, save to the specified file name
 *
 * \param   fileName    The location to save the file to
 */
void MainWindow::saveFile(QString fileName)
{
    QDomDocument saveDocument("expression");
    QDomElement root = saveDocument.createElement("root");
    saveDocument.appendChild(root);

    QDomElement formatElem = saveDocument.createElement("format");
    root.appendChild(formatElem);

    QDomText regexpFormat = saveDocument.createTextNode(format);
    formatElem.appendChild(regexpFormat);

    QDomElement expression = saveDocument.createElement("expression");
    root.appendChild(expression);

    QDomCDATASection regex = saveDocument.createCDATASection(editor->getExpression());
    expression.appendChild(regex);

    QDomElement tests = saveDocument.createElement("tests");
    root.appendChild(tests);

    QStringList testStrings = editor->getTestStrings();
    for(int i = 0; i < testStrings.size(); ++i)
    {
        QDomElement test = saveDocument.createElement("test");
        tests.appendChild(test);

        QDomCDATASection testString = saveDocument.createCDATASection(testStrings.at(i));
        test.appendChild(testString);
    }

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(saveDocument.toByteArray());
    addRecentFile(fileName);
    openFilePath = fileName;
}

/*!
 * Save the file in a new location
 */
void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Expression"), QDir::homePath(), tr("Expression files (*.regex)"));
    if(!fileName.isEmpty())
        saveFile(fileName);
}

/*!
 * Add the provided file path to recent files if it isn't already in the list.
 * If the file is present in the list move it to the top
 *
 * \param   fileName    The file path to add to the recent files list
 */
void MainWindow::addRecentFile(QString fileName)
{
    if(recentFiles.contains(fileName))
    {
        if(recentFiles.at(0) != fileName)
        {
            for(int i = 1; i < recentFiles.size(); ++i)
            {
                if(recentFiles.at(i) == fileName)
                    recentFiles.removeAt(i);
            }
            recentFiles.push_front(fileName);
            updateSettings();
            createMenuBar();
        }
    }
    else
    {
        while(recentFiles.size() >= MainWindow::maximumRecentFiles)
            recentFiles.removeLast();
        recentFiles.push_front(fileName);
        updateSettings();
        createMenuBar();
    }
}

/*!
 * Show some kind of regex help dialog
 */
void MainWindow::showRegexHelp()
{
    // I should perhaps ask to borrow a cheat sheet, or produce one
}

/*!
 * Show details of how to get expression editor assistance
 */
void MainWindow::showAppHelp()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Expression Editor Manual"));
    msgBox.setText(tr("<h2>Documentation</h2>"
                      "<p>Documentation is available at http://wiki.github.com/aelliott/expressioneditor"));
    msgBox.setIconPixmap(QPixmap(":/images/expressioneditor-shadow.png"));
    msgBox.exec();
}

/*!
 * Provide details about this application
 */
void MainWindow::showAboutApp()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("About Expression Editor"));
    msgBox.setText(tr("<h2>Expression Editor (pre alpha)</h2>"
                      "<p>Expression Editor is a Regular Expression (regexp) editor "
                      "which provides text-based and GUI-based editing tools and "
                      "a testing element to ensure validity.</p>"
                      "<p>The editor supports several regexp formats including "
                      "perl-compatible, POSIX extended, ICU and Qt4's internal format."
                      "<br></p>"
                      "<p>Expression Editor was written by Alex Elliott "
                      "&lt;alex@alex-elliott.co.uk&gt;"));
    msgBox.setIconPixmap(QPixmap(":/images/expressioneditor-shadow.png"));
    msgBox.exec();
}

/*!
 * Export the current regular expression visualisation to a saved PNG file
 */
void MainWindow::exportToImage()
{
    QPixmap image = editor->exportToImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Expression Visualisation"), QDir::homePath(), tr("PNG File (*.png)"));
    if(!fileName.isEmpty())
        image.save(fileName);
}

#ifndef NO_PCRE
/*!
 * Set the current regular expression format to PCRE mode and update the
 * interface to reflect this
 */
void MainWindow::setFormatPcre()
{
    editor->setRegexpFormat(RegexFactory::PCRE);
    formatLabel->setText("PCRE Format");
    format = "pcre";
    pcreStyleAction->setChecked(true);
}

/*!
 * Set the current regular expression format to PERL emulation mode and update
 * the interface to reflect this
 */
void MainWindow::setFormatPerlEmulation()
{
    editor->setRegexpFormat(RegexFactory::PerlEmulation);
    formatLabel->setText("Perl Emulation");
    format = "perl";
    perlStyleAction->setChecked(true);
}
#endif // NO_PCRE

/*!
 * Set the current regular expression format to Qt4 mode and update the
 * interface to reflect this
 */
void MainWindow::setFormatQt()
{
    editor->setRegexpFormat(RegexFactory::Qt);
    formatLabel->setText("Qt4 Format");
    format = "qt";
    qt4StyleAction->setChecked(true);
}

#ifndef NO_POSIX
/*!
 * Set the current regular expression format to POSIX mode and update the
 * interface to reflect this
 */
void MainWindow::setFormatPosix()
{
    editor->setRegexpFormat(RegexFactory::POSIX);
    formatLabel->setText("POSIX Format");
    format = "posix";
    posixStyleAction->setChecked(true);
}
#endif // NO_POSIX

#ifndef NO_ICU
/*!
 * Set the current regular expression format to ICU regex mode and update the
 * interface to reflect this
 */
void MainWindow::setFormatIcu()
{
    editor->setRegexpFormat(RegexFactory::ICU);
    formatLabel->setText("ICU Format");
    format = "icu";
    icuStyleAction->setChecked(true);
}
#endif // NO_ICU

#ifdef WITH_CPP0X
/*!
 * Set the current regular expression format to C++0x mode and update the
 * interface to reflect this
 */
void MainWindow::setFormatCpp0x()
{
    editor->setRegexpFormat(RegexFactory::CPP0X);
    formatLabel->setText("C++0x Format");
    format = "cpp0x";
    cpp0xStyleAction->setChecked(true);
}
#endif // WITH_CPP0X

/*!
 * Show the applications settings dialog
 */
void MainWindow::showSettings()
{
    SettingsDialog *s = new SettingsDialog(this);
    s->show();
}
