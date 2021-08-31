#ifndef NN_H
#define NN_H

#include <bits/stdc++.h>
#include "matrix.hpp"

class NN
{
    public:
    //変数
    std::vector<int> layer_num;
    matrix X, Y;
    std::vector<matrix> W, B;


    //コンストラクタ
    NN();
    NN(std::vector<int>);
    ~NN();

    //関数
    void InputX();
    void InputBias();
    void InputWeight();
    long double sigmoid(long double);
    matrix sigmoid(matrix);
    matrix identity_function(matrix);
    void CalcNN();
    void PrintLayerNumber();

    private:
    
};

#endif