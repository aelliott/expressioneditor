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
#ifndef REGEXGRAPHICSITEM_HPP
#define REGEXGRAPHICSITEM_HPP

#include <QGraphicsWidget>
#include <QPainter>
#include <QSettings>
#include <QFontMetrics>

#include "RegexModules/token.hpp"

class RegexGraphicsItem : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit RegexGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent = 0);

    Token *token() const;
    int tokenPos() const;
    int endPos() const;

    void setEndPos(int endPos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    Token *_token;
    int _tokenPos;
    int _endPos;
    QFont _font;
    QFontMetrics _metrics;
};

#endif // REGEXGRAPHICSITEM_HPP
