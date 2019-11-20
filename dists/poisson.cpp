#include "poisson.h"

Poisson::Poisson(double lambda):exp_dist(lambda) {
    //do nothing
}

double Poisson::generate() {
    double temp = this->exp_dist.generate();
    double cur_delta_time = 0;
    int num_arrivals = 0;
    if (temp <= this->delta_T) {
        while (cur_delta_time < delta_T) {
            num_arrivals++;
            cur_delta_time += temp;
            temp = this->exp_dist.generate();
        }
    }
    return num_arrivals;
}