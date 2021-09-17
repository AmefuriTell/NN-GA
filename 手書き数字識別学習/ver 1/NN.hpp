#ifndef NN_H
#define NN_H

#include <bits/stdc++.h>
#include "matrix.hpp"

class NN
{
    public:
    //変数
    std::vector<int> layer_num;
    int batch_size;
    std::vector<std::pair<int, std::vector<double>>> ans_data;
    matrix X, Y;
    std::vector<matrix> W, B;


    //コンストラクタ
    NN();
    NN(std::vector<int>);
    NN(std::vector<int>, int);
    ~NN();

    //関数
    void init();
    void InputX();
    void InputX(std::vector<std::pair<int, std::vector<double>>>);
    void InputBias();
    void InputWeight();
    void InputWB(std::vector<double>);
    double sigmoid(double);
    matrix sigmoid(matrix);
    double relu(double);
    matrix relu(matrix);
    matrix identity_function(matrix);
    matrix softmax(matrix);
    void CalcNN();
    void PrintLayerNumber();
    double LossFunction();

    private:
    
};

#endif