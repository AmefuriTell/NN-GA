#include <bits/stdc++.h>
#include "NN.hpp"
#include "matrix.hpp"
#include "GA.hpp"

void GA::CalcScore(NN wb)
{
    for (int i = 0; i < BiontNumber; i++)
    {
        wb.InputWB(genome[i].Chromosome);
        wb.CalcNN();
        genome[i].score = wb.LossFunction();
        std::cerr << i << " " << genome[i].score << std::endl;
    }
    return;
}

std::vector<std::pair<int, std::vector<int>>> load_data(int);

int main()
{
    srand((unsigned)time(NULL));

    std::vector<std::pair<int, std::vector<int>>> data = load_data(100);

    NN NeuralNetwork(std::vector<int>{28 * 28, 50, 10}, 100);
    NeuralNetwork.InputX(data);

    GA WeightBias(28 * 28 * 50 + 50 * 10 + 50 + 10, 100);
    WeightBias.MakeFirstGenome();
    int generation = 0;

    while (generation < 100000)
    {
        WeightBias.CalcScore(NeuralNetwork);
        WeightBias.ScoreSortAsc();

        std::cout << WeightBias.genome[0].score << std::endl;
        for (int i = 0; i < WeightBias.Length; i++)
        {
            std::cout << std::fixed << std::setprecision(19) << WeightBias.genome[0].Chromosome[i] << " ";
        }
        std::cout << std::endl;

        WeightBias.CreateNewGeneration(5, 60, 35);

        generation++;
    }
    
}

std::vector<std::pair<int, std::vector<int>>> load_data(int batch_num)
{
    std::string images_file_path = "MNIST/images", labels_file_path = "MNIST/labels";
    std::vector<std::pair<int, std::vector<int>>> ret(batch_num);

    std::ifstream image_f(images_file_path, std::ios::binary);
    std::ifstream label_f(labels_file_path, std::ios::binary);

    image_f.seekg(0, std::ios::end);
    long long int size_f = image_f.tellg();
    image_f.seekg(0);
    char *data_f = new char[size_f];
    image_f.read(data_f, size_f);

    for (int i = 0; i < size_f - 16; i++)
    {
        if(i / (28 * 28) == batch_num)break;
        ret[i / (28 * 28)].second.push_back((unsigned char)data_f[i + 16]);
    }

    label_f.seekg(0, std::ios::end);
    long long int size_l = label_f.tellg();
    label_f.seekg(0);
    char *data_l = new char[size_l];
    label_f.read(data_l, size_l);

    for (int i = 0; i < size_l - 8; i++)
    {
        if(i == batch_num)break;
        ret[i].first = data_l[i + 8];
    }
/*
    for (int i = 0; i < batch_num; i++)
    {
        std::cout << ret[i].first << std::endl;
        for (int j = 0; j < ret[i].second.size(); j++)
        {
            std::cout << ret[i].second[j] << "\t";
            if(j % 28 == 27)std::cout << std::endl;
        }
        std::cout << std::endl;
    }
*/

    delete data_l;
    delete data_f;
    
    return ret;
}