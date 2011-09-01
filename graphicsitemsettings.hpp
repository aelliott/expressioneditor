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
#ifndef GRAPHICSITEMSETTINGS_HPP
#define GRAPHICSITEMSETTINGS_HPP

#include <QWidget>
#include <QSettings>
#include <QColorDialog>
#include <QDebug>

namespace Ui {
    class GraphicsItemSettings;
}

class GraphicsItemSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsItemSettings(QWidget *parent = 0);
    ~GraphicsItemSettings();

    void setType(QString type);

public slots:
    void reset();
    void apply();

    void horizontalPaddingChanged(int padding);
    void verticalPaddingChanged(int padding);
    void cornerRadiusChanged(int radius);
    void selectColor();

signals:
    void valueChanged();

private:
    Ui::GraphicsItemSettings *_ui;
    QSettings _settings;

    QString _type;
    int _horizontalPadding;
    int _verticalPadding;
    int _cornerRadius;
    QColor _color;
};

#endif // GRAPHICSITEMSETTINGS_HPP
