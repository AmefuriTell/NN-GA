#ifndef POP_H
#define POP_H

#include <bits/stdc++.h>
#include "Individual.hpp"

class Population
{
    public:
        Population();
        Population(int, int, int, int, long double);
        ~Population();

        void alternate();

        std::vector<Individual> NowInd, NextInd;

        int POP_SIZE, ELITE;
    private:
        void init(int, int, int, int, long double);
        void evaluate();
        int select();
};

#endif