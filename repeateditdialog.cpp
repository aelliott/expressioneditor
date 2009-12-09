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

#include "repeateditdialog.hpp"

RepeatEditDialog::RepeatEditDialog(RepeatGraphicsItem::Type currentType, int currentMinimum, int currentMaximum, QWidget *parent) : QDialog(parent)
{
    setup = false;
    type = currentType;
    minimum = currentMinimum;
    maximum = currentMaximum;

    setWindowTitle(tr("Edit Repeat Options"));
    setWindowIcon(QIcon::fromTheme("expressioneditor", QIcon(":/images/expressioneditor.png")));

    groupBoxLayout = new QVBoxLayout(this);
    groupBox = new QGroupBox(tr("Repeat Options"), this);
    groupBoxLayout->addWidget(groupBox);

    mainLayout = new QGridLayout(groupBox);
    groupBox->setLayout(mainLayout);

    zeroOrOneRadio = new QRadioButton(tr("Zero or One"), groupBox);
    connect(zeroOrOneRadio, SIGNAL(clicked()), this, SLOT(updateZeroOrOne()));
    mainLayout->addWidget(zeroOrOneRadio, 0, 0);

    zeroOrMoreRadio = new QRadioButton(tr("Zero or More"), groupBox);
    connect(zeroOrMoreRadio, SIGNAL(clicked()), this, SLOT(updateZeroOrMore()));
    mainLayout->addWidget(zeroOrMoreRadio, 1, 0);

    oneOrMoreRadio = new QRadioButton(tr("One or More"), groupBox);
    connect(oneOrMoreRadio, SIGNAL(clicked()), this, SLOT(updateOneOrMore()));
    mainLayout->addWidget(oneOrMoreRadio, 2, 0);

    exactValueRadio = new QRadioButton(tr("Exact Value: "), groupBox);
    connect(exactValueRadio, SIGNAL(clicked()), this, SLOT(updateExactValue()));
    exactValueInput = new QSpinBox(groupBox);
    connect(exactValueInput, SIGNAL(valueChanged(int)), this, SLOT(updateExactValue()));
    exactValueInput->setMinimum(0);
    mainLayout->addWidget(exactValueRadio, 3, 0);
    mainLayout->addWidget(exactValueInput, 3, 1);

    specifiedMinimumRadio = new QRadioButton(tr("Specified Minimum: "), groupBox);
    connect(specifiedMinimumRadio, SIGNAL(clicked()), this, SLOT(updateSpecifiedMinimum()));
    specifiedMinimumInput = new QSpinBox(groupBox);
    connect(specifiedMinimumInput, SIGNAL(valueChanged(int)), this, SLOT(updateSpecifiedMinimum()));
    specifiedMinimumInput->setMinimum(0);
    mainLayout->addWidget(specifiedMinimumRadio, 4, 0);
    mainLayout->addWidget(specifiedMinimumInput, 4, 1);

    specifiedMaximumRadio = new QRadioButton(tr("Specified Maximum: "), groupBox);
    connect(specifiedMaximumRadio, SIGNAL(clicked()), this, SLOT(updateSpecifiedMaximum()));
    specifiedMaximumInput = new QSpinBox(groupBox);
    connect(specifiedMaximumInput, SIGNAL(valueChanged(int)), this, SLOT(updateSpecifiedMaximum()));
    specifiedMaximumInput->setMinimum(0);
    mainLayout->addWidget(specifiedMaximumRadio, 5, 0);
    mainLayout->addWidget(specifiedMaximumInput, 5, 1);

    specifiedRangeRadio = new QRadioButton(tr("Specified Range From: "), groupBox);
    connect(specifiedRangeRadio, SIGNAL(clicked()), this, SLOT(updateSpecifiedRange()));
    specifiedRangeMinInput = new QSpinBox(groupBox);
    connect(specifiedRangeMinInput, SIGNAL(valueChanged(int)), this, SLOT(updateSpecifiedRange()));
    specifiedRangeMinInput->setMinimum(0);
    specifiedRangeMaxLabel = new QLabel("To: ", groupBox);
    specifiedRangeMaxLabel->setAlignment(Qt::AlignRight);
    specifiedRangeMaxInput = new QSpinBox(groupBox);
    connect(specifiedRangeMaxInput, SIGNAL(valueChanged(int)), this, SLOT(updateSpecifiedRange()));
    specifiedRangeMaxInput->setMinimum(0);
    mainLayout->addWidget(specifiedRangeRadio,    6, 0);
    mainLayout->addWidget(specifiedRangeMinInput, 6, 1);
    mainLayout->addWidget(specifiedRangeMaxLabel, 7, 0);
    mainLayout->addWidget(specifiedRangeMaxInput, 7, 1);

    currentOutputLabel = new QLabel(tr("Current Repeat: "), groupBox);
    currentOutputInput = new QLineEdit(groupBox);
    //NOTE: later we could make this text box editable
    currentOutputInput->setDisabled(true);
    mainLayout->addWidget(currentOutputLabel);
    mainLayout->addWidget(currentOutputInput);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    groupBoxLayout->addWidget(buttonBox);

    setLayout(groupBoxLayout);

    updateDialog();
    setup = true;
}

