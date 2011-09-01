/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
 *
 * \section LICENSE
 * This file is part of Expression editor
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
#include "graphicsitemsettings.hpp"
#include "ui_graphicsitemsettings.h"

GraphicsItemSettings::GraphicsItemSettings(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::GraphicsItemSettings)
{
    _ui->setupUi(this);

    _ui->colorExampleView->setScene(new QGraphicsScene());
}

GraphicsItemSettings::~GraphicsItemSettings()
{
    delete _ui;
}

void GraphicsItemSettings::setType(QString type)
{
    _type = type;

    _horizontalPadding = _settings.value(
                QString("Visualisation/") + _type
                + "/HorizontalPadding", 8).toInt();
    _verticalPadding = _settings.value(
                QString("Visualisation/") + _type
                + "/VerticalPadding", 6).toInt();
    _cornerRadius = _settings.value(
                QString("Visualisation/") + _type
                + "/CornerRadius", 5).toInt();
    if(_type == "Literal")
        _color = _settings.value(
                    QString("Visualisation/") + _type
                    + "/Color", QColor(220,255,220)).value<QColor>();
    else if(_type == "Grouping")
        _color = _settings.value(
                    QString("Visualisation/") + _type
                    + "/Color", QColor(245,245,245)).value<QColor>();
    else if(_type == "Alternation")
        _color = _settings.value(
                    QString("Visualisation/") + _type
                    + "/Color", QColor(255,255,225)).value<QColor>();
    else if(_type == "BracketExpression")
        _color = _settings.value(
                    QString("Visualisation/") + _type
                    + "/Color", QColor(225,225,255)).value<QColor>();
    else
        _color = _settings.value(
                    QString("Visualisation/") + _type
                    + "/Color", Qt::white).value<QColor>();

    reset();
}

void GraphicsItemSettings::reset()
{
    _ui->horizontalPaddingSpinBox->setValue(_horizontalPadding);
    _ui->verticalPaddingSpinBox->setValue(_verticalPadding);
    _ui->cornerRadiusSpinBox->setValue(_cornerRadius);
    _ui->colorExampleView->scene()->setBackgroundBrush(_color);
}

void GraphicsItemSettings::apply()
{
    setType(_type);
}

void GraphicsItemSettings::horizontalPaddingChanged(int padding)
{
    _settings.setValue(
                QString("Visualisation/") + _type
                + "/HorizontalPadding", padding);

    emit valueChanged();
}

void GraphicsItemSettings::verticalPaddingChanged(int padding)
{
    _settings.setValue(
                QString("Visualisation/") + _type
                + "/VerticalPadding", padding);

    emit valueChanged();
}

void GraphicsItemSettings::cornerRadiusChanged(int radius)
{
    _settings.setValue(
                QString("Visualisation/") + _type
                + "/CornerRadius", radius);

    emit valueChanged();
}

void GraphicsItemSettings::selectColor()
{
    QColorDialog dialog(_color);
    if(dialog.exec())
    {
        _settings.setValue(
                    QString("Visualisation/") + _type
                    + "/Color", dialog.selectedColor());

        _ui->colorExampleView->scene()->setBackgroundBrush(_color);

        emit valueChanged();
    }
}
