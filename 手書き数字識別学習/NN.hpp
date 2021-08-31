#ifndef NN_H
#define NN_H

#include <bits/stdc++.h>
#include "matrix.hpp"

class NN
{
    public:
    //�ϐ�
    std::vector<int> layer_num;
    matrix X, Y;
    std::vector<matrix> W, B;


    //�R���X�g���N�^
    NN();
    NN(std::vector<int>);
    ~NN();

    //�֐�
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