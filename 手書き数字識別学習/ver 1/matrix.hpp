#ifndef MATRIX_H
#define MATRIX_H

#include <bits/stdc++.h>

using Matrix = std::vector<std::vector<double>>;
class matrix
{
    public:
    
    Matrix mat;
    
    matrix();
    matrix(Matrix);
    ~matrix();

    void Print();


    //演算
    matrix operator + (matrix);
    matrix operator * (matrix);
};

#endif