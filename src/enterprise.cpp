#include "../include/enterprise.h"
#include "../include/exceptions.h"
#include "../include/utilities.h"

#include <iomanip>

using  namespace std;

Enterprise::Enterprise(const string &name, const string &contact, const Address &address, const set<Event> &events) {
    this->name = name;
    this->contact = contact;
    this->address = address;
    this->events = events;
}

string Enterprise::get_name() const {
    return this->name;
}

string Enterprise::get_contact() const {
    return this->contact;
}

Address Enterprise::get_address() const {
    return this->address;
}

const set<Event> &Enterprise::get_events() const {
    return this->events;
}

const Event &Enterprise::get_event(unsigned id) const {
    for (const auto &ev: this->events) {
        if (ev == id)
            return ev;
    }

    throw EventNotFound(id);
}

bool Enterprise::has_event(unsigned id) const {
    for (const auto &ev: this->events) {
        if (ev == id)
            return true;
    }
    return false;
}

void Enterprise::purchase_event(unsigned id, unsigned cc) {

    // Apparently sets always return const iterators... so yeah... about that one...
    for (const auto &ev: this->events) {
        if (ev == id) {
            Event aux = ev;
            aux.purchase(cc);
            this->events.erase(ev);
            this->events.insert(aux);
        }
    }

    throw EventNotFound(id);
}

std::ostream &operator<<(std::ostream &outstream, const Enterprise &ent) {
    outstream <<
              left << setw(ENTERPRISE_OUPUT_DELIM) << "Name"	      << " : " << right << ent.name << endl <<
              left << setw(ENTERPRISE_OUPUT_DELIM) << "Contact"		  << " : " << right << ent.contact << endl <<
              left << setw(ENTERPRISE_OUPUT_DELIM) << "Address"	      << " : " << right << ent.address << endl <<
              left << setw(ENTERPRISE_OUPUT_DELIM) << "Num of Events" << " : " << right << ent.events.size();

    return outstream;
}

std::ofstream &operator<<(std::ofstream &outfstream, const Enterprise &ent) {
    outfstream << ent.name << endl;
    outfstream << ent.contact << endl;
    outfstream << to_string(ent.events.size()) << endl;
    for (const auto &ev: ent.events) {
        outfstream << ev <<  endl;
    }
    outfstream << ent.address;
    return outfstream;
}

std::ifstream &operator>>(std::ifstream &infstream, Enterprise &ent) {

    try {
        // NAME
        getline(infstream, ent.name);

        // CONTACT
        getline(infstream, ent.contact);

        // EVENTS
        int num_events;
        infstream >> num_events; utl::ignore(infstream);

        Event auxEv;
        for (; num_events > 0; --num_events) {
            infstream >> auxEv;
            ent.events.insert(auxEv);
        }

        // ADDRESS
        infstream >> ent.address;
    }
    catch (std::exception &e) {
        infstream.setstate(ios::failbit);
        cerr << e.what();
    }

    return infstream;
}
