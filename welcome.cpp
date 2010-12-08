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

#include "welcome.hpp"

/*!
 * Create and set up the welcome screen
 *
 * \param   recent  A list of the recent files that have been used
 * \param   common  A list of common regular expression files
 * \param   parent  This widget's parent widget
 */
Welcome::Welcome(
        QStringList recent,
        QStringList common,
        QWidget *parent
        )
    : QWidget(parent)
{
    recentFiles = recent;
    commonFiles = common;
    mainLayout = new QVBoxLayout(this);

    title = new QLabel(tr("Expression Editor"));
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(tr("QLabel { font: 40px 'Georgia', sans-serif; }"));
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    introduction = new QLabel(tr("Welcome to Expression Editor, a graphical or text based regular expression editing utility."));
    introduction->setAlignment(Qt::AlignCenter);

    welcomeOptions = new QHBoxLayout;

    welcomeButtons = new QVBoxLayout;
    newButton = new QPushButton(tr("New Expression..."));
        connect(newButton, SIGNAL(pressed()), parent, SLOT(newFile()));
    openButton = new QPushButton(tr("Open Expression..."));
        connect(openButton, SIGNAL(pressed()), parent, SLOT(openFile()));
    welcomeButtons->addWidget(newButton);
    welcomeButtons->addWidget(openButton);

    recentExpressions = new QGroupBox(tr("Recent Expressions:"));
    recentExpressions->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QHBoxLayout *tmp = new QHBoxLayout(recentExpressions);
    recentList = new QListWidget(recentExpressions);
    for(int i = 0; i < recentFiles.size(); ++i)
    {
        QFileInfo file(recentFiles.at(i));
        QListWidgetItem *tmp = new QListWidgetItem(file.fileName());
        tmp->setData(Qt::UserRole, file.absoluteFilePath());
        recentList->addItem(tmp);
    }
        connect(recentList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), parent, SLOT(openFile(QListWidgetItem*)));
    tmp->addWidget(recentList);

    commonExpressions = new QGroupBox(tr("Common Expressions:"));
    commonExpressions->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QHBoxLayout *tmp2 = new QHBoxLayout(commonExpressions);
    commonList = new QListWidget(commonExpressions);
    for(int i = 0; i < commonFiles.size(); ++i)
    {
        QFileInfo file(commonFiles.at(i));
        QListWidgetItem *tmp = new QListWidgetItem(file.fileName());
        tmp->setData(Qt::UserRole, file.absoluteFilePath());
        commonList->addItem(tmp);
    }
        connect(commonList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), parent, SLOT(openFile(QListWidgetItem*)));
    tmp2->addWidget(commonList);

    connect(recentList, SIGNAL(itemSelectionChanged()), commonList, SLOT(clearSelection()));
    connect(commonList, SIGNAL(itemSelectionChanged()), recentList, SLOT(clearSelection()));

    welcomeOptions->addStretch(10);
    welcomeOptions->addLayout(welcomeButtons);
    welcomeOptions->addStretch(1);
    welcomeOptions->addWidget(recentExpressions);
    welcomeOptions->addStretch(1);
    welcomeOptions->addWidget(commonExpressions);
    welcomeOptions->addStretch(10);

    mainLayout->addStretch(10);
    mainLayout->addWidget(title);
    mainLayout->addStretch(1);
    mainLayout->addWidget(introduction);
    mainLayout->addStretch(1);
    mainLayout->addLayout(welcomeOptions);
    mainLayout->addStretch(20);
}
