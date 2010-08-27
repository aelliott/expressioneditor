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

TextEditDialog::TextEditDialog(QString curText, QWidget *parent) : QDialog(parent)
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

QString TextEditDialog::getText() const
{
    QStringList specialchars;
    specialchars << "\\" << "[" << "]" << "(" << ")" << "*" << "^" << "$" << "." << "|" << "?" << "+" << "{" << "}";
    QString pattern = QString("(\\") + specialchars.join("|\\") + ")";
    QString tmp = text;
    return tmp.replace(QRegExp(pattern), "\\\\1");
}

/**
 * Public slots
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
