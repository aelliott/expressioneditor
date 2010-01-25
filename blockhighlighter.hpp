#ifndef BLOCKHIGHLIGHTER_HPP
#define BLOCKHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include "regexfactory.hpp"

class BlockHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT;

public:
    explicit BlockHighlighter(QTextEdit *parent = 0);
    void highlightBlock(const QString &text);

public slots:
    void updateExpression(QString exp);
    void setRegexpFormat(int type);

private:
    RegexFactory *factory;
    RegexBase *rx;
};

#endif // BLOCKHIGHLIGHTER_HPP
