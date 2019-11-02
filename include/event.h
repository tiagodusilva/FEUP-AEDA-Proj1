#ifndef EVENT_H
#define EVENT_H

#include "../include/time.h"
#include "../include/date.h"
#include "../include/address.h"
#include <string>
#include <set>
#include <iostream>

#define EVENT_OUPUT_DELIM 15

class DateTime;

class Event {
private:
    static unsigned id_tracker;
    unsigned id;
    std::string name;
    float ticket_fee;
    int current_capacity, max_capacity;
    Address address;
    Time time;
    Date date;
    std::set<unsigned> reservations;
    bool is_valid;

public:
    Event() = default;
    Event(const std::string& name, float cost, int current_capacity, int max_capacity, const Address& addres, const Time &time, const Date &date, const std::set<unsigned> &reservations=std::set<unsigned>(), bool is_valid=true);
    ~Event() = default;

    unsigned getId() const;
    float getFee() const;
    std::string getName() const;
    int getCurrentCapacity() const;
    int getMaxCapacity() const;
    Address getAddress() const;
    Time getTime() const;
    Date getDate() const;

    void purchase(unsigned cc);

    bool isFull() const;
    bool isHalfFull() const;
    float getCapacityPercentage() const;
    bool isOver() const;

    bool operator==(const Event &ev) const;
    bool operator<(const Event &ev) const;

    friend std::ostream& operator<<(std::ostream &outstream, const Event &ev);
    static void show(const std::set<Event> &events);
};

#endif // EVENT_H
