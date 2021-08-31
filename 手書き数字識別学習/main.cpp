#include <bits/stdc++.h>
#include "NN.hpp"
#include "matrix.hpp"

int main()
{
    NN NeuralNetwork(std::vector<int>{2, 3, 2, 2});
    NeuralNetwork.PrintLayerNumber();
    NeuralNetwork.InputX();
    NeuralNetwork.InputWeight();
    NeuralNetwork.InputBias();

    NeuralNetwork.CalcNN();

    std::cout << "o—Í‘w" << std::endl;
    NeuralNetwork.Y.Print();

/*
    matrix X(Matrix{{1, 0.5}});
    matrix W1(Matrix{{0.1, 0.3, 0.5}, {0.2, 0.4, 0.6}}), W2(Matrix{{0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6}}), W3(Matrix{{0.1, 0.3}, {0.2, 0.4}});
    matrix B1(Matrix{{0.1, 0.2, 0.3}}), B2(Matrix{{0.1, 0.2}}), B3(Matrix{{0.1, 0.2}});
    matrix Z1, A1, Z2, A2, Y, A3;

    X.Print();
    A1 = X * W1;
    A1.Print();
    A1 = A1 + B1;
    A1.Print();
*/
}