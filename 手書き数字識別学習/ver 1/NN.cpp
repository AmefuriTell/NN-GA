#include "NN.hpp"

NN::NN()
{
}
NN::NN(std::vector<int> l)
{
    batch_size = 1;
    layer_num = l;
    init();
}
NN::NN(std::vector<int> l, int batch)
{
    batch_size = batch;
    layer_num = l;
    init();
}
NN::~NN()
{
}

void NN::init()
{
    X.mat.resize(batch_size);
    for (int i = 0; i < batch_size; i++)
    {
        X.mat[i].resize(layer_num[0]);
    }
    B.resize(layer_num.size() - 1);
    W.resize(layer_num.size() - 1);
    for (int i = 1; i < layer_num.size(); i++)
    {
        B[i - 1].mat.resize(batch_size);
        for (int j = 0; j < batch_size; j++)
        {
            B[i - 1].mat[j].resize(layer_num[i]);
        }

        W[i - 1].mat.resize(layer_num[i - 1]);
        for (int j = 0; j < layer_num[i - 1]; j++)
        {
            W[i - 1].mat[j].resize(layer_num[i]);
        }
    }
}

void NN::InputX()
{
    std::cout << "入力層 : " << batch_size << " * " << layer_num[0] << std::endl;
    for (int j = 0; j < batch_size; j++)
    {
        for (int i = 0; i < layer_num[0]; i++)
        {
            std::cin >> X.mat[j][i];
        }
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
        for (int j = 1; j < batch_size; j++)
        {
            B[i].mat[j] = B[i].mat[0];
        }
        
        B[i].Print();
    }
    return;
}
void NN::InputX(std::vector<std::pair<int, std::vector<double>>> in)
{
    ans_data = in;
    for (int i = 0; i < batch_size; i++)
    {
        for (int j = 0; j < layer_num[0]; j++)
        {
            X.mat[i][j] = ans_data[i].second[j];
        }
    }
    
    return;
}
void NN::InputWB(std::vector<double> chromo)
{
    int count = 0;
    for (int i = 0; i < layer_num.size() - 1; i++)
    {
        for (int j = 0; j < layer_num[i]; j++)
        {
            for (int k = 0; k < layer_num[i + 1]; k++)
            {
                W[i].mat[j][k] = chromo[count];
                count++;
            }
        }
    }
    
    for (int i = 0; i < layer_num.size() - 1; i++)
    {
        for (int j = 0; j < layer_num[i + 1]; j++)
        {
            B[i].mat[0][j] = chromo[count];
            count++;
        }
        for (int j = 1; j < batch_size; j++)
        {
            B[i].mat[j] = B[i].mat[0];
        }
    }

    return;
}

double NN::sigmoid(double x)
{
    return 1.0L / (1.0L + exp(-x));
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
double NN::relu(double x)
{
    if(x > 0)return x;
    return 0.0;
}
matrix NN::relu(matrix x)
{
    for (int i = 0; i < x.mat.size(); i++)
    {
        for (int j = 0; j < x.mat[i].size(); j++)
        {
            x.mat[i][j] = relu(x.mat[i][j]);
        }
    }
    return x;
}
matrix NN::identity_function(matrix x)
{
    return x;
}
matrix NN::softmax(matrix x)
{
    matrix ret = x;
    for (int i = 0; i < batch_size; i++)
    {
        double denominator = 0, maxi = x.mat[i][0];
        for (int j = 1; j < 10; j++)maxi = std::max(maxi, x.mat[i][j]);
        
        for (int j = 0; j < 10; j++)
        {
            denominator += exp(x.mat[i][j] - maxi);
        }
        for (int j = 0; j < 10; j++)
        {
            ret.mat[i][j] = exp(x.mat[i][j] - maxi) / denominator;
        }
    }
    return ret;
}
void NN::CalcNN()
{
    matrix Z = X, A;
    for (int i = 0; i < layer_num.size() - 1; i++)
    {
        A = Z * W[i] + B[i];
        Z = relu(A);
    }
    Y = identity_function(A);
    Y = softmax(Y);

    return;
}
double NN::LossFunction()
{

    double d = 0.0000001;
    double ret = 0;
    for (int i = 0; i < batch_size; i++)
    {
        ret -= log(Y.mat[i][ans_data[i].first] + d);
    }
    return ret;

/*
    long double ret = 0;
    for (int i = 0; i < batch_size; i++)
    {
        for (int j = 0; j < Y.mat[i].size(); j++)
        {
            if(ans_data[i].first == j)ret += (Y.mat[i][j] - 1) * (Y.mat[i][j] - 1);
            else ret += Y.mat[i][j] * Y.mat[i][j];
        }
    }
    return ret;
*/
}

void NN::PrintLayerNumber()
{
    for (int i = 0; i < layer_num.size(); i++)
    {
        std::cout << layer_num[i] << " ";
    }
    std::cout << std::endl;
}
