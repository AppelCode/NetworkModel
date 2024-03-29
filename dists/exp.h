#ifndef EXP_H
#define EXP_H

#include "uniform.h"

class Exp {
    public:
        Exp(double,int);
        double generate();
    private:
        Uniform uniform_dist;
        double n;
        double lambda;
};

#endif