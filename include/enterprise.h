#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include "../include/address.h"
#include "../include/event.h"
#include "set"
#include <string>

#define ENTERPRISE_OUPUT_DELIM 15

class Enterprise {
private:
    std::string name;
    std::string contact;
    Address address;
    std::set<Event> events;

public:
    Enterprise() = default;
    Enterprise(const std::string &name, const std::string &contact, const Address &address, const std::set<Event> &events = std::set<Event>());
    ~Enterprise() = default;

    std::string get_name() const;
    std::string get_contact() const;
    Address get_address() const;
    const std::set<Event>& get_events() const;
    const Event& get_event(unsigned id) const;

    bool has_event(unsigned id) const;

    friend std::ostream& operator<<(std::ostream &outstream, const Enterprise &ent);
    friend std::ofstream& operator<<(std::ofstream &outfstream, const Enterprise &ent);
    friend std::ifstream &operator>>(std::ifstream &infstream, Enterprise &ent);

};

#endif // ENTERPRISE_H
