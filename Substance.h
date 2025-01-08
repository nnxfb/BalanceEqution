#ifndef SUBSTANCE_H
#define SUBSTANCE_H

#include <string>
#include <map>
#include <set>
#include <cctype>
//#include <iostream>

#define MAX_ELEMENTS 118
#define BASE 32

extern std::set<int> AllElements;

class Substance
{
public:
    Substance(const std::string& name, int s);
    ~Substance();
//    void dump();

    int side;
    std::string rawName;
    std::map<int, int> elements;

private:
    int parseChemicalFormula(int start, int scale);
};

#endif // SUBSTANCE_H