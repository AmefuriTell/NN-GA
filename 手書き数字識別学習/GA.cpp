#include "GA.hpp"

GA::GA(int L, int BN)//長さLの遺伝子をもつ個体をBN個生成
{
    srand((unsigned int)time(NULL));
    Length = L;
    BiontNumber = BN;
    genome.resize(BiontNumber);
    Newgenome.resize(BiontNumber);
    for (int i = 0; i < BiontNumber; i++)
    {
        genome[i].Chromosome.resize(Length);
        Newgenome[i].Chromosome.resize(Length);
    }
}

void GA::MakeFirstGenome()//遺伝子を最初に構築
{

    std::mt19937_64 engine(rand());
    std::normal_distribution<long double> dist(0.0L, 1.0L);

    FormatScore();
    for (int i = 0; i < BiontNumber; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            genome[i].Chromosome[j] = dist(engine);
        }
    }
}


void GA::FormatScore()//スコアの初期化
{
    for (int i = 0; i < BiontNumber; i++)genome[i].score = 0;
}
void GA::ScoreSortAsc()//スコアを昇順にソート
{
    std::sort(genome.begin(), genome.end(), [](Genome& a, Genome& b) {return a.score < b.score; });
}
void GA::ScoreSortDec()//スコアを降順にソート
{
    std::sort(genome.begin(), genome.end(), [](Genome& a, Genome& b) {return a.score > b.score; });
}

void GA::CreateNewGeneration(int SaveNum, int CrossNum, int NewNum)//SaveNum体残してCrossNum体を交配で作成。新しい遺伝子をNewNum体作成
{
    //乱数生成
    std::mt19937_64 engine(rand());
    std::normal_distribution<long double> dist(0.0L, 1.0L);
    srand((unsigned int)time(NULL));

    int SaveGenomeNumber = SaveNum;
    int CrossGenomeNumber = CrossNum;
    int CreateNewGenomeNumber = NewNum;

    //エリートを保存
    int i = 0;
    for (i = 0; i < SaveGenomeNumber; i++)
    {
        Newgenome[i].Chromosome = genome[i].Chromosome;
    }

    //交差
    for (; i < BiontNumber - CreateNewGenomeNumber; i++)
    {
        //選択する
        int Father = select(), Mother = select();

        //交差する
        for (int j = 0; j < BiontNumber; j++)
        {
            if(rand() % 2)Newgenome[i].Chromosome[j] = genome[Father].Chromosome[j];
            else Newgenome[i].Chromosome[j] = genome[Mother].Chromosome[j];

            //突然変異
            if (rand() % 100 < 2)Newgenome[i].Chromosome[j] = dist(engine);
        }
    }

    for (; i < BiontNumber; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            Newgenome[i].Chromosome[j] = dist(engine);
        }
    }

    for (int i = 0; i < BiontNumber; i++)
    {
        genome[i] = Newgenome[i];
    }
}

int GA::select()
{
    int rank, denom;
    long double prob, r;

    denom = BiontNumber * (BiontNumber + 1) / 2;
    r = (long double)rand() / (long double)RAND_MAX;

    for (rank = 0; rank < BiontNumber; rank++)
    {
        prob = (long double)(BiontNumber - rank + 1) / denom;
        if(r <= prob)break;
        r -= prob;
    }
    
    return rank - 1;
}