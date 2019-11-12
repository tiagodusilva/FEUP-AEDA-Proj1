#include "../include/museum.h"
#include "../include/utilities.h"
#include "../include/exceptions.h"

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
    outfstream << fixed << setprecision(2) << museum.entry_fee << endl;
    outfstream << museum.address;

    return outfstream;
}

std::ifstream &operator>>(std::ifstream &infstream, Museum &museum) {

    try {
        // NAME
        getline(infstream, museum.name);

        // OPEN
        infstream >> museum.open;

        // CLOSE
        infstream >> museum.close;

        if (museum.close < museum.open) {
            cout << museum.open << endl << museum.close << endl;
            throw FileReadingFailed("Museum must not open after closing");
        }

        // ENTRY FEE
        infstream >> museum.entry_fee; utl::ignore(infstream);

        // ADDRESS
        infstream >> museum.address;
    }
    catch (std::exception &e) {
        infstream.setstate(ios::failbit);
        cerr << e.what();
    }

    return infstream;
}

void Museum::cin_read_museum(Museum &museum) {
    try {

        /* name */
        std::cout << "Name? ";
        getline(std::cin, museum.name);
        if (utl::isStrEmpty(museum.name))
            throw UserInputReadingFailure("given name is empty");

        /* address */
        cout << "Address (street name/XXXX-XXX/region name  or  region)? ";
        std::cin >> museum.address;
        if (cin.fail())
            throw "Address reading failed";

        /* entry fee */
        std::cout << "Event's entry fee? ";
        std::cin >> museum.entry_fee; utl::ignore(cin);
        if (cin.fail())
            throw UserInputReadingFailure("given name is empty");

        /* opening time */
        cout << "Opening time of the Museum (h:m)? ";
        std::cin >> museum.open;
        if (cin.fail())
            throw "Event time reading failed";

        /* closing time */
        cout << "Closing time of the Museum (h:m)? ";
        std::cin >> museum.close;
        if (cin.fail())
            throw "Event time reading failed";

        if (museum.close < museum.open)
            throw UserInputReadingFailure("Museum must not open after closing");

    }catch(const char* e) {
        // In this case, the exception would have already been handled
        std::cin.setstate(std::ios::failbit);
    }catch(const std::exception& e) {
        std::cin.setstate(std::ios::failbit);
        std::cerr << e.what() << endl;
    }
}

