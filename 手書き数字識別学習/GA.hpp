#ifndef GA_H
#define GA_H

#include <bits/stdc++.h>
#include "NN.hpp"

typedef struct
{
    //std::vector<char> Chromosome;
    std::vector<long double> Chromosome;
    long double score;
}Genome;

class GA
{
public:
    std::vector<Genome> genome;
    std::vector<Genome> Newgenome;
    int Length;
    int BiontNumber;
    GA(int, int);
    void MakeFirstGenome();

    void CalcScore();
    void CalcScore(NN);

    void FormatScore();
    void ScoreSortAsc();
    void ScoreSortDec();

    void CreateNewGeneration(int, int, int);
    int Fatherselect();
    int Motherselect();
};

#endif