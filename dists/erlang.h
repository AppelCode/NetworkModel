#ifndef ERLANG_H
#define ERLANG_H

#include "uniform.h"
#include <random>

class Erlang {
    public:
        Erlang(double,int,int);
        double generate();
        std::default_random_engine gen;
        std::gamma_distribution<double> distribution;
    private:
        Uniform uniform_dist;
        double num;
        double lambda;
        int k;
};

#endif