#include "../include/event.h"
#include "../include/exceptions.h"
#include "../include/utilities.h"

#include <iomanip>
#include <sstream>

using namespace std;

unsigned Event::id_tracker = 1;

Event::Event(const string& name, float ticket_fee, unsigned max_capacity, const Address &address, const Time &time, const Date &date, const set<unsigned> &reservations, bool is_valid) {
    this->id = id_tracker++;
    this->name = name;
    this->ticket_fee = ticket_fee;
    this->max_capacity = max_capacity;
    this->address = address;
    this->time = time;
    this->date = date;
    this->reservations = reservations;
    this->is_valid = is_valid;
}

unsigned Event::get_id() const {
    return this->id;
}

float Event::get_fee() const {
    return this->ticket_fee;
}

string Event::get_name() const {
    return this->name;
}

unsigned Event::get_max_capacity() const {
    return this->max_capacity;
}

unsigned Event::get_current_capacity() const {
    return this->reservations.size();
}

Address Event::get_address() const {
    return this->address;
}

Time Event::get_time() const {
    return this->time;
}

Date Event::get_date() const {
    return this->date;
}

bool Event::get_validity() const {
    return this->is_valid;
}

void Event::purchase(unsigned cc) {
    if (this->is_full())
        throw EventFull(this->id);

    if (!this->is_valid)
        throw EventInvalid(this->id);

    if (this->reservations.find(cc) != this->reservations.end())
        throw EventAlreadyBought(this->id, cc);

    this->reservations.insert(cc);
}

bool Event::is_full() const {
    return this->reservations.size() >= this->max_capacity;
}

bool Event::is_half_full() const {
    return (this->reservations.size() * 2 >= this->max_capacity); // Plz don't overflow
}

float Event::get_capacity_percentage() const {
    if (this->max_capacity == 0)
        return 1;
    return ((float) this->reservations.size() / (float) this->max_capacity);
}

bool Event::is_over() const {
    if (this->date == Date())
        return this->time >= Time();
    return this->date >= Date();
}

void Event::print_with_discount(std::ostream &outstream, float discount) const {
    outstream <<
              left << setw(EVENT_OUPUT_DELIM) << "Name"	     << " : " << right << this->name << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Id"		     << " : " << right << this->id << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Entry Fee"	     << " : " << right << this->ticket_fee << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "With Discount"	     << " : " << right << this->ticket_fee * (1-discount) << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Tickets Sold"    << " : " << right << setprecision(2) << this->get_capacity_percentage() * 100 << "% de "  << this->max_capacity << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Location"        << " : " << right << this->address << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Day"	     << " : " << right << this->date << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Time"	     << " : " << right << this->time;
}

std::ostream&
operator<<(std::ostream &outstream, const Event &ev)
{
	outstream <<
		left << setw(EVENT_OUPUT_DELIM) << "Name"	     << " : " << right << ev.name << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Id"		     << " : " << right << ev.id << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Entry Fee"	     << " : " << right << ev.ticket_fee << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Tickets Sold"    << " : " << right << setprecision(2) << ev.get_capacity_percentage() * 100 << "% de "  << ev.max_capacity << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Location"        << " : " << right << ev.address << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Day"	     << " : " << right << ev.date << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Time"	     << " : " << right << ev.time;

	return outstream;
}

std::ofstream &operator<<(std::ofstream &outfstream, const Event & ev) {
    outfstream << ev.name << endl;
    outfstream << to_string(ev.ticket_fee) << endl;

    outfstream << to_string(ev.reservations.size()) << endl;

    if (ev.reservations.size() > 0) {
	for (const auto &cc: ev.reservations) {
	    outfstream << to_string(cc) << ' ';
	}
        outfstream << endl;
    }

    outfstream << to_string(ev.max_capacity) << endl;
    outfstream << ev.address << endl;
    outfstream << ev.date << endl;
    outfstream << ev.time << endl;
    outfstream << to_string(ev.is_valid);

    return outfstream;
}

std::ifstream &operator>>(std::ifstream &infstream, Event &ev) {

    try {
        // ID
        ev.id = Event::id_tracker++;

        // NAME
        getline(infstream, ev.name);

        // TICKETS
        infstream >> ev.ticket_fee; utl::ignore(infstream);

        // RESERVATIONS
        int num_reservations;
        infstream >> num_reservations; utl::ignore(infstream);

	if (num_reservations > 0) {
		string tempStr;
		getline(infstream, tempStr);

		istringstream ss(tempStr);
		int tempInt;
		for (; num_reservations > 0; --num_reservations) {
		    ss >> tempInt;
		    // As this is a set, there will never be repeated elements *winks*
		    ev.reservations.insert(tempInt);
		}
	}

        // MAX CAPACITY
        infstream >> ev.max_capacity; utl::ignore(infstream);

        // ADDRESS
        infstream >> ev.address;

        // DATE
        infstream >> ev.date;

        // TIME
        infstream >> ev.time;

	// IS_VALID
	infstream >> ev.is_valid; utl::ignore(infstream);
    }
    catch (std::exception &e) {
        infstream.setstate(ios::failbit);
        cerr << e.what();
    }

    return infstream;
}
