#ifndef POP_H
#define POP_H

#include <bits/stdc++.h>
#include "Individual.hpp"
#include "NN.hpp"

class Population
{
    public:
        Population();
        Population(int, int, int, int, double, NN&);
        ~Population();

        void alternate(NN&);

        void Save(std::string);

        std::vector<Individual> NowInd, NextInd;

        int POP_SIZE, ELITE, now_generation;
        int pop_elite_cnt;
    private:
        void init(int, int, int, int, double, NN&);
        void evaluate(NN&);
        int select();
};

#endif