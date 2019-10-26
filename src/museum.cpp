#include "../include/museum.h"

using  namespace std;

Museum::Museum(const string &name, const Time &open, const Time &close, int current_capacity, int max_capacity,
               float entry_fee, const Address &address) {
    this->name = name;
    this->open = open;
    this->close = close;
    this->current_capacity = current_capacity;
    this->max_capacity = max_capacity;
    this->entry_fee = entry_fee;
    this->address = address;
}

string Museum::getName() const {
    return std::__cxx11::string();
}

Time Museum::getOpen() const {
    return this->open;
}

Time Museum::getClose() const {
    return this->close;
}

int Museum::getCurrentCapacity() const {
    return this->max_capacity;
}

int Museum::getMaximumCapacity() const {
    return this->max_capacity;
}

float Museum::getFee() const {
    return this->entry_fee;
}

Address Museum::getAddress() const {
    return this->address;
}
