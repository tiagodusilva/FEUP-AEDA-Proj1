#include "../include/museum.h"
#include "../include/utilities.h"

#include <iomanip>

using namespace std;

Museum::Museum(const string &name, const Time &open, const Time &close, float entry_fee, const Address &address) {
    this->name = name;
    this->open = open;
    this->close = close;
    this->entry_fee = entry_fee;
    this->address = address;
}

string Museum::get_name() const {
    return this->name;
}

Time Museum::get_open() const {
    return this->open;
}

Time Museum::get_close() const {
    return this->close;
}

float Museum::get_fee() const {
    return this->entry_fee;
}

Address Museum::get_address() const {
    return this->address;
}

std::ostream &operator<<(std::ostream &outstream, const Museum &museum) {
    outstream <<
              left << setw(MUSEUM_OUPUT_DELIM) << "Name"	      << " : " << right << museum.name << endl <<
              left << setw(MUSEUM_OUPUT_DELIM) << "Opening Hours"		  << " : " << right << museum.open << " to " << museum.close << endl <<
              left << setw(MUSEUM_OUPUT_DELIM) << "Entry Fee"	      << " : " << right << museum.entry_fee << endl <<
              left << setw(MUSEUM_OUPUT_DELIM) << "Address" << " : " << right << museum.address;

    return outstream;
}

std::ofstream &operator<<(std::ofstream &outfstream, const Museum &museum) {
    outfstream << museum.name << endl;
    outfstream << museum.open << endl;
    outfstream << museum.close << endl;
    outfstream << to_string(museum.entry_fee) << endl;
    outfstream << museum.address;

    return outfstream;
}

std::ifstream &operator>>(std::ifstream &infstream, Museum &ent) {

    try {
        // NAME
        getline(infstream, ent.name);

        // OPEN
        infstream >> ent.open;

        // CLOSE
        infstream >> ent.close;

        // ENTRY FEE
        infstream >> ent.entry_fee; utl::ignore(infstream);

        // ADDRESS
        infstream >> ent.address;
    }
    catch (std::exception &e) {
        infstream.setstate(ios::failbit);
        cerr << e.what();
    }

    return infstream;
}
