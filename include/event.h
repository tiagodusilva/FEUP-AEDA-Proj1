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
    unsigned id, max_capacity;
    std::string name;
    float ticket_fee;
    Address address;
    Time time;
    Date date;
    std::set<unsigned> reservations;
    bool is_valid;

public:
    Event() = default;
    Event(const std::string& name, float cost, unsigned max_capacity, const Address& addres, const Time &time, const Date &date, const std::set<unsigned> &reservations=std::set<unsigned>(), bool is_valid=true);
    ~Event() = default;

    unsigned get_id() const;
    float get_fee() const;
    std::string get_name() const;
    unsigned get_max_capacity() const;
    unsigned get_current_capacity() const;
    Address get_address() const;
    Time get_time() const;
    Date get_date() const;

    void purchase(unsigned cc);

    bool is_full() const;
    bool is_half_full() const;
    float get_capacity_percentage() const;
    bool is_over() const;

    inline bool operator==(const Event &ev) const { return this->id == ev.id; };
    inline bool operator<(const Event &ev) const { return this->id < ev.id; };

    void print_with_discount(float discount=1.0);
    friend std::ostream& operator<<(std::ostream &outstream, const Event &ev);
    friend std::ofstream& operator <<(std::ofstream &outfstream, const Event &ev);
    friend std::ifstream &operator>>(std::ifstream &infstream, Event &ev);

};

inline bool operator==(const Event& ev, const unsigned id) { return ev.get_id() == id; };
inline bool operator==(const unsigned id, const Event& ev) { return operator==(ev, id); };
inline bool operator!=(const Event& ev, const unsigned id) { return ev.get_id() != id; };
inline bool operator!=(const unsigned id, const Event& ev) { return operator!=(ev, id); };

#endif // EVENT_H
