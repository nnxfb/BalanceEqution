#ifndef QNUMBER_H
#define QNUMBER_H

#include <algorithm>
#include <cassert>
//#include <string>

class QNumber
{
public:
    QNumber(int n, int d=1);
    ~QNumber();

    QNumber operator+(const QNumber& n);
    QNumber operator-(const QNumber& n);
    QNumber operator-();
    QNumber operator*(const QNumber& n);
    QNumber operator/(const QNumber& n);

    bool zero();
    bool one();
    double value();
    int getNumerator();
    int getDenominator();
//    std::string str();

private:
    int numerator;
    int denominator;

    void format();
};

#endif