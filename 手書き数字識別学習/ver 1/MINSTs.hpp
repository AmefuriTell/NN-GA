#ifndef MINSTS_H
#define MINSTS_H

#include <bits/stdc++.h>
#include "MINST.hpp"

class MINSTs
{
    public:
        MINSTs(int);
        void LoadMINSTs();
        MINST RandomGetMINST();
        std::vector<std::pair<int, std::vector<double>>> RandomGetMINSTBatch(int);

        int size;
        std::vector<MINST> minsts;
};

#endif