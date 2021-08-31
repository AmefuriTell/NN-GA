#ifndef NN_H
#define NN_H

#include <bits/stdc++.h>
#include "matrix.hpp"

class NN
{
    public:
    //�ϐ�
    std::vector<int> layer_num;
    int batch_size;
    std::vector<std::pair<int, std::vector<int>>> ans_data;
    matrix X, Y;
    std::vector<matrix> W, B;


    //�R���X�g���N�^
    NN();
    NN(std::vector<int>);
    NN(std::vector<int>, int);
    ~NN();

    //�֐�
    void init();
    void InputX();
    void InputX(std::vector<std::pair<int, std::vector<int>>>);
    void InputBias();
    void InputWeight();
    void InputWB(std::vector<long double>);
    long double sigmoid(long double);
    matrix sigmoid(matrix);
    matrix identity_function(matrix);
    void CalcNN();
    void PrintLayerNumber();
    long double LossFunction();

    private:
    
};

#endif