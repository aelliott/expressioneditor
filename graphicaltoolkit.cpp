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

#include "graphicaltoolkit.hpp"

GraphicalToolkit::GraphicalToolkit(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    generalTitle = new QGroupBox(tr("General"));
    generalLayout = new QVBoxLayout;
    generalTitle->setLayout(generalLayout);

    generalItems = new QListWidget;
    generalItems->setFixedWidth(180);
    generalItems->setDragEnabled(true);

    QListWidgetItem *textItem = new QListWidgetItem(QIcon(":/images/text.png"), tr("Text Segment"));
    textItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    generalItems->addItem(textItem);
    generalItems->addItem(tr("Character Range"));
    generalLayout->addWidget(generalItems);

    layout->addWidget(generalTitle);

    specialTitle = new QGroupBox(tr("Special Symbols"));
    specialLayout = new QVBoxLayout;
    specialTitle->setLayout(specialLayout);

    specialItems = new QListWidget;
    specialItems->setFixedWidth(180);
    specialItems->addItem(tr("Word Character"));
    specialItems->addItem(tr("Word Boundary"));
    specialLayout->addWidget(specialItems);

    layout->addWidget(specialTitle);
}
