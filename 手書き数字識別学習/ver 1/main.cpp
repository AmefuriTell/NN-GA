#include <bits/stdc++.h>

#include "Individual.hpp"
#include "Population.hpp"
#include "matrix.hpp"
#include "NN.hpp"
#include "MINST.hpp"
#include "MINSTs.hpp"

int main()
{
    //乱数初期化
    srand((unsigned int)time(NULL));

    //学習用データ
    MINSTs minsts(60000);

    //NNの用意
    NN NeuralNetwork(std::vector<int>{28 * 28, 50, 10}, 100);
    NeuralNetwork.InputX(minsts.RandomGetMINSTBatch(100));
    Population WeightBias(10000, 1000, 1, 28 * 28 * 50 + 50 * 10 + 50 + 10, 0.02, NeuralNetwork);

    int generation = 10000;

    std::cerr << "start!" << std::endl;

    while (true)
    {
        NeuralNetwork.InputX(minsts.RandomGetMINSTBatch(100));
        WeightBias.alternate(NeuralNetwork);
        if(WeightBias.NowInd[0].score <= 0.2) break;
    }
    
}