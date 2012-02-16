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
#include "characterclassitem.hpp"

CharacterClassItem::CharacterClassItem(Token *token, int tokenPos, QGraphicsItem *parent)
    : RegexGraphicsItem(token, tokenPos, parent)
{
    _text = "";

    switch(token->type())
    {
    case T_WORD:
        _text = tr("Word\nCharacter");
        break;
    case T_NOT_WORD:
        _text = tr("Non-word\nCharacter");
        break;
    case T_DIGIT:
        _text = tr("Digit\nCharacter");
        break;
    case T_NOT_DIGIT:
        _text = tr("Non-digit\nCharacter");
        break;
    case T_SPACE:
        _text = tr("Space\nCharacter");
        break;
    case T_NOT_SPACE:
        _text = tr("Non-space\nCharacter");
        break;
    default:
        _text = tr("Unhandled\nToken");
    }
}

QRectF CharacterClassItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/CharacterClass/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/CharacterClass/VerticalPadding", 5.0).toDouble();

    int lines = _text.count("\n")+1;
    double textWidth = 0.0;
    QStringList words = _text.split("\n");
    for(int i = 0; i < words.size(); ++i)
        if(_metrics.width(words.at(i)) > textWidth)
            textWidth = _metrics.width(words.at(i));
    // To prevent a rounding error causing a cut-off later, just add an extra pixel now
    textWidth++;

    return QRectF(0, 0, textWidth + 2*horizontalPadding, lines*_metrics.height() + 2*verticalPadding);
}

void CharacterClassItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    _font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    double horizontalPadding = settings.value("Visualisation/CharacterClass/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/CharacterClass/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/CharacterClass/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/CharacterClass/Color", QColor(255,220,255)).value<QColor>();

    painter->setFont(_font);
    painter->setBrush(bgColor);
    painter->setPen(Qt::black);

    QRectF drawRect = boundingRect();
    // Align the rect to the pixel grid
    if(qRound(scenePos().x()) == scenePos().x())
    {
        drawRect.setX(0.5);
        drawRect.setWidth(drawRect.width()-.5);
    }
    if(qRound(scenePos().y()) == scenePos().y())
    {
        drawRect.setHeight(drawRect.height()-.5);
        drawRect.setY(0.5);
    }
    painter->drawRoundedRect(drawRect, cornerRadius, cornerRadius);

    painter->drawText(QRectF(
                          horizontalPadding,
                          verticalPadding,
                          drawRect.width() - 2*horizontalPadding,
                          drawRect.height() - 2*verticalPadding),
                      Qt::AlignCenter | Qt::TextWordWrap,
                      _text);
}

QSizeF CharacterClassItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
