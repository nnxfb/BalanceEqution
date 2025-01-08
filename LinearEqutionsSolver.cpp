#include "LinearEqutionsSolver.h"

LinearEqutionsSolver::LinearEqutionsSolver() { }
LinearEqutionsSolver::~LinearEqutionsSolver() { }

void LinearEqutionsSolver::add(const std::vector<QNumber>& eq)
{
    matrix.push_back(eq);
}
void LinearEqutionsSolver::rref()
{
    int i, j, k, p, row = matrix.size(), col = matrix[0].size();
    index.resize(row, -1);
    pivot.resize(row, -1);
    QNumber scale(0);

    for (i = 0; i < row; i++)
    {
        for (p = 0; p < col; p++)
            if (!matrix[i][p].zero())
                break;
        if (p == col)
            continue;

        pivot[i] = p;
        index[p] = i;

        for (j = i + 1; j < row; j++)
        {
            if (matrix[j][p].zero())
                continue;

            scale = matrix[j][p] / matrix[i][p];
            for (k = 0; k < col; k++)
                matrix[j][k] = matrix[j][k] - scale * matrix[i][k];
        }
    }

    for (i = row - 1; i >= 0; i--)
    {
        if (index[i] < 0)
            continue;

        p = pivot[index[i]];

        if (!matrix[index[i]][p].one())
        {
            scale = matrix[index[i]][p];
            for (k = p; k < col; k++)
                matrix[index[i]][k] = matrix[index[i]][k] / scale;
        }

        for (j = i - 1; j >= 0; j--)
        {
            if (index[j] < 0 || matrix[index[j]][p].zero())
                continue;

            scale = matrix[index[j]][p] / matrix[index[i]][p];
            for (k = p; k < col; k++)
                matrix[index[j]][k] = matrix[index[j]][k] - scale * matrix[index[i]][k];
        }
    }

    for (i = 0; i < col; i++)
    {
        if (find(pivot.begin(), pivot.end(), i) == pivot.end())
            freevars.push_back(i);
    }
}
void LinearEqutionsSolver::solve()
{
    solution.clear();

    int lcm,i;
    QNumber q(0);
    std::vector<QNumber> vec;

    rref();

    for (auto& freevar : freevars)
    {
        lcm = 1;
        vec.clear();
        for (i = 0; i < matrix[0].size(); i++)
        {
            if (i < freevar)
            {
                auto it = find(pivot.begin(), pivot.end(), i);
                if (it != pivot.end())
                {
                    q = -matrix[distance(pivot.begin(), it)][freevar];
                    lcm *= q.getDenominator() / std::__gcd(q.getDenominator(), lcm);
                    vec.push_back(q);
                }
                else
                    vec.push_back(QNumber(0));
            }
            else if (i == freevar)
                vec.push_back(QNumber(1));
            else
                vec.push_back(QNumber(0));
        }

        for (auto& v : vec)
            v = v * lcm;

        solution.push_back(vec);
    }
}