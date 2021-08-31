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
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    printf("\n");
    return;
}