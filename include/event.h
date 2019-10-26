#ifndef EVENT_H
#define EVENT_H

#include "../include/time.h"
#include "../include/date.h"
#include "../include/address.h"
#include <string>

class DateTime;

using namespace std;

class Event {
private:
    string name;
    float ticket_fee;
    int current_capacity, max_capacity;
    Address address;
    Time time;
    Date date;
public:
    Event() = default;
    Event(const string& name, float cost, int current_capacity, int max_capacity, const Address& addres, const Time &time, const Date &date);
    ~Event() = default;

    float getFee() const;
    string getName() const;
    int getCurrentCapacity() const;
    int getMaxCapacity() const;
    Time getTime() const;
    Date getDate() const;

    void purchase();
};

#endif // EVENT_H
