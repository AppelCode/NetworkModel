#ifndef MM1_H
#define MM1_H

#include "Buffer.h"
#include "Customer.h"
#include "exp.h"
#include "poisson.h"
#include "erlang.h"
#include <map>

using namespace std;

class MM1 {
    public :
        MM1(double lambda,double mu);
        Buffer buf_state();
        double expected_wait();
        map<int,double> customer_state;
        void tick();
        Buffer line;
    private:

        Exp arrival_generator;
        Exp service_generator;
        double time = 0;
        double step_time = 1;
        int num_customers = 0;
        double service_rate = 6;
        double arrival_rate = 5;
        double next_arrival = 0;
        double next_service = 0;
        int cur_sequence_id = 0;
        int last_sid_served = 0;
        double total_wait = 0;
};

#endif