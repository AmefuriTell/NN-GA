#include "MINSTs.hpp"

MINSTs::MINSTs(int s)
{
    size = s;
    minsts.resize(size);

    LoadMINSTs();
}

void MINSTs::LoadMINSTs()
{
    std::string images_file_path = "MINST/train/images/images";
    std::ifstream images_f(images_file_path, std::ios::binary);
    images_f.seekg(0, std::ios::end);
    long long int size_i_f = images_f.tellg();

    images_f.seekg(0);
    char *data_i_f = new char[size_i_f];
    images_f.read(data_i_f, size_i_f);

    std::string labels_file_path = "MINST/train/labels/labels";
    std::ifstream labels_f(labels_file_path, std::ios::binary);
    labels_f.seekg(0, std::ios::end);
    long long int size_l_f = labels_f.tellg();
    labels_f.seekg(0);
    char *data_l_f = new char[size_l_f];
    labels_f.read(data_l_f, size_l_f);

    for (int i = 0; i < size; i++)
    {
        minsts[i].LoadData(data_i_f, i);
        minsts[i].LoadAns(data_l_f, i);
    }

    delete data_i_f;
    delete data_l_f;
}

MINST MINSTs::RandomGetMINST()
{
    return minsts[rand() % size];
}

std::vector<std::pair<int, std::vector<long double>>> MINSTs::RandomGetMINSTBatch(int batch)
{
    std::vector<std::pair<int, std::vector<long double>>> ret(batch);
    for (int i = 0; i < batch; i++)
    {
        MINST d = RandomGetMINST();
        ret[i].first = d.ans;
        ret[i].second = d.data;
    }
    return ret;
}