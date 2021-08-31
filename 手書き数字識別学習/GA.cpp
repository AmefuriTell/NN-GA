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

    std::mt19937_64(std::random_device{}());
    std::normal_distribution<> dist(0.0L,1.0L);

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
    std::mt19937_64(std::random_device{}());
    std::normal_distribution<> dist(0.0L,1.0L);
    srand((unsigned int)time(NULL));

    int SaveGenomeNumber = SaveNum;
    int CrossGenomeNumber = CrossNum;
    int CreateNewGenomeNumber = NewNum;

    int ChildlenNum = 0;
    for (int i = 0; i < SaveGenomeNumber; i++)
    {
        Newgenome[i].Chromosome = genome[i].Chromosome;
        ChildlenNum++;
    }

    for (int i = 0; i < CrossGenomeNumber / 2; i++)
    {
        int Father = 0, Mother = 0;
        do
        {
            Father = rand() % SaveNum;
            Mother = rand() % BiontNumber;
        } while (Father == Mother);


        Newgenome[ChildlenNum].Chromosome = genome[Father].Chromosome;
        Newgenome[ChildlenNum + 1].Chromosome = genome[Mother].Chromosome;

        for (int j = 0; j < Length; j++)
        {
            if (rand() % 2 == 0)
            {
                Newgenome[ChildlenNum].Chromosome[j] = genome[Mother].Chromosome[j];
                Newgenome[ChildlenNum + 1].Chromosome[j] = genome[Father].Chromosome[j];
            }
        }
        ChildlenNum += 2;
    }

    for (int i = 0; i < CreateNewGenomeNumber; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            Newgenome[ChildlenNum].Chromosome[j] = dist(engine);
        }
        ChildlenNum++;
    }

    for (int i = 0; i < BiontNumber; i++)
    {
        genome[i] = Newgenome[i];
    }
}
