#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include <bits/stdc++.h>

#define M_PI 3.1415926535897932384

long double Uniform()
{
    return((long double)rand() + 1.0L) / ((long double)RAND_MAX + 2.0L);
}

long double rand_normal(long double mu, long double sigma)
{
    long double z = sqrtl(-2.0 * logl(Uniform())) * sinl(2.0 * M_PI);

    return mu + sigma * z;
}

#endif