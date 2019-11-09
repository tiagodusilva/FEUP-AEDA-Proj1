#ifndef MUSEUM_H
#define MUSEUM_H

#include "../include/address.h"
#include "../include/time.h"

#define MUSEUM_OUPUT_DELIM 15

class Museum {
private:
    std::string name;
    Time open, close;
    float entry_fee;
    Address address;

public:
    Museum() = default;
    Museum(const std::string &name, const Time& open, const Time &close, float entry_fee, const Address &address);
    ~Museum() = default;

    std::string get_name() const;
    Time get_open() const;
    Time get_close() const;
    float get_fee() const;
    Address get_address() const;

    // Two museums are equal if their name and address is the same
    inline bool operator== (const Museum &museum) { return (this->name == museum.name) && (this->address == museum.address); }

    friend std::ostream& operator<<(std::ostream &outstream, const Museum &ent);
    friend std::ofstream& operator<<(std::ofstream &outfstream, const Museum &ent);
    friend std::ifstream &operator>>(std::ifstream &infstream, Museum &ent);

};

#endif // MUSEUM_H
