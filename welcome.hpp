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
 * \brief   Provides a welcome screen for Expression Editor with quick start
 *          options like resuming a recent expression, or using a common
 *          expression
 */

#ifndef WELCOME_HPP
#define WELCOME_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QListWidget>
#include <QFile>
#include <QFileInfo>

class Welcome : public QWidget
{
    Q_OBJECT;

public:
    explicit Welcome(QStringList recent, QStringList common, QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QLabel *title;
    QLabel *introduction;
    QHBoxLayout *welcomeOptions;
    QVBoxLayout *welcomeButtons;
    QPushButton *newButton;
    QPushButton *openButton;
    QGroupBox *recentExpressions;
    QListWidget *recentList;
    QGroupBox *commonExpressions;
    QListWidget *commonList;
    QStringList recentFiles;
    QStringList commonFiles;
};

#endif // WELCOME_HPP
