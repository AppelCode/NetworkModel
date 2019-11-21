#include "uniform.h"

Uniform::Uniform(int s) {
    this->rn = s;
}

void Uniform::setSeed(int s){
    this->seed = s;
}

double Uniform::generate(){
    this->rn = (a*rn)%m;
    this->uni_num = (double) this->rn/m;
    return this->uni_num;
}