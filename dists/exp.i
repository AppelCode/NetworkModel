/* distributions.i */
%module exp
%{
#include "exp.h"
%}

class Exp {
    public:
        Exp(double);
        double generate();
    private:
        Uniform uniform_dist;
        double n;
        double lambda;
};