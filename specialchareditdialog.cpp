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

#include "specialchareditdialog.hpp"
#include "GraphicsItems/specialchargraphicsitem.hpp"

/*!
 * Create a new special char edit dialog for the double-clicked special
 * character
 *
 * \param   setContents The pattern for the special character
 * \param   parent      This widget's parent widget
 */
SpecialCharEditDialog::SpecialCharEditDialog(
        QString setContents,
        QWidget *parent
        )
    : QDialog(parent)
{
    contents = setContents;

    setWindowTitle(tr("Edit Special Character"));
    setWindowIcon(QIcon::fromTheme("expressioneditor", QIcon(":/images/expressioneditor.png")));

    mainLayout = new QVBoxLayout(this);

    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    commonPage = new QWidget(tabWidget);
    tabWidget->addTab(commonPage, tr("Common"));
    commonLayout = new QVBoxLayout(commonPage);

    matchAnyRadio = new QRadioButton(tr("Match Any Character"), tabWidget);
    connect(matchAnyRadio, SIGNAL(clicked()), this, SLOT(updateMatchAny()));
    commonLayout->addWidget(matchAnyRadio);

    QHBoxLayout *lineChars = new QHBoxLayout;
    lineStartRadio = new QRadioButton(tr("Line Start"), tabWidget);
    connect(lineStartRadio, SIGNAL(clicked()), this, SLOT(updateLineStart()));
    lineChars->addWidget(lineStartRadio);

    lineEndRadio = new QRadioButton(tr("Line End"), tabWidget);
    connect(lineEndRadio, SIGNAL(clicked()), this, SLOT(updateLineEnd()));
    lineChars->addWidget(lineEndRadio);
    commonLayout->addLayout(lineChars);

    qtPage = new QWidget(tabWidget);
    tabWidget->addTab(qtPage, tr("Qt/PCRE format"));
    qtLayout = new QVBoxLayout(qtPage);

    pcrePage = new QWidget(tabWidget);
    tabWidget->addTab(pcrePage, tr("Perl-compatible"));
    pcreLayout = new QVBoxLayout(pcrePage);

    currentLabel = new QLabel(tr("Current Character: ") + "\"" + contents + "\" - " + SpecialCharGraphicsItem::parseString(contents).replace("<br>"," "), tabWidget);
    mainLayout->addWidget(currentLabel);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout->addWidget(buttonBox);
}

/*!
 * Update the dialog to display the current special character's pattern and the
 * character/item it represents
 */
void SpecialCharEditDialog::updateDialog()
{
    currentLabel->setText(tr("Current Character: ") + "\"" + contents + "\" - "
                          + SpecialCharGraphicsItem::parseString(contents).replace("<br>"," "));
}

/*!
 * Update the special character to be a "match any" item: "."
 */
void SpecialCharEditDialog::updateMatchAny()
{
    contents = ".";
    updateDialog();
}

/*!
 * Update the special character to be a "line start" item: "^"
 */
void SpecialCharEditDialog::updateLineStart()
{
    contents = "^";
    updateDialog();
}

/*!
 * Update the special character to be a "line end" item: "$"
 */
void SpecialCharEditDialog::updateLineEnd()
{
    contents = "$";
    updateDialog();
}
