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

#include "texteditdialog.hpp"

/*!
 * Create a new modal dialog to edit the text element that has been double
 * clicked
 *
 * \param   curText The current contents of the text element
 * \param   parent  This widget's parent widget
 */
TextEditDialog::TextEditDialog(
        QString curText,
        QWidget *parent
        )
    : QDialog(parent)
{
    text = curText;

    setWindowTitle(tr("Edit Text Item"));
    setWindowIcon(QIcon::fromTheme("expressioneditor", QIcon(":/images/expressioneditor.png")));

    mainLayout = new QVBoxLayout(this);

    textEditLayout = new QHBoxLayout;
    textEditLabel = new QLabel(tr("Text: "), this);
    textEdit = new QLineEdit(this);
    textEdit->setText(text);
    connect(textEdit, SIGNAL(textChanged(QString)), this, SLOT(updateText(QString)));
    textEditLayout->addWidget(textEditLabel);
    textEditLayout->addWidget(textEdit);

    mainLayout->addLayout(textEditLayout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout->addWidget(buttonBox);
}

/*!
 * Return the current text string as a literal string (to be used literally in
 * the regular expression)
 *
 * \return  A pattern representing the literal text contained
 */
QString TextEditDialog::getText() const
{
    QStringList specialchars;
    specialchars << "\\" << "[" << "]" << "(" << ")" << "*" << "^" << "$" << "." << "|" << "?" << "+" << "{" << "}";
    QString pattern = QString("(\\") + specialchars.join("|\\") + ")";
    QString tmp = text;
    return tmp.replace(QRegExp(pattern), "\\\\1");
}

/*!
 * Update the contents of this dialog with new text contents
 *
 * \param   newText The new text to be used in the dialog
 */
void TextEditDialog::updateText(QString newText)
{
    if(text != newText)
    {
        text = newText;
        if(text != textEdit->text())
            textEdit->setText(text);
    }
}
