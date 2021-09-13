#ifndef MINST_H
#define MINST_H

#include <bits/stdc++.h>

class MINST
{
    public:
        MINST();
        ~MINST();

        void LoadData(char*, int);
        void LoadAns(char*, int);

        int ans;
        std::vector<long double> data;
};

#endif