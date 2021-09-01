#include "GA.hpp"

GA::GA(int L, int BN)//����L�̈�`�q�����̂�BN����
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

void GA::MakeFirstGenome()//��`�q���ŏ��ɍ\�z
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


void GA::FormatScore()//�X�R�A�̏�����
{
    for (int i = 0; i < BiontNumber; i++)genome[i].score = 0;
}
void GA::ScoreSortAsc()//�X�R�A�������Ƀ\�[�g
{
    std::sort(genome.begin(), genome.end(), [](Genome& a, Genome& b) {return a.score < b.score; });
}
void GA::ScoreSortDec()//�X�R�A���~���Ƀ\�[�g
{
    std::sort(genome.begin(), genome.end(), [](Genome& a, Genome& b) {return a.score > b.score; });
}

void GA::CreateNewGeneration(int SaveNum, int CrossNum, int NewNum)//SaveNum�̎c����CrossNum�̂���z�ō쐬�B�V������`�q��NewNum�̍쐬
{
    //��������
    std::mt19937_64 engine(rand());
    std::normal_distribution<long double> dist(0.0L, 1.0L);
    srand((unsigned int)time(NULL));

    int SaveGenomeNumber = SaveNum;
    int CrossGenomeNumber = CrossNum;
    int CreateNewGenomeNumber = NewNum;

    //�G���[�g��ۑ�
    int i = 0;
    for (i = 0; i < SaveGenomeNumber; i++)
    {
        Newgenome[i].Chromosome = genome[i].Chromosome;
    }

    //����
    for (; i < BiontNumber - CreateNewGenomeNumber; i++)
    {
        //�I������
        int Father = select(), Mother = select();

        //��������
        for (int j = 0; j < BiontNumber; j++)
        {
            if(rand() % 2)Newgenome[i].Chromosome[j] = genome[Father].Chromosome[j];
            else Newgenome[i].Chromosome[j] = genome[Mother].Chromosome[j];

            //�ˑR�ψ�
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