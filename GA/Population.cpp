#include "Population.hpp"


//コンストラクタ
Population::Population()
{
    init(1000, 1000, 1, 1000, 0.1);
}
Population::Population(int gen_max, int pop_size, int elite, int chromo_size, long double mutate_prob)
{
    init(gen_max, pop_size, elite, chromo_size, mutate_prob);
}

//デコンストラクタ
Population::~Population()
{
}

//初期化(1回のみ)
void Population::init(int gen_max, int pop_size, int elite, int chromo_size, long double mutate_prob)
{
    POP_SIZE = pop_size;
    ELITE = elite;

    NowInd.resize(POP_SIZE);
    NextInd.resize(POP_SIZE);

    for (int i = 0; i < POP_SIZE; i++)
    {
        NowInd[i] = Individual(gen_max, pop_size, elite, chromo_size, mutate_prob);
        NextInd[i] = Individual(gen_max, pop_size, elite, chromo_size, mutate_prob);
    }

    evaluate();
}

//評価し、ソート
void Population::evaluate()
{
    for (int i = 0; i < POP_SIZE; i++)
    {
        NowInd[i].evaluate();
    }

    //昇順ソート
    std::sort(NowInd.begin(), NowInd.end(), [](const Individual &a, const Individual &b)->bool{return a.score < b.score;});
}

//世代交代
void Population::alternate()
{
    int i;

    //エリートを保存
    for (i = 0; i < ELITE; i++)
    {
        NextInd[i] = NowInd[i];
    }

    //交叉
    for (; i < POP_SIZE; i++)
    {
        int father = select(), mother = select();
        while (father == mother)
        {
            father = select();
            mother = select();
        }
        
        //父と母から遺伝子を継ぐ
        NextInd[i].crossover(NowInd[mother], NowInd[father]);

        //突然変異させる
        NextInd[i].mutate();
    }

    //現世代を更新
    NowInd = NextInd;

    //評価
    evaluate();
}

//交叉する親を決定する
int Population::select()
{
    int rank;
    long double prob, r = (long double)rand() / RAND_MAX;
    int denom = POP_SIZE * (POP_SIZE + 1) / 2;

    for (rank = 1; rank < POP_SIZE; rank++)
    {
        prob = (long double)(POP_SIZE - rank + 1) / denom;
        if(r >= prob)break;
        r -= prob;
    }
    
    return rank - 1;
}