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
        Customer next_up();
        deque<Customer> buf;
};

#endif