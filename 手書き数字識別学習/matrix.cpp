#include "matrix.hpp"

matrix::matrix()
{

}
matrix::matrix(std::vector<std::vector<long double>> m)
{
    mat = m;
}
matrix::~matrix()
{

}

void matrix::Print()
{
    std::cout << std::fixed << std::setprecision(18);
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            std::cerr << mat[i][j] << "\t";
        }
        std::cerr << std::endl;
    }
    printf("\n");
    return;
}