#include "perlregex.hpp"

PerlRegex::PerlRegex(QString expression, QObject *parent) : _valid(true)
{
    expression = parseExpression(expression);
    PcreRegex(expression, parent);
    regexp = expression;
    pcre.setExpression(expression.toStdString());
}

QString PerlRegex::parseExpression(QString expression)
{
    if(expression.isEmpty())
        return expression;

    QChar delim = expression.at(0);
    if(expression.indexOf(delim, 1) == -1)
    {
        _valid = false;
        return QString();
    }

    _valid = true;
    int endDelim = expression.lastIndexOf(delim, expression.length()-1);
    QString parsed = expression.mid(1, endDelim-1);
    expression.remove(0, endDelim+1);
    QString modifiers = expression;

    if(!modifiers.isEmpty())
        for(int i = 0; i < modifiers.length(); ++i)
            parsed = QString("(?") + modifiers.at(i) + ")" + parsed;

    return parsed;
}

bool PerlRegex::isValid() const
{
    return (pcre.isValid() && _valid);
}

void PerlRegex::setExpression(QString expression)
{
    regexp = expression;
    pcre.setExpression(parseExpression(expression).toStdString());
}
