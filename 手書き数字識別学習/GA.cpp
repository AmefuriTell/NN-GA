#include "GA.hpp"

GA::GA(int L, int BN)//????L???`?q?????????BN?????
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

void GA::MakeFirstGenome()//??`?q???????\?z
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


void GA::FormatScore()//?X?R?A???????
{
    for (int i = 0; i < BiontNumber; i++)genome[i].score = 0;
}
void GA::ScoreSortAsc()//?X?R?A????????\?[?g
{
    std::sort(genome.begin(), genome.end(), [](Genome& a, Genome& b) {return a.score < b.score; });
}
void GA::ScoreSortDec()//?X?R?A???~????\?[?g
{
    std::sort(genome.begin(), genome.end(), [](Genome& a, Genome& b) {return a.score > b.score; });
}

void GA::CreateNewGeneration(int SaveNum, int CrossNum, int NewNum)//SaveNum??c????CrossNum?????z????B?V??????`?q??NewNum???
{
    //????????
    std::mt19937_64 engine(rand());
    std::normal_distribution<long double> dist(0.0L, 1.0L);
    srand((unsigned int)time(NULL));

    int SaveGenomeNumber = SaveNum;
    int CrossGenomeNumber = CrossNum;
    int CreateNewGenomeNumber = NewNum;

    //?G???[?g????
    int i = 0;
    for (i = 0; i < SaveGenomeNumber; i++)
    {
        Newgenome[i].Chromosome = genome[i].Chromosome;
    }

    //????
    for (; i < SaveGenomeNumber + CrossGenomeNumber; i++)
    {
        //?I??????
        int Father = select(), Mother = select();
        while (Father < 0 || Father >= BiontNumber || Mother < 0 || Mother >= BiontNumber || Father == Mother)
        {
            Father = select();
            Mother = select();
        }
        
        //std::cout << Father << " " << BiontNumber << " " << Mother << std::endl;

        //????????
        for (int j = 0; j < Length; j++)
        {
            if(rand() % 2)Newgenome[i].Chromosome[j] = genome[Father].Chromosome[j];
            else Newgenome[i].Chromosome[j] = genome[Mother].Chromosome[j];

            //??R?ψ?
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
    //完全ランダム
    return rand() % BiontNumber;

    //ランキング方式
    int rank;
    long double prob = 0, r, denom;

    denom = BiontNumber * (BiontNumber + 1) / 2;
    r = (long double)rand() / (long double)RAND_MAX;

    for (rank = 1; rank < BiontNumber; rank++)
    {
        prob += (long double)(BiontNumber - rank + 1) / denom;
        if(r <= prob)break;
    }
    
    return rank;
}

void GA::CalcScore(NN wb)
{
    for (int i = 0; i < BiontNumber; i++)
    {
        wb.InputWB(genome[i].Chromosome);

        wb.CalcNN();
        genome[i].score = wb.LossFunction();
    }
    return;
}