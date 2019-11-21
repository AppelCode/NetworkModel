#ifndef UNIFORM_H
#define UNIFORM_H

class Uniform {
    public:
        Uniform(int);
        void setSeed(int);
        double generate();
    private:
        int seed;
        long int rn;
        double uni_num = 0;
        long int m = 1000000;
        long int a = 45652;
};

#endif