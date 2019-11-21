#ifndef POISSON_H
#define POISSON_H

#include "exp.h"

class Poisson {
    public:
        Poisson(double,int);
        double generate();
    private:
        Exp exp_dist;
        int n;
        double lambda;
        double delta_T = 1;
};

#endif