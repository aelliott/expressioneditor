#include "blocktester.hpp"

BlockTester::BlockTester(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    text_ = new QTextEdit(this);
    highlighter = new BlockHighlighter(text_);
    layout->addWidget(text_);

    setLayout(layout);
}

QString BlockTester::text() const
{
    return text_->toPlainText();
}

void BlockTester::updateExpression(QString exp)
{
    highlighter->updateExpression(exp);
}

void BlockTester::setText(QString testString)
{
    text_->setText(testString);
}

void BlockTester::setFormat(int type)
{
    highlighter->setRegexpFormat(type);
}
