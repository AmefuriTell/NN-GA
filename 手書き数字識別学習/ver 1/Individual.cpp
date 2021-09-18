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
Individual::Individual(int gen_max, int pop_size, int elite, int chromo_size, double mutate_prob)
{
    init(gen_max, pop_size, elite, chromo_size, mutate_prob);
}

//デコンストラクタ
Individual::~Individual()
{
}

//個体を初期化(各個体1回しか発動させない)
void Individual::init(int gen_max, int pop_size, int elite, int chromo_size, double mutate_prob)
{
    srand((unsigned int)time(NULL));

    GEN_MAX = gen_max;
    POP_SIZE = pop_size;
    ELIET = elite;
    CHROMO_SIZE = chromo_size;
    MUTATE_PROB = mutate_prob;

    elite_cnt = 0;

    chromo.resize(CHROMO_SIZE);
    score = 0.0;

    create_now_chromo();
}

//新種の個体を生成
void Individual::create_now_chromo()
{
    for (int i = 0; i < CHROMO_SIZE; i++)
    {
        chromo[i] = (double)(rand() % 200000) / 100000;
        if(rand() % 2)chromo[i] *= -1;
        //chromo[i] = rand_normal(0, 1.0);
    }
}

//交叉
void Individual::crossover(Individual &father, Individual &mother, NN &wb)
{
    Individual c1 = father, c2 = mother;
    //一様交叉
    for (int i = 0; i < CHROMO_SIZE; i++)
    {
        if(rand() % 2)
        {
            std::swap(c1.chromo[i], c2.chromo[i]);
        }
        //chromo[i] = (rand() % 2) ? father.chromo[i] : mother.chromo[i];
    }

    //突然変異
    //c1.Annealing(10, wb);
    //c2.Annealing(10, wb);

    c1.mutate();
    c2.mutate();

    c1.evaluate(wb);
    c2.evaluate(wb);

    *this = (c1.score < c2.score) ? c1 : c2;
    elite_cnt = 0;
}

//突然変異
void Individual::mutate()
{
    for (int i = ELIET; i < CHROMO_SIZE; i++)
    {
        if((double)rand() / RAND_MAX < MUTATE_PROB)
        {
            double d = (double)(rand() % 200000) / 100000;
            if(rand() % 2)d *= -1;
            chromo[i] += d;
            
            //chromo[i] = rand_normal(0, 1.0);
        }
    }
}

void Individual::evaluate(NN &wb)
{
    wb.InputWB(chromo);

    wb.CalcNN();
    score = wb.LossFunction();
}


//焼きなまし
void Individual::Annealing(int t, NN &wb)
{
    int now_time = 0, time_limit = t;

    Individual state = *this, new_state;
    state.evaluate(wb);
    while (now_time < time_limit)
    {
        //近傍を取る
        new_state = state;
        new_state.mutate();

        //スコア計算
        new_state.evaluate(wb);

        if(prob(state.score, new_state.score, now_time, time_limit) >= (double)rand() / RAND_MAX)
        {
            state = new_state;
        }
        now_time++;
    }

    *this = state;
}

double Individual::temperature(int now_time, int time_limit)
{
    double stemp = 20.0, etemp = 5.0;
    double x = (double)now_time / time_limit;
    return pow(stemp, 1.0 - x) * pow(etemp, x);
}

double Individual::prob(double score, double new_score, int now_time, int time_limit)
{
    double d = score - new_score;
    if(d >= 0)return 1;
    return exp(d / temperature(now_time, time_limit));
}

void Individual::Save(std::string file_name)
{
    std::ofstream outputfile(file_name);

    outputfile << std::setprecision(15) << score << "\n";
    for (int i = 0; i < CHROMO_SIZE; i++)
    {
        outputfile << std::setprecision(15) << chromo[i] << " ";
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