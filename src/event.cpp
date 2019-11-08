#include "../include/event.h"
#include "../include/exceptions.h"

#include <iomanip>

using namespace std;

unsigned Event::id_tracker = 1;

Event::Event(const string& name, float ticket_fee, int current_capacity, int max_capacity, const Address &address, const Time &time, const Date &date, const set<unsigned> &reservations, bool is_valid) {
    this->id = id_tracker++;
    this->name = name;
    this->ticket_fee = ticket_fee;
    this->current_capacity = current_capacity;
    this->max_capacity = max_capacity;
    this->address = address;
    this->time = time;
    this->date = date;
    this->reservations = reservations;
    this->is_valid = is_valid;
}

unsigned Event::getId() const {
    return this->id;
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

Address Event::getAddress() const {
    return this->address;
}

Time Event::getTime() const {
    return this->time;
}

Date Event::getDate() const {
    return this->date;
}

void Event::purchase(unsigned cc) {

    if (this->isFull())
        throw EventFull(this->id);

    if (this->reservations.find(cc) != this->reservations.end())
        throw EventAlreadyBought(this->id, cc);

    this->reservations.insert(cc);
    ++current_capacity;
}

bool Event::isFull() const {
    return this->current_capacity >= this->max_capacity;
}

bool Event::isHalfFull() const {
    return (this->current_capacity * 2 >= this->max_capacity); // Plz don't overflow
}

float Event::getCapacityPercentage() const {
    if (this->max_capacity == 0)
        return 1;
    return ((float) this->current_capacity / (float) this->max_capacity);
}

bool Event::isOver() const {
    if (this->date == Date())
        return this->time >= Time();
    return this->date >= Date();
}

inline bool Event::operator==(const Event &ev) const {
    return this->id == ev.id;
}

inline bool Event::operator<(const Event &ev) const {
    return this->id < ev.id;
}

std::ostream&
operator<<(std::ostream &outstream, const Event &ev)
{
	outstream <<
		left << setw(EVENT_OUPUT_DELIM) << "Name"	     << " : " << right << ev.name << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Id"		     << " : " << right << ev.id << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Entry Fee"	     << " : " << right << ev.ticket_fee << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Max Capacity"    << " : " << right << ev.max_capacity << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Percentage sold" << " : " << right << setprecision(2) << ev.getCapacityPercentage() * 100 << " %" << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Location"        << " : " << right << ev.address << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Date"	     << " : " << right << ev.date << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Time"	     << " : " << right << ev.time;

	return outstream;
}

std::ofstream &operator<<(std::ofstream &outfstream, const Event & ev) {
    outfstream << ev.name << endl;
    outfstream << to_string(ev.ticket_fee) << endl;
    outfstream << to_string(ev.current_capacity) << endl;
    outfstream << to_string(ev.max_capacity) << endl;
    outfstream << ev.address << endl;
    outfstream << ev.date << endl;
    outfstream << ev.time;
    return outfstream;
}

std::ifstream &operator>>(std::ifstream &infstream, Event & ev) {
    return infstream;
}