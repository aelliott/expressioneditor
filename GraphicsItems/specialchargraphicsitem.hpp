/*!
 * \file
 *
 * Copyright (c) 2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef SPECIALCHARGRAPHICSITEM_HPP
#define SPECIALCHARGRAPHICSITEM_HPP

#include "GraphicsItems/regexgraphicsitem.hpp"

#include "cmakeconfig.hpp"

#ifndef NO_ICU
#include <unicode/udata.h>
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/ucnv.h>
#endif // NO_ICU

#include "RegexModules/token.hpp"

class SpecialCharGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT

public:
    explicit SpecialCharGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

private:
    QGraphicsTextItem *_text;
};

#endif // SPECIALCHARGRAPHICSITEM_HPP
