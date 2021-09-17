#ifndef IND_H
#define IND_H

#include <bits/stdc++.h>
#include "NN.hpp"

//流用する際書き換えるポイント
/*
1. 染色体の型
2. 染色体の初期値
3. 染色体の突然変異
4. 評価値計算
*/

long double Uniform();
long double rand_normal(long double mu, long double sigma);

class Individual
{
    public:
        Individual();
        Individual(int, int, int, int, double);
        ~Individual();

        void create_now_chromo();//完全新種を作成
        void evaluate();//評価値を算出
        void evaluate(NN&);
        void crossover(Individual&, Individual&, NN&);//交叉
        void mutate();//突然変異

        void Annealing(int, NN&);//焼きなまし

        void Save(std::string);

        int GEN_MAX, POP_SIZE, ELIET, CHROMO_SIZE;
        double MUTATE_PROB;
        std::vector<double> chromo;
        double score;
    private:
        void init(int, int, int, int, double);
        double prob(double, double, int, int);
        double temperature(int, int);
};

#endif