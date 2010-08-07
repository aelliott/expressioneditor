#ifndef PERLREGEX_H
#define PERLREGEX_H

#include "pcreregex.hpp"

class PerlRegex : public PcreRegex
{
    Q_OBJECT;

protected:
    bool _valid;

public:
    explicit PerlRegex(QString expression = QString(), QObject *parent = 0);
    QString parseExpression(QString expression);
    bool isValid() const;
    void setExpression(QString expression);
};

#endif // PERLREGEX_H
