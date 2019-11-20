/* distributions.i */
%module uniform
%{
#include "uniform.h"
%}

class Uniform {
    public:
        Uniform();
        void setSeed(int);
        double generate();
    private:
        int seed = 0;
        long int rn = 2;
        double uni_num = 0;
        long int m = 1000000;
        long int a = 45652;
};