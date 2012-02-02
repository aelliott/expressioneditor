#ifndef TESTINPUTSWIDGET_HPP
#define TESTINPUTSWIDGET_HPP

#include <QTableWidget>
#include <QDebug>

#include "regexfactory.hpp"

class TestInputsWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit TestInputsWidget(QWidget *parent = 0);

    void addTestRows(int rows);
    void addTestRow();

public slots:
    void updateRows(QTableWidgetItem *item);
    void updateResults();

    void setRegexFactory(RegexFactory *factory);
    void updateExpression(QString expression);

private:
    RegexFactory *_factory;
    QString _expression;
};

#endif // TESTINPUTSWIDGET_HPP
