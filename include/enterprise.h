#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include "../include/address.h"
#include "../include/event.h"
#include <string>
#include <vector>

using namespace std;

class Enterprise {
private:
    string name;
    string contact;
    Address address;
    vector<Event> events;
public:
    Enterprise() = default;
    Enterprise(const string &name, const string &contact, const Address &address, const vector<Event> &events);
    ~Enterprise() = default;

    string getName() const;
    string getContact() const;
    Address getAddress() const;
    const vector<Event>& getEvents() const;
};

#endif // ENTERPRISE_H
