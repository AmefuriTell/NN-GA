#ifndef POP_H
#define POP_H

#include <bits/stdc++.h>
#include "Individual.hpp"
#include "NN.hpp"

class Population
{
    public:
        Population();
        Population(int, int, int, int, long double, NN&);
        ~Population();

        void alternate();
        void alternate(NN&);

        void Save(std::string);

        std::vector<Individual> NowInd, NextInd;

        int POP_SIZE, ELITE, now_generation;
    private:
        void init(int, int, int, int, long double, NN&);
        void evaluate();
        void evaluate(NN&);
        int select();
};

#endif