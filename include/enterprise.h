#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include "../include/address.h"
#include "../include/event.h"
#include "set"
#include <string>

class Enterprise {
private:
    std::string name;
    std::string contact;
    Address address;
    std::set<Event> events;
public:
    Enterprise() = default;
    Enterprise(const std::string &name, const std::string &contact, const Address &address, const std::set<Event> &events);
    ~Enterprise() = default;

    std::string getName() const;
    std::string getContact() const;
    Address getAddress() const;
    const std::set<Event>& getEvents() const;
    const Event& getEvent(unsigned id) const;



};

#endif // ENTERPRISE_H
