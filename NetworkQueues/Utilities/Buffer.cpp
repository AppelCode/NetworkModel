#include "Buffer.h"

Buffer::Buffer() {
    //do nothing
}

int Buffer::add(Customer c){
    this->buf.push_back(c);
    return 0;
}

Customer Buffer::next_up() {
    return this->buf.front();
}

Customer Buffer::last_up() {
    return this->buf.back();
}

int Buffer::served(){
    this->buf.pop_front();
    return 0;
}

int Buffer::schedule_service(int packet_id,double service_time){
    this->buf[packet_id].time_tobe_served = service_time;
}

int Buffer::num_waiting(){
    return this->buf.size();
}