#ifndef BUFFER_H
#define BUFFER_H

#include "Customer.h"
#include <deque>

using namespace std;

class Buffer {
    public:
        Buffer();
        int add(Customer);
        int served();
        int num_waiting();
        int schedule_service(int packet_id,double service_time);
        Customer last_up();
        Customer next_up();
        deque<Customer> buf;
};

#endif