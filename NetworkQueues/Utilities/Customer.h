#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
    public:
        double arrival_time = 0;
        double time_tobe_served = 0;
        int sequence_id = 0;
        bool in_system = false;
};

#endif