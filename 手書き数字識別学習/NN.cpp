#include "NN.hpp"

NN::NN()
{
}
NN::NN(std::vector<int> l)
{
    layer_num = l;
    X.mat.resize(1);
    X.mat[0].resize(layer_num[0]);
    B.resize(layer_num.size() - 1);
    W.resize(layer_num.size() - 1);
    for (int i = 1; i < layer_num.size(); i++)
    {
        B[i - 1].mat.resize(1);
        B[i - 1].mat[0].resize(layer_num[i]);

        W[i - 1].mat.resize(layer_num[i - 1]);
        for (int j = 0; j < layer_num[i - 1]; j++)
        {
            W[i - 1].mat[j].resize(layer_num[i]);
        }
    }
}

NN::~NN()
{
}

void NN::InputX()
{
    std::cout << "入力層 : " << layer_num[0] << std::endl;
    for (int i = 0; i < layer_num[0]; i++)
    {
        std::cin >> X.mat[0][i];
    }
    X.Print();
    return;
}
void NN::InputWeight()
{
    for (int i = 0; i < layer_num.size() - 1; i++)
    {
        std::cout << "重み" << i + 1 << " : " << layer_num[i] << " * " << layer_num[i + 1] << std::endl;
        for (int j = 0; j < layer_num[i]; j++)
        {
            for (int k = 0; k < layer_num[i + 1]; k++)
            {
                std::cin >> W[i].mat[j][k];
            }
        }
        W[i].Print();
    }
    return;
}
void NN::InputBias()
{
    for (int i = 0; i < layer_num.size() - 1; i++)
    {
        std::cout << "バイアス" << i + 1 << " : " <<  layer_num[i + 1] << std::endl;
        for (int j = 0; j < layer_num[i + 1]; j++)
        {
            std::cin >> B[i].mat[0][j];
        }
        B[i].Print();
    }
    return;
}

long double NN::sigmoid(long double x)
{
    return 1.0L / (1.0L + expl(-x));
}
matrix NN::sigmoid(matrix x)
{
    matrix ans = x;
    for (int i = 0; i < x.mat.size(); i++)
    {
        for (int j = 0; j < x.mat[i].size(); j++)
        {
            ans.mat[i][j] = sigmoid(x.mat[i][j]);
        }
    }
    return ans;
}
matrix NN::identity_function(matrix x)
{
    return x;
}
void NN::CalcNN()
{
    matrix Z = X, A;
    for (int i = 0; i < layer_num.size() - 1; i++)
    {
        A = Z * W[i] + B[i];
        Z = sigmoid(A);
    }
    
    Y = identity_function(A);
}

void NN::PrintLayerNumber()
{
    for (int i = 0; i < layer_num.size(); i++)
    {
        std::cout << layer_num[i] << " ";
    }
    std::cout << std::endl;
}
