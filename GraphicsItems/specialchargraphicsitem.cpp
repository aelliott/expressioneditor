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
#include "specialchargraphicsitem.hpp"

SpecialCharGraphicsItem::SpecialCharGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent)
    : RegexGraphicsItem(token, tokenPos, parent)
{
    _text = "";

    switch(token->type())
    {
    case T_ANY_CHARACTER:
        _text = tr("Any\nCharacter");
        break;
    case T_BELL:
        _text = tr("Bell\nCharacter");
        break;
    case T_BACKSPACE:
        _text = tr("Backspace\nCharacter");
        break;
    case T_ESCAPE:
        _text = tr("Escape\nCharacter");
        break;
    case T_FORM_FEED:
        _text = tr("Form\nFeed");
        break;
    case T_LINE_FEED:
        _text = tr("Line\nFeed");
        break;
    case T_CARRIAGE_RETURN:
        _text = tr("Carriage\nReturn");
        break;
    case T_HORIZONTAL_TAB:
        _text = tr("Horizonal\nTab");
        break;
    case T_VERTICAL_TAB:
        _text = tr("Vertical\nTab");
        break;
    case T_ASCII_CONTROL_CHAR:
        _text = tr("ASCII Control\nCharacter");
        break;
    case T_UNICODE_NEWLINE:
        _text = tr("Unicode\nNewline");
        break;
    case T_BYTE:
        _text = tr("Any\nByte");
        break;
    case T_OCTAL_CHAR:
        _text = tr("Octal\nCharacter");
        break;
    case T_HEXADECIMAL_CHAR:
        _text = tr("Hexadecimal\nCharacter");
        break;
    case T_UNICODE_CHAR:
        _text = tr("Unicode\nCharacter");
        break;
    case T_UNICODE_NAMED_CHAR:
    {
        QString msg;

#ifndef NO_ICU
        QString name = token->value().mid(3, token->value().length() - 4);

        //UnicodeString unicodeName(name.toStdString().c_str());
        UnicodeString unicodeChar;
        UErrorCode status;

        unicodeChar = UnicodeString(u_charFromName(
                                        U_EXTENDED_CHAR_NAME,
                                        name.toStdString().c_str(),
                                        &status));

        UConverter *conv = ucnv_open("iso-8859-1", &status);
        char *dest = new char[9];
        int32_t targetsize = unicodeChar.extract(dest, 8, conv, status);
        dest[targetsize] = 0;

        _text = tr("Unicode Named\nCharacter \"%1\"");
        _text = _text.arg(QString(dest));
#else
        _text = tr("Unicode Named\nCharacter");
#endif // NO_ICU
    }
        break;
    case T_GRAPHEME_CLUSTER:
        _text = tr("Grapheme\nCluster");
        break;
    default:
        _text = tr("Unhandled token");
    }
}

QRectF SpecialCharGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/SpecialCharacter/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/SpecialCharacter/VerticalPadding", 5.0).toDouble();

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

void SpecialCharGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    _font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    double horizontalPadding = settings.value("Visualisation/SpecialCharacter/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/SpecialCharacter/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/SpecialCharacter/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/SpecialCharacter/Color", QColor(220,255,255)).value<QColor>();

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

QSizeF SpecialCharGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
