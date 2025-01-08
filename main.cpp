#include "QNumber.h"
#include "Substance.h"
#include "LinearEqutionsSolver.h"

#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<Substance> substs;
    LinearEqutionsSolver solver;
    std::string input, reactants, products;

    std::cout << "Please input an unbalanced chemical eqution:" << std::endl;
    getline(std::cin, input);
    input += " ";

    int i, j, side = 1, isParsing = 0;

    for (i = j = 0; i < input.size(); i++)
    {
        if (input[i] == ' ' || input[i] == '+' ||
            input[i] == '-' || input[i] == '=' || input[i] == '>')
        {
            if (isParsing) substs.push_back(Substance(input.substr(j, i - j), side));
            isParsing = 0;
            if (input[i] == '-' || input[i] == '=' || input[i] == '>')
                side = -1;
        }
        else
        {
            if (!isParsing) j = i;
            isParsing = 1;
        }
    }

    for (auto& ele : AllElements)
    {
        std::vector<QNumber> eqution;
        for (i = 0; i < substs.size(); i++)
        {
            if (substs[i].elements.find(ele) != substs[i].elements.end())
                eqution.push_back(QNumber(substs[i].elements[ele] * substs[i].side));
            else
                eqution.push_back(QNumber(0));
        }
        solver.add(eqution);
    }

    solver.solve();

    if (solver.solution.empty())
    {
        std::cout << "No solution" << std::endl;
        return 0;
    }

    for (auto& coeffs : solver.solution)
    {
        reactants.clear();
        products.clear();
        for (i = 0; i<coeffs.size(); i++)
        {
            int c = coeffs[i].getNumerator();
            int abs_c = c > 0 ? c : -c;
            if (c != 0)
            {

                if (c * substs[i].side > 0)
                {
                    if (!reactants.empty()) reactants += " + ";
                    reactants += std::to_string(abs_c) + substs[i].rawName;
                }
                else
                {
                    if (!products.empty()) products += " + ";
                    products += std::to_string(abs_c) + substs[i].rawName;
                }
            }
        }
        std::cout << reactants << " === " << products << std::endl;
    }
}
//g++ .\main.cpp .\LinearEqutionsSolver.cpp .\QNumber.cpp .\Substance.cpp -o BalanceEqution ; if ($?) { .\BalanceEqution }

/*
Cu + HNO3 -- Cu(NO3)2 + NO + H2O
3Cu + 8HNO3 === 3Cu(NO3)2 + 2NO + 4H2O

CaCO3 + HCl -- CaCl2 + H2O + CO2
1CaCO3 + 2HCl === 1CaCl2 + 1H2O + 1CO2

H2+Ca(CN)2+NaAlF4+FeSO4+MgSiO3+KI+H3PO4+PbCrO4+BrCl+CF2Cl2+SO2->PbBr2+CrCl3+MgCO3+KAl(OH)4+Fe(SCN)3+PI3+Na2SiO3+CaF2+H2O
88H2 + 15Ca(CN)2 + 6NaAlF4 + 10FeSO4 + 3MgSiO3 + 6KI + 2H3PO4 + 6PbCrO4 + 12BrCl + 3CF2Cl2 + 20SO2 === 6PbBr2 + 6CrCl3 + 3MgCO3 + 6KAl(OH)4 + 10Fe(SCN)3 + 2PI3 + 3Na2SiO3 + 15CaF2 + 79H2O

Na2CO3 + HCl -> NaCl + NaHCO3 +H2O +CO2
1Na2CO3 + 1HCl === 1NaCl + 1NaHCO3
1Na2CO3 + 2HCl === 2NaCl + 1H2O + 1CO2

Cl2+NaOH=NaCl+NaClO+NaClO3+H2O
3NaClO === 2NaCl + 1NaClO3
1Cl2 + 2NaOH === 1NaCl + 1NaClO + 1H2O

*/