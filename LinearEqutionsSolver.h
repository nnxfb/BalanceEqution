#ifndef LINEAREQUTIONSSOLVER_H
#define LINEAREQUTIONSSOLVER_H

#include "QNumber.h"
#include <vector>
#include <algorithm>

class LinearEqutionsSolver
{
public:
    LinearEqutionsSolver();
    ~LinearEqutionsSolver();
    void add(const std::vector<QNumber>& eq);
    void solve();

    std::vector<std::vector<QNumber>> solution;

private:
    std::vector<std::vector<QNumber>> matrix;
    std::vector<int> index;
    std::vector<int> pivot;
    std::vector<int> freevars;

    void rref();
};

#endif // LINEAREQUTIONSSOLVER_H