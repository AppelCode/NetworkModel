#ifndef MEK1_H
#define MEK1_H

#include "Buffer.h"
#include "Customer.h"
#include "erlang.h"
#include "exp.h"
#include <map>

using namespace std;

class MEk1 {
    public :
        MEk1(double lambda,double mu, int k);
        Buffer buf_state();
        double expected_wait();
        map<int,double> customer_state;
        void tick();
        Buffer line;
    private:

        Exp arrival_generator;
        Erlang service_generator;
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