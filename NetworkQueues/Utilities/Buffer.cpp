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

int Buffer::served(){
    this->buf.pop_front();
    return 0;
}

int Buffer::num_waiting(){
    return this->buf.size();
}