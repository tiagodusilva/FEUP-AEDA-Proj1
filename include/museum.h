#ifndef MUSEUM_H
#define MUSEUM_H

#include "../include/address.h"
#include "../include/time.h"

class Museum {
private:
    std::string name;
    Time open, close;
    int current_capacity, max_capacity; // TODO: Implement daily limit on entries, need to keep track of them in some structure
    float entry_fee;
    Address address;

public:
    Museum() = default;
    Museum(const std::string &name, const Time& open, const Time &close, int current_capacity, int max_capacity, float entry_fee, const Address &address);
    ~Museum() = default;

    std::string getName() const;
    Time getOpen() const;
    Time getClose() const;
    int getCurrentCapacity() const;
    int getMaximumCapacity() const;
    float getFee() const;
    Address getAddress() const;
};

#endif // MUSEUM_H
