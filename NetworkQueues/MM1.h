#ifndef MM1_H
#define MM1_H

#include "Buffer.h"
#include "Customer.h"
#include "exp.h"
#include "poisson.h"
#include <map>

using namespace std;

class MM1 {
    public :
        MM1();
        MM1(double lambda,double mu);
        MM1(double lambda,double mu, double step_time);
        MM1(double lambda,double mu, double step_time,int intial_customers);
        Buffer buf_state();
        void tick();
    private:
        Buffer line;
        Exp arrival_generator;
        Exp service_generator;
        double time = 0;
        double step_time = 1;
        int num_customers = 0;
        double service_rate = 1;
        double arrival_rate = 0.5;
        double next_arrival = 0;
        double next_service = 0;
        int cur_sequence_id = 0;
        map<int,double> customer_state;
};

#endif