#include <bits/stdc++.h>
#include "NN.hpp"
#include "matrix.hpp"
#include "GA.hpp"

std::vector<std::pair<int, std::vector<int>>> load_data(int);

int main()
{
    srand((unsigned)time(NULL));

    NN NeuralNetwork(std::vector<int>{28 * 28, 50, 10}, 100);
    GA WeightBias(28 * 28 * 50 + 50 * 10 + 50 + 10, 1000);

    WeightBias.MakeFirstGenome();
    int generation = 0;

    while (generation < 100000)
    {
        NeuralNetwork.InputX(load_data(100));
        WeightBias.CalcScore(NeuralNetwork);
        WeightBias.ScoreSortDec();

        std::cout << WeightBias.genome[0].score << std::endl;
        for (int i = 0; i < WeightBias.Length; i++)
        {
            std::cout << std::fixed << std::setprecision(19) << WeightBias.genome[0].Chromosome[i] << " ";
        }
        std::cout << std::endl;

        std::cerr << generation << "¢‘ã " << WeightBias.genome[0].score << std::endl;

        WeightBias.CreateNewGeneration(1, 900, 99);

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

    std::vector<int> laern_data_num(60000);
    for (int i = 0; i < 60000; i++)
    {
        laern_data_num[i] = i;
    }
    for (int i = 0; i < 60000; i++)
    {
        srand((unsigned int)time(NULL));
        std::swap(laern_data_num[i], laern_data_num[rand() % 60000]);
    }
    
    for (int i = 0; i < batch_num; i++)
    {

        for (int j = 0; j < 28 * 28; j++)
        {
            ret[i].second.push_back((unsigned char)data_f[laern_data_num[i] * 28 * 28 + j + 16]);
        }
    }

    label_f.seekg(0, std::ios::end);
    long long int size_l = label_f.tellg();
    label_f.seekg(0);
    char *data_l = new char[size_l];
    label_f.read(data_l, size_l);

    for (int i = 0; i < batch_num; i++)
    {
        if(i == batch_num)break;
        ret[i].first = data_l[laern_data_num[i] + 8];
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