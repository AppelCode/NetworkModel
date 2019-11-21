#ifndef ERLANG_H
#define ERLANG_H

#include "uniform.h"

class Erlang {
    public:
        Erlang(double,int,int);
        double generate();
    private:
        Uniform uniform_dist;
        double num;
        double lambda;
        int k;
};

#endif