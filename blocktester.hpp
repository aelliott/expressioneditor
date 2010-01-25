#ifndef BLOCKTESTER_HPP
#define BLOCKTESTER_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <blockhighlighter.hpp>

class BlockTester : public QWidget
{
    Q_OBJECT;

public:
    explicit BlockTester(QWidget *parent = 0);
    QString text() const;

public slots:
    void updateExpression(QString exp);
    void setText(QString testString);
    void setFormat(int type);

private:
    QVBoxLayout *layout;
    QTextEdit *text_;
    BlockHighlighter *highlighter;
};

#endif // BLOCKTESTER_HPP
