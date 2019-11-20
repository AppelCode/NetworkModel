#include "uniform.h"
#include "exp.h"
#include <bits/stdc++.h>

using namespace std;
Exp::Exp(double lambda){
    this->lambda = lambda;
}

double Exp::generate(){
    double temp = this->uniform_dist.generate();
    this->n = (-1/this->lambda) * log(1-temp);
}