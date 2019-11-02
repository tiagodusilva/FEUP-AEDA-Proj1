#include "../include/enterprise.h"
#include "../include/exceptions.h"

using  namespace std;

Enterprise::Enterprise(const string &name, const string &contact, const Address &address, const set<Event> &events) {
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

const set<Event> &Enterprise::getEvents() const {
    return this->events;
}

const Event &Enterprise::getEvent(unsigned id) const {
    for (const auto &x: this->events) {
        if (x.getId() == id)
            return x;
    }

    throw EventNotFound(id);
}
