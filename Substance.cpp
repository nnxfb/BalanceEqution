#include "Substance.h"

std::set<int> AllElements;

Substance::Substance(const std::string& name, int s) : rawName(name), side(s)
{
    parseChemicalFormula(rawName.size() - 1, 1);
}
Substance::~Substance() {}

int Substance::parseChemicalFormula(int start, int scale)
{
    int i, w, number, symbol;
    for (i = start; i >= 0 && rawName[i] != '(' && rawName[i] != '['; i--)
    {
        number = 1;
        if (isdigit(rawName[i]))
        {
            for (number = 0, w = 1; isdigit(rawName[i]); i--, w *= 10)
                number += (rawName[i] - '0') * w;
        }
        number *= scale;

        if (isalpha(rawName[i]))
        {
            symbol = 0;
            if (islower(rawName[i]))
                symbol = rawName[i--] - 'a' + 1;
            symbol = symbol * BASE + rawName[i] - 'A' + 1;

            if (elements.find(symbol) == elements.end())
            {
                if (AllElements.find(symbol) == AllElements.end())
                    AllElements.insert(symbol);
                elements[symbol] = number;
            }
            else
                elements[symbol] += number;
        }

        else if (rawName[i] == ')' || rawName[i] == ']')
            i = parseChemicalFormula(i - 1, number);
    }
    return i;
}
// void Substance::dump()
// {
//     std::cout<<"<"<<rawName<<"> =>  ";
//     for(const auto& e : elements)
//     {
//         std::cout<<char(e.first%BASE+'A'-1)
//             <<(e.first>BASE ? char(e.first/BASE+'a'-1):' ')
//             <<":"
//             <<e.second
//             <<"  ";
//     }
//     std::cout<<std::endl;
// }
/*

CH3(CH(C(CH3)2SO3Na)CH2)2C6H5

              CH3
              |
          CH3-C-SO3Na
              |
   CH3-CH-CH2-CH-CH2-C6H5
       |
   CH3-C-SO3Na
       |
       CH3

*/