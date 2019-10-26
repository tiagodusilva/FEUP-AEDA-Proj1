#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>

using namespace std;

class Address
{
private:
    std::string street, zipCode, region;
public:
    Address();
    Address(const string &street, const string &zipCode, const string &region);

    /* GET methods */
    std::string getStreet() const;
    std::string getZipCode() const;
    std::string getRegion() const;

    /* Other Methods */
    static bool verify_zip_code(const string &string);

    /**
        Outputs Address to ostream
    */
    friend std::ostream& operator<< (std::ostream& stream, const Address& address);
};

#endif // ADDRESS_H