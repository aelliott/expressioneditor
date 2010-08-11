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

#ifndef TEXTEDITDIALOG_HPP
#define TEXTEDITDIALOG_HPP

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QLineEdit>

class TextEditDialog : public QDialog
{
    Q_OBJECT;

public:
    explicit TextEditDialog(QString curText, QWidget *parent = 0);
    QString getText() const;

public slots:
    void updateText(QString newText);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *textEditLayout;
    QLabel *textEditLabel;
    QLineEdit *textEdit;
    QDialogButtonBox *buttonBox;
    QString text;
};

#endif // TEXTEDITDIALOG_HPP
