#include "MM1.h"
#include <iterator>
#include <iostream>

MM1::MM1(): arrival_generator(0.5), service_generator(1) {
    //add intial packet arrival to line
    Customer c;
    c.sequence_id = 1;
    this->cur_sequence_id = 1;
    c.arrival_time = this->arrival_generator.generate();
    this->line.add(c);
}

MM1::MM1(double lambda, double mu): MM1() {
    this->arrival_rate = lambda;
    this->service_rate = mu;
}

MM1::MM1(double lambda, double mu, double step_time): MM1(lambda,mu) {
    this->step_time = step_time;
    MM1(lambda,mu);
}

MM1::MM1(double lambda,double mu, double step_time,int intial_customers) : MM1(lambda,mu,step_time) {
    this->num_customers = intial_customers;
}

void MM1::tick() {

    double current_step = this->time;

    //add new packets and thier arrival time to a queue
    //do this for packet arrival in this->step_time
    Customer cp = this->line.next_up();
    double current_arrival_time = cp.arrival_time;
    while (current_arrival_time < current_step + this->step_time){
        Customer c;

        //calculate exponentially distributed  inter_arrival_time
        double arrival_time_delta = this->arrival_generator.generate();

        //update sequency_id and arrival time for next packet
        this->cur_sequence_id++;
        c.sequence_id = this->cur_sequence_id;
        c.arrival_time = cp.arrival_time + arrival_time_delta;

        current_arrival_time = current_arrival_time + arrival_time_delta;

        //add customer to packet line
        line.add(c);
        cp = c;
    }

    //Todo: change to iterator
    for(deque<Customer>::iterator ptr = this->line.buf.begin(); ptr != this->line.buf.end() && \
            this->time < (current_step + this->step_time); ptr++) {

        if (!ptr->in_system) {
            this->next_arrival = ptr->arrival_time;                           //check arrival time of next packet
            double service_time_delta = this->service_generator.generate();   //generate exponeitally distributed serivec time

            //check to see if a customer is in service
            if (this->next_service > 0) {

                //if next action happens in this step
                if ((this->next_arrival < (current_step + this->step_time)) || (this->next_service < (current_step + this->step_time))){

                    //add another customer to the system if there is a wait
                    if(this->next_arrival < this->next_service){
                        customer_state[this->num_customers] = customer_state[this->num_customers] \
                        + (this->next_arrival - this->time);
                        this->num_customers++;
                        this->time = this->next_arrival;
                        ptr->in_system = true;

                    //packet is leaving system
                    } else if (this->next_arrival > this->next_service){
                        customer_state[this->num_customers] = customer_state[this->num_customers] \
                        + (this->next_service - this->time);
                        this->time = this->next_service;            //update sim time
                        this->num_customers--;                      //remove from system
                        this->line.served();                        //serve that packet
                        cp = this->line.next_up();                  //check next packet in line to be served

                        //next packet up enters the server now
                        //next packet up has been waiting
                        if (cp.arrival_time < this->next_service){
                            this->next_service = this->next_service + service_time_delta;   //set next service time for next packet
                            cp.time_tobe_served = this->next_service; //set service time for next packet
                            ptr--;

                        //if queue goes to zero i.e. no packets waiting to be served
                        } else {

                            //if packet can be handled this tick cycle
                            if (this->next_arrival < (current_step + this->step_time)){
                                customer_state[this->num_customers] = customer_state[this->num_customers] \
                                    + (this->next_arrival - this->time);
                                ptr->time_tobe_served = next_arrival + service_time_delta; //time to be served
                                this->next_service = ptr->time_tobe_served;                //update next service time
                                this->time = this->next_arrival;                        //set current time to when packet arrives
                                this->num_customers++;                                  //add packet to system
                                ptr->in_system = true;

                            //wait for next tick to be handled
                            } else {
                                customer_state[this->num_customers] = customer_state[this->num_customers] \
                                    + ((current_step + this->step_time) - this->time);
                                this->time = current_step + this->step_time;
                                this->next_service = 0;
                            }
                        }
                    }
                }

            //no one is being served at start of tick cycle
            } else {
                //if next action happens in this step
                if (this->next_arrival < (current_step + this->step_time)){
                    customer_state[this->num_customers] = customer_state[this->num_customers] \
                        + (this->next_arrival - this->time);
                    ptr->time_tobe_served = next_arrival + service_time_delta; //time to be served
                    this->next_service = ptr->time_tobe_served;                //update next service time
                    this->time = this->next_arrival;                        //set current time to when packet arrives
                    this->num_customers++;                                  //add packet to system
                    ptr->in_system = true;
                }
            }
        }
    }

    //take to the end of tick cycle and add into map
    customer_state[this->num_customers] = customer_state[this->num_customers] \
                    + ((current_step + this->step_time) - this->time);
    this->time = current_step + this->step_time;

}