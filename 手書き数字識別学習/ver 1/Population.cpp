#include "Population.hpp"


//コンストラクタ
Population::Population()
{
    NN wb;
    init(1000, 1000, 1, 1000, 0.1, wb);
}
Population::Population(int gen_max, int pop_size, int elite, int chromo_size, long double mutate_prob, NN &wb)
{
    init(gen_max, pop_size, elite, chromo_size, mutate_prob, wb);
}

//デコンストラクタ
Population::~Population()
{
}

//初期化(1回のみ)
void Population::init(int gen_max, int pop_size, int elite, int chromo_size, long double mutate_prob, NN &wb)
{
    POP_SIZE = pop_size;
    ELITE = elite;
    now_generation = 1;

    NowInd.resize(POP_SIZE);
    NextInd.resize(POP_SIZE);

    for (int i = 0; i < POP_SIZE; i++)
    {
        NowInd[i] = Individual(gen_max, pop_size, elite, chromo_size, mutate_prob);
        NextInd[i] = Individual(gen_max, pop_size, elite, chromo_size, mutate_prob);
    }

    evaluate(wb);
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

void Population::evaluate(NN &wb)
{
    for (int i = 0; i < POP_SIZE; i++)
    {
        NowInd[i].evaluate(wb);
    }

    //昇順ソート
    std::sort(NowInd.begin(), NowInd.end(), [](const Individual &a, const Individual &b)->bool{return a.score < b.score;});
    //std::cerr << NowInd[0].score << " " << NowInd[1].score << std::endl;
    return;
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
    now_generation ++;

    //評価
    evaluate();
}

void Population::alternate(NN &wb)
{

    Save("result/" + std::to_string(now_generation) + ".result");
    std::cerr << "The " << now_generation << " generation of elites was saved. score is " << NowInd[0].score << "." << std::endl;
    int i;

    //エリートを保存
    for (i = 0; i < ELITE; i++)
    {
        NextInd[i] = NowInd[i];
    }

    //交叉
    for (; i < POP_SIZE; i++)
    {
        //int father = select(), mother = select();
        int father = rand() % ELITE, mother = rand() % POP_SIZE;
        mother = select();
        while (father == mother)
        {
            //father = select();
            mother = select();

            father = rand() % ELITE;
            //mother = rand() % POP_SIZE;
        }
        
        //父と母から遺伝子を継ぐ
        NextInd[i].crossover(NowInd[mother], NowInd[father]);

        //突然変異させる
        NextInd[i].mutate();
    }

    //現世代を更新
    NowInd = NextInd;
    now_generation++;

    //評価
    evaluate(wb);
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

//最良遺伝子を出力する。
void Population::Save(std::string file_name)
{
    NowInd[0].Save(file_name);
}