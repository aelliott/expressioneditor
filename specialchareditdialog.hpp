/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009 Alex Elliott <alex@alex-elliott.co.uk>
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
 *
 */

#ifndef SPECIALCHAREDITDIALOG_HPP
#define SPECIALCHAREDITDIALOG_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QRadioButton>
#include <QLabel>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QIcon>

class SpecialCharEditDialog : public QDialog
{
    Q_OBJECT;

public:
    explicit SpecialCharEditDialog(QString setContents, QWidget *parent = 0);

public slots:
    void updateMatchAny();
    void updateLineStart();
    void updateLineEnd();

private:
    void updateDialog();
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
    QWidget *commonPage;
    QVBoxLayout *commonLayout;
    QWidget *qtPage;
    QVBoxLayout *qtLayout;
    QWidget *pcrePage;
    QVBoxLayout *pcreLayout;
    QRadioButton *matchAnyRadio;        // .
    QRadioButton *lineStartRadio;       // ^
    QRadioButton *lineEndRadio;         // $
    QRadioButton *digitRadio;           // \d
    QRadioButton *notDigitRadio;        // \D
    QRadioButton *wordCharRadio;        // \w
    QRadioButton *notWordCharRadio;     // \W
    QRadioButton *wordBoundaryRadio;    // \b
    QRadioButton *notWordBoundaryRadio; // \B
    QRadioButton *whitespaceRadio;      // \s
    QRadioButton *notWhitespaceRadio;   // \S
    QRadioButton *lineBreakRadio;       // \n
    QRadioButton *carraigeReturnRadio;  // \r
    QRadioButton *tabCharRadio;         // \t
    QRadioButton *verticalTabRadio;     // \v
    QRadioButton *bellRadio;            // \a
    QRadioButton *formRadio;            // \f
    QRadioButton *unicodeRadio;         // \xhhhh
    QRegExpValidator *unicodeValidator;
    QLineEdit    *unicodeInput;
    QRadioButton *octalRadio;           // \0ooo and \0oo
    QRegExpValidator *octalValidator;
    QLineEdit    *octalInput;
    QRadioButton *backreferenceRadio;   // \(n) - nth backreference
    QSpinBox     *backreferenceInput;
    QLabel *currentLabel;
    QDialogButtonBox *buttonBox;
    QString contents;
};

#endif // SPECIALCHAREDITDIALOG_HPP
