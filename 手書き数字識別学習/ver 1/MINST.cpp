#include <bits/stdc++.h>
#include "MINST.hpp"

MINST::MINST()
{
    ans = -1;
    data.resize(28 * 28);

    return;
}

MINST::~MINST()
{
    
}

void MINST::LoadData(char *data_f, int i)
{

    for (int j = 0; j < 28 * 28; j++)
    {
        data[j] = (double)((unsigned char)data_f[i * 28 * 28 + j + 16]) / 255.0;
    }
}

void MINST::LoadAns(char *data_f, int i)
{
    ans = data_f[i + 8];
}