#include "blockhighlighter.hpp"

BlockHighlighter::BlockHighlighter(QTextEdit *parent) : QSyntaxHighlighter(parent)
{
    factory = new RegexFactory();
    rx = factory->factory(QString());
}

void BlockHighlighter::highlightBlock(const QString &text)
{
    if(!rx->isValid())
        return;

    QTextCharFormat red;
    red.setForeground(Qt::red);
    QTextCharFormat blue;
    blue.setForeground(Qt::blue);
    int offset = 0;
    bool isRed = true;
    while((offset = rx->indexIn(text, offset)) != -1)
    {
        int length = rx->matchedLength();
        if(isRed)
            setFormat(offset, length, red);
        else
            setFormat(offset, length, blue);
        isRed = !isRed;
        offset += length;
    }
}

void BlockHighlighter::updateExpression(QString exp)
{
    rx = factory->factory(exp);
}

void BlockHighlighter::setRegexpFormat(int type)
{
    factory->setType(type);
    updateExpression(rx->getExpression());
}