void RepeatEditDialog::updateDialog()
{
    exactValueInput->setDisabled(true);
    specifiedMinimumInput->setDisabled(true);
    specifiedMaximumInput->setDisabled(true);
    specifiedRangeMinInput->setDisabled(true);
    specifiedRangeMaxInput->setDisabled(true);

    QString value = "";
    switch(type)
    {
        case RepeatGraphicsItem::ZeroOrOne:
            zeroOrOneRadio->setChecked(true);
            currentOutputInput->setText("?");
            break;
        case RepeatGraphicsItem::ZeroOrMore:
            zeroOrMoreRadio->setChecked(true);
            currentOutputInput->setText("*");
            break;
        case RepeatGraphicsItem::OneOrMore:
            oneOrMoreRadio->setChecked(true);
            currentOutputInput->setText("+");
            break;
        case RepeatGraphicsItem::ExactValue:
            exactValueRadio->setChecked(true);
            exactValueInput->setDisabled(false);
            exactValueInput->setValue(minimum);
            value = QString("{") + QVariant(minimum).toString() + "}";
            currentOutputInput->setText(value);
            break;
        case RepeatGraphicsItem::SpecifiedRange:
            if(maximum == -1)
            {
                specifiedMinimumRadio->setChecked(true);
                specifiedMinimumInput->setDisabled(false);
                specifiedMinimumInput->setValue(minimum);
                value = QString("{") + QVariant(minimum).toString() + ",}";
                currentOutputInput->setText(value);
            }
            else if(minimum == -1)
            {
                specifiedMaximumRadio->setChecked(true);
                specifiedMaximumInput->setDisabled(false);
                specifiedMaximumInput->setValue(maximum);
                value = QString("{,") + QVariant(maximum).toString() + "}";
                currentOutputInput->setText(value);
            }
            else
            {
                specifiedRangeRadio->setChecked(true);
                specifiedRangeMaxInput->setDisabled(false);
                specifiedRangeMaxInput->setValue(maximum);
                specifiedRangeMinInput->setDisabled(false);
                specifiedRangeMinInput->setValue(minimum);
                value = QString("{") + QVariant(minimum).toString() + "," + QVariant(maximum).toString() + "}";
                currentOutputInput->setText(value);
            }
    }
}

RepeatGraphicsItem::Type RepeatEditDialog::getType()
{
    return type;
}

int RepeatEditDialog::getMinimum()
{
    return minimum;
}

int RepeatEditDialog::getMaximum()
{
    return maximum;
}

void RepeatEditDialog::updateZeroOrOne()
{
    type = RepeatGraphicsItem::ZeroOrOne;
    updateDialog();
}

void RepeatEditDialog::updateZeroOrMore()
{
    type = RepeatGraphicsItem::ZeroOrMore;
    updateDialog();
}

void RepeatEditDialog::updateOneOrMore()
{
    type = RepeatGraphicsItem::OneOrMore;
    updateDialog();
}

void RepeatEditDialog::updateExactValue()
{
    type = RepeatGraphicsItem::ExactValue;
    minimum = exactValueInput->value();
    updateDialog();
}

void RepeatEditDialog::updateSpecifiedMinimum()
{
    if(maximum != -1)
        maximum = -1;
    type = RepeatGraphicsItem::SpecifiedRange;
    minimum = specifiedMinimumInput->value();
    updateDialog();
}

void RepeatEditDialog::updateSpecifiedMaximum()
{
    if(minimum != -1)
        minimum = -1;
    type = RepeatGraphicsItem::SpecifiedRange;
    maximum = specifiedMaximumInput->value();
    updateDialog();
}

void RepeatEditDialog::updateSpecifiedRange()
{
    if(setup)
    {
        type = RepeatGraphicsItem::SpecifiedRange;
        if(specifiedRangeMinInput->value() > specifiedRangeMaxInput->value())
            specifiedRangeMaxInput->setValue(specifiedRangeMinInput->value());
        minimum = specifiedRangeMinInput->value();
        maximum = specifiedRangeMaxInput->value();
        updateDialog();
    }
}
