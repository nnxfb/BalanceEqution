#include "QNumber.h"

QNumber::QNumber(int n, int d) : numerator(n), denominator(d)
{
    assert(denominator != 0);
    format();
};
QNumber::~QNumber() {};

QNumber QNumber::operator+(const QNumber& n)
{
    return QNumber(
        this->numerator * n.denominator + this->denominator * n.numerator,
        this->denominator * n.denominator);
}
QNumber QNumber::operator-(const QNumber& n)
{
    return QNumber(
        this->numerator * n.denominator - this->denominator * n.numerator,
        this->denominator * n.denominator);
}
QNumber QNumber::operator-()
{
    return QNumber(-this->numerator, this->denominator);
}
QNumber QNumber::operator*(const QNumber& n)
{
    return QNumber(
        this->numerator * n.numerator,
        this->denominator * n.denominator);
}
QNumber QNumber::operator/(const QNumber& n)
{
    assert(n.numerator != 0);
    return QNumber(
        this->numerator * n.denominator,
        this->denominator * n.numerator);
}
bool QNumber::zero() { return numerator == 0; }
bool QNumber::one() { return (numerator==1 && denominator==1); }
double QNumber::value(){ return (double)numerator/(double)denominator; }
int QNumber::getNumerator() { return numerator; }
int QNumber::getDenominator() { return denominator; }
//std::string QNumber::str(){ return std::to_string(numerator)+"/"+std::to_string(denominator); }

void QNumber::format()
{
    if (numerator == 0)
    {
        denominator = 1;
        return;
    }
    if (denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }
    int g = std::__gcd(numerator < 0 ? -numerator : numerator, denominator);
    numerator /= g;
    denominator /= g;
}