#include "Individual.hpp"

//流用する際書き換えるポイント
/*
1. 染色体の型
2. 染色体の初期値
3. 染色体の突然変異
4. 評価値計算
*/

//コンストラクタ
Individual::Individual()
{
    init(1000, 1000, 1, 1000, 0.1);
}
Individual::Individual(int gen_max, int pop_size, int elite, int chromo_size, long double mutate_prob)
{
    init(gen_max, pop_size, elite, chromo_size, mutate_prob);
}

//デコンストラクタ
Individual::~Individual()
{
}

//個体を初期化(各個体1回しか発動させない)
void Individual::init(int gen_max, int pop_size, int elite, int chromo_size, long double mutate_prob)
{
    srand((unsigned int)time(NULL));

    GEN_MAX = gen_max;
    POP_SIZE = pop_size;
    ELIET = elite;
    CHROMO_SIZE = chromo_size;
    MUTATE_PROB = mutate_prob;

    chromo.resize(CHROMO_SIZE);
    score = 0.0L;

    create_now_chromo();
}

//新種の個体を生成
void Individual::create_now_chromo()
{
    for (int i = 0; i < CHROMO_SIZE; i++)
    {
        chromo[i] = rand_normal(0, 1.0);
    }
}

//交叉
void Individual::crossover(Individual &father, Individual &mother)
{
    //一様交叉
    for (int i = 0; i < CHROMO_SIZE; i++)
    {
        chromo[i] = (rand() % 2) ? father.chromo[i] : mother.chromo[i];
    }
}

//突然変異
void Individual::mutate()
{
    for (int i = ELIET; i < CHROMO_SIZE; i++)
    {
        if((long double)rand() / RAND_MAX < MUTATE_PROB)
        {
            chromo[i] = rand_normal(0, 1.0);
        }
    }
}

//評価値を算出する(これは、コードごとに書き換える。)
void Individual::evaluate()
{

}

void Individual::evaluate(NN &wb)
{
    wb.InputWB(chromo);

    wb.CalcNN();
    score = wb.LossFunction();
}

void Individual::Save(std::string file_name)
{
    std::ofstream outputfile(file_name);

    outputfile << std::setprecision(19) << score << "\n";
    for (int i = 0; i < CHROMO_SIZE; i++)
    {
        outputfile << std::setprecision(19) << chromo[i] << " ";
    }
    
    outputfile.close();
}

//乱数関係(正規分布)
#define MY_PI 3.1415926535897932384

long double Uniform()
{
    return((long double)rand() + 1.0L) / ((long double)RAND_MAX + 2.0L);
}

long double rand_normal(long double mu, long double sigma)
{
    long double z = sqrtl(-2.0 * logl(Uniform())) * sinl(2.0 * MY_PI * Uniform());

    return mu + sigma * z;
}