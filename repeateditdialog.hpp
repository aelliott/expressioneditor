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

#ifndef REPEATEDITDIALOG_HPP
#define REPEATEDITDIALOG_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include "GraphicsItems/repeatgraphicsitem.hpp"

class RepeatEditDialog : public QDialog
{
    Q_OBJECT;

public:
    explicit RepeatEditDialog(RepeatGraphicsItem::Type currentType, int currentMinimum, int currentMaximum, QWidget *parent = 0);
    void updateDialog();
    RepeatGraphicsItem::Type getType() const;
    int getMinimum() const;
    int getMaximum() const;

public slots:
    void updateZeroOrOne();
    void updateZeroOrMore();
    void updateOneOrMore();
    void updateExactValue();
    void updateSpecifiedMinimum();
    void updateSpecifiedMaximum();
    void updateSpecifiedRange();

private:
    QVBoxLayout *groupBoxLayout;
    QGroupBox *groupBox;
    QGridLayout *mainLayout;
    QRadioButton *zeroOrOneRadio;
    QRadioButton *zeroOrMoreRadio;
    QRadioButton *oneOrMoreRadio;
    QRadioButton *exactValueRadio;
    QSpinBox *exactValueInput;
    QRadioButton *specifiedMinimumRadio;
    QSpinBox *specifiedMinimumInput;
    QRadioButton *specifiedMaximumRadio;
    QSpinBox *specifiedMaximumInput;
    QRadioButton *specifiedRangeRadio;
    QSpinBox *specifiedRangeMinInput;
    QLabel *specifiedRangeMaxLabel;
    QSpinBox *specifiedRangeMaxInput;
    QLabel *currentOutputLabel;
    QLineEdit *currentOutputInput;
    QDialogButtonBox *buttonBox;
    bool setup;
    RepeatGraphicsItem::Type type;
    int minimum;
    int maximum;
};

#endif // REPEATEDITDIALOG_HPP
