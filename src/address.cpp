#include "../include/address.h"

using namespace std;

Address::Address() {
    this->street = "Undefined Street";
    this->zipCode = "XXXX-XXX";
    this->region = "Undefined Region";
}

Address::Address(const string &street, const string &zipCode, const string &region) {
    this->street = street;
    this->zipCode = zipCode;
    this->region = region;
}

string Address::getStreet() const {
    return this->street;
}

string Address::getZipCode() const {
    return this->zipCode;
}

string Address::getRegion() const {
    return this->region;
}

std::ostream& operator<<(std::ostream& stream, const Address& address) {
    stream << address.street << " / " << " / " <<
           address.zipCode << " / " << address.region;
    return stream;
}

bool Address::verify_zip_code(const string &zip) {
    if (zip.size() != 8)
        return false;

    if (zip[4] != '-')
        return false;

    return isdigit(zip[0]) && isdigit(zip[1]) && isdigit(zip[2]) &&
           isdigit(zip[3]) && isdigit(zip[5]) && isdigit(zip[6]) && isdigit(zip[7]);
}
