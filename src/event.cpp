#include "../include/event.h"

using namespace std;

Event::Event(const string& name, float ticket_fee, int current_capacity, int max_capacity, const Address &address, const Time &time, const Date &date) {
    this->name = name;
    this->ticket_fee = ticket_fee;
    this->current_capacity = current_capacity;
    this->max_capacity = max_capacity;
    this->address = address;
    this->time = time;
    this->date = date;
}

float Event::getFee() const {
    return this->ticket_fee;
}

string Event::getName() const {
    return this->name;
}

int Event::getCurrentCapacity() const {
    return this->current_capacity;
}

int Event::getMaxCapacity() const {
    return this->max_capacity;
}

Time Event::getTime() const {
    return this->time;
}

Date Event::getDate() const {
    return this->date;
}

void Event::purchase() {
    return;
}

