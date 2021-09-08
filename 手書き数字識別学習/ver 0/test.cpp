#include <bits/stdc++.h>
#include "NN.hpp"
#include "matrix.hpp"

std::vector<std::pair<int, std::vector<int>>> load_data(int);

int main()
{
    NN NeuralNetwork(std::vector<int>{28 * 28, 50, 10}, 10000);
    NeuralNetwork.InputX(load_data(10000));
    
    std::vector<long double> WB(28 * 28 * 50 + 50 * 10 + 50 + 10);
    for (int i = 0; i < 28 * 28 * 50 + 50 * 10 + 50 + 10; i++)
    {
        std::cin >> WB[i];
    }
    NeuralNetwork.InputWB(WB);
    NeuralNetwork.CalcNN();

    std::vector<int> count(2, 0);
    std::vector<int> number_kind(10, 0);
    std::vector<int> each_number_c(10, 0), hand_num_count(10, 0);
    for (int i = 0; i < 10000; i++)
    {
        int maxi = 0;
        for (int j = 0; j < 10; j++)
        {
            if(NeuralNetwork.Y.mat[i][j] > NeuralNetwork.Y.mat[i][maxi])
            {
                maxi = j;
            }
        }
        std::cerr << maxi << " " << NeuralNetwork.ans_data[i].first << std::endl;
        count[(maxi == NeuralNetwork.ans_data[i].first)]++;

        number_kind[NeuralNetwork.ans_data[i].first]++;
        hand_num_count[maxi]++;
        if(maxi == NeuralNetwork.ans_data[i].first)
        {
            each_number_c[maxi]++;
        }
    }
    
    std::cout << "　正解 : " << count[1] << "回" << std::endl;
    std::cout << "不正解 : " << count[0] << "回" << std::endl;

    std::cout << std::endl;

    for (int i = 0; i < 10; i++)
    {
        std::cout << i << "の総数と正解数 : " << each_number_c[i] << " / " <<  number_kind[i] << " : " << (long double)each_number_c[i] / number_kind[i] * 100.0L << "%" << " : " << hand_num_count[i] << std::endl;
    }


    
}

std::vector<std::pair<int, std::vector<int>>> load_data(int batch_num)
{
    std::string images_file_path = "MNIST/test/images", labels_file_path = "MNIST/test/labels";
    std::vector<std::pair<int, std::vector<int>>> ret(batch_num);

    std::ifstream image_f(images_file_path, std::ios::binary);
    std::ifstream label_f(labels_file_path, std::ios::binary);

    image_f.seekg(0, std::ios::end);
    long long int size_f = image_f.tellg();
    image_f.seekg(0);
    char *data_f = new char[size_f];
    image_f.read(data_f, size_f);

    std::vector<int> laern_data_num(10000);
    for (int i = 0; i < 10000; i++)
    {
        laern_data_num[i] = i;
    }
    for (int i = 0; i < 10000; i++)
    {
        srand((unsigned int)time(NULL));
        std::swap(laern_data_num[i], laern_data_num[rand() % 10000]);
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