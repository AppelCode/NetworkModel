#include "uniform.h"
#include "erlang.h"
#include <bits/stdc++.h>


using namespace std;
Erlang::Erlang(double lambda,int k,int s): uniform_dist(s), distribution(k,1/lambda){
    this->lambda = lambda;
    this->k = k;
}

double Erlang::generate(){

    double pi = 0;
    double temp = 0;

    pi = temp;

    for (int i = 1; i <= this->k ; i++){
        temp = (double)rand()/(RAND_MAX);
        if (i==1) {
            pi = temp;
        } else {
            //multiply cuyrrent genrated with previous
            pi = pi*(temp);
        }
    }
    this->num = (-1/this->lambda) * log(pi);
    //temp = distribution(gen); //used to check

    return this->num;
}