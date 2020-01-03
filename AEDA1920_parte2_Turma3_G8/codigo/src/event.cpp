#include "../include/event.h"
#include "../include/exceptions.h"
#include "../include/utilities.h"

#include <iomanip>
#include <sstream>

using namespace std;

unsigned Event::id_tracker = 1;

Event::Event(const string& name, float ticket_fee, unsigned max_capacity, const string &location_name, const Address &address, const Time &time, const Date &date, const set<unsigned> &reservations, bool is_valid) {
    this->id = id_tracker++;
    this->name = name;
    this->ticket_fee = ticket_fee;
    this->max_capacity = max_capacity;
    this->location_name = location_name;
    this->address = address;
    this->time = time;
    this->date = date;
    this->reservations = reservations;
    this->is_valid = is_valid;
}


/* GETTERS */
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

string Event::get_location_name() const {
    return this->location_name;
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

/* SETTERS */
void Event::set_max_capacity(unsigned new_capacity) {
    if (new_capacity < this->reservations.size())
        throw UserInputReadingFailure("Event's maximum capacity must not be lower than the current number of reservations");
    this->max_capacity = new_capacity;
}

void Event::set_name(const std::string &new_name) {
    if (utl::isStrEmpty(new_name))
        throw UserInputReadingFailure("Name must not be be considered an empty string");
    this->name = new_name;
}

void Event::set_ticket_fee(float new_ticket_fee) {
    if (new_ticket_fee < 0)
        throw UserInputReadingFailure("Event's ticket fee must not be a negative number");
    this->ticket_fee = new_ticket_fee;
}

void Event::set_location_name(const std::string &new_location_name) {
    if (utl::isStrEmpty(new_location_name))
        throw UserInputReadingFailure("Location name must not be be considered an empty string");
    this->location_name = new_location_name;
}

void Event::set_address(const Address &new_address) {
    this->address = new_address;
}

void Event::set_time(const Time &new_time) {
    this->time = new_time;
}

void Event::set_date(const Date &new_date) {
    this->date = new_date;
}

void Event::set_invalid_id() {
    this->id = 0;
}

void Event::set_validity(bool new_is_valid) {
    this->is_valid = new_is_valid;
}

/* OTHER PUBLIC METHODS */

void Event::purchase(unsigned cc) {
    if (this->is_full())
        throw InvalidObject("Event", "event with id " + to_string(this->id) + "is full");

    if (!this->is_valid)
        throw InvalidObject("Event", "event with id " + to_string(this->id) + "is not available");

    if (this->reservations.find(cc) != this->reservations.end())
        throw InvalidObject("Event", "event with id " + to_string(this->id) + " was already bough by user with cc " + to_string(cc));

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
              left << setw(EVENT_OUPUT_DELIM) << "Name"	           << " : " << right << this->name << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Id"		       << " : " << right << this->id << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Ticket Fee"	   << " : " << right << fixed << setprecision(2) << this->ticket_fee << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "With Discount"   << " : " << right << fixed << setprecision(2) << this->ticket_fee * (1-discount) << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Tickets Sold"    << " : " << right << setprecision(0) << this->get_capacity_percentage() * 100 << "% de "  << this->max_capacity << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Location name"   << " : " << right << this->location_name << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Location"        << " : " << right << this->address << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Day"	           << " : " << right << this->date << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Time"	           << " : " << right << this->time << endl <<
              left << setw(EVENT_OUPUT_DELIM) << "Available"       << " : " << right;

              if (this->is_valid && !this->is_full())
                  outstream << "Yes";
              else
                  outstream << "No";
}

std::ostream&
operator<<(std::ostream &outstream, const Event &ev)
{
	outstream <<
		left << setw(EVENT_OUPUT_DELIM) << "Name"	     << " : " << right << ev.name << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Id"		     << " : " << right << ev.id << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Ticket Fee"	     << " : " << right << fixed << setprecision(2) << ev.ticket_fee << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Tickets Sold"    << " : " << right  << setprecision(0) << ev.get_capacity_percentage() * 100 << "% de "  << ev.max_capacity << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Location Name"   << " : " << right << ev.location_name << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Location"        << " : " << right << ev.address << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Day"	     << " : " << right << ev.date << endl <<
		left << setw(EVENT_OUPUT_DELIM) << "Time"	     << " : " << right << ev.time << endl <<
        left << setw(EVENT_OUPUT_DELIM) << "Available"       << " : " << right;


	if (timespan_size(Date(), Time(), ev.date, ev.time) < 0)
		outstream << "Has already taken place";
	else {
		if (ev.is_valid && !ev.is_full())
			outstream << "Yes";
		else
			outstream << "No";
	}

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
    outfstream << ev.location_name << endl;
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
        if (ev.ticket_fee < 0)
            throw FileReadingFailed("Event's ticket fee must not be negative");

        // RESERVATIONS
        ev.reservations.clear();
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
        if (ev.max_capacity < num_reservations)
            throw FileReadingFailed("Event's maximum capacity must not be lower than the current number of reservations");

        // LOCATION NAME
        getline(infstream, ev.location_name);

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


void Event::cin_read_event(Event &ev) {
    try {

        // Attribute it an invalid id
        ev.id = 0;

        /* name */
        std::cout << "Name? ";
        getline(std::cin, ev.name);
        if (utl::isStrEmpty(ev.name))
            throw UserInputReadingFailure("given name is empty");

        /* entry fee */
        std::cout << "Event's ticket fee? ";
        std::cin >> ev.ticket_fee; utl::ignore(cin);
        if (cin.fail())
            throw UserInputReadingFailure("given name is empty");
        if (ev.ticket_fee < 0)
            throw FileReadingFailed("Event's ticket fee must not be negative");

        /* max capacity */
        std::cout << "Event's max capacity? ";
        std::string temp_str;
        getline(std::cin, temp_str);
        if (utl::isNum(temp_str))
            ev.max_capacity = stoi(temp_str);
        else
            throw UserInputReadingFailure("given capacity is not a number: " + temp_str);

        /* location name */
        cout << "Location name? ";
        getline(std::cin, ev.location_name);
        if (utl::isStrEmpty(ev.location_name))
            throw UserInputReadingFailure("given location name is empty");

        /* address */
        cout << "Address (street name/XXXX-XXX/region name  or  region)? ";
        std::cin >> ev.address;
        if (cin.fail())
            throw "Address reading failed";

        /* get date */
        cout << "Date of the Event (year/month/day)? ";
        Date temp_date;
        std::cin >> ev.date;
        if (cin.fail())
            throw "Event date reading failed";

        /* time */
        cout << "Time of the start of the Event (h:m)? ";
        std::cin >> ev.time;
        if (cin.fail())
            throw "Event time reading failed";

        ev.reservations = set<unsigned>();
        ev.is_valid = true;
        // Everythin went all fine and dandy so far, time so set it's id to a valid state
        ev.id = Event::id_tracker++;

    }catch(const char* e) {
        // In this case, the exception would have already been handled
        std::cin.setstate(std::ios::failbit);

    }catch(const std::exception& e) {
        std::cin.setstate(std::ios::failbit);
        std::cerr << e.what() << endl;
    }
}

