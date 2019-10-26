#include "../include/enterprise.h"

using  namespace std;

Enterprise::Enterprise(const string &name, const string &contact, const Address &address, const vector<Event> &events) {
    this->name = name;
    this->contact = contact;
    this->address = address;
    this->events = events;
}

string Enterprise::getName() const {
    return this->name;
}

string Enterprise::getContact() const {
    return this->contact;
}

Address Enterprise::getAddress() const {
    return this->address;
}

const vector<Event> &Enterprise::getEvents() const {
    return this->events;
}
