#ifndef IND_H
#define IND_H

#include <bits/stdc++.h>

//流用する際書き換えるポイント
/*
1. 染色体の型
2. 染色体の初期値
3. 染色体の突然変異
4. 評価値計算
*/

class Individual
{
    public:
        Individual();
        Individual(int, int, int, int, long double);
        ~Individual();

        void create_now_chromo();//完全新種を作成
        void evaluate();//評価値を算出
        void crossover(Individual&, Individual&);//交叉
        void mutate();//突然変異

        int GEN_MAX, POP_SIZE, ELIET, CHROMO_SIZE;
        long double MUTATE_PROB;
        std::vector<long double> chromo;
        long double score;
    private:
        void init(int, int, int, int, long double);
};

#endif