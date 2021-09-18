#include "Population.hpp"


//コンストラクタ
Population::Population()
{
    NN wb;
    init(1000, 1000, 1, 1000, 0.1, wb);
}
Population::Population(int gen_max, int pop_size, int elite, int chromo_size, double mutate_prob, NN &wb)
{
    init(gen_max, pop_size, elite, chromo_size, mutate_prob, wb);
}

//デコンストラクタ
Population::~Population()
{
}

//初期化(1回のみ)
void Population::init(int gen_max, int pop_size, int elite, int chromo_size, double mutate_prob, NN &wb)
{
    srand((unsigned int)time(NULL));

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

void Population::evaluate(NN &wb)
{
    for (int i = 0; i < POP_SIZE; i++)
    {
        NowInd[i].evaluate(wb);
    }

    //昇順ソート
    std::sort(NowInd.begin(), NowInd.end(), [](const Individual &a, const Individual &b)->bool{return a.score < b.score;});
}

void Population::alternate(NN &wb)
{
    Save("result/" + std::to_string(now_generation) + ".result");
    std::cerr << "The " << now_generation << " generation of elites was saved. score is " << NowInd[0].score << ". " << NowInd[0].elite_cnt << std::endl;
    
    int i;
    pop_elite_cnt = 0;
    //エリートを保存
    for (i = 0; i < ELITE; i++)
    {
        NowInd[i].elite_cnt++;
    }

    for (i = 0; i < ELITE; i++)
    {
        NowInd[i].pop_elite_cnt = pop_elite_cnt;
        NextInd[i] = NowInd[i];

        NextInd[i].Annealing(pop_elite_cnt, wb);

        pop_elite_cnt = std::max(pop_elite_cnt, NowInd[i].elite_cnt);
    }
    

    //交叉
    for (; i < POP_SIZE; i++)
    {
        NextInd[i].pop_elite_cnt = pop_elite_cnt;
        int father = select(), mother = select();
        //int father = rand() % ELITE, mother = rand() % POP_SIZE;
        while (father == mother)
        {
            father = select();
            mother = select();

            //father = rand() % ELITE;
            //mother = rand() % POP_SIZE;
        }
        
        //父と母から遺伝子を継ぐ(遺伝子交配とともに、突然変異させる。)
        NextInd[i].crossover(NowInd[mother], NowInd[father], wb);
    }

    //現世代を更新
    NowInd = NextInd;
    now_generation++;

    //評価
    //evaluate(wb);
    std::sort(NowInd.begin(), NowInd.end(), [](const Individual &a, const Individual &b)->bool{return a.score < b.score;});
}

//交叉する親を決定する
int Population::select()
{

    int rank;
    double prob = 0.0, r = (double)rand() / RAND_MAX;
    int denom = POP_SIZE * (POP_SIZE + 1) / 2;

    for (rank = 1; rank < POP_SIZE; rank++)
    {
        prob += (double)(POP_SIZE - rank + 1) / denom;
        if(r <= prob)break;
    }
    
    return rank - 1;
}

//最良遺伝子を出力する。
void Population::Save(std::string file_name)
{
    NowInd[0].Save(file_name);
}