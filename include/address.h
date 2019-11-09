#ifndef ADDRESS_H
#define ADDRESS_H

#include <fstream>
#include <iostream>
#include <string>

#define HALF_ADDR_ZIPCODE "0000-000"

class Address
{
private:
	std::string street, zipCode, region;
public:
	Address();
	Address(const std::string &region);
	Address(const std::string &street, const std::string &zipCode, const std::string &region);

	/* getters */
	std::string getStreet() const;
	std::string getZipCode() const;
	std::string getRegion() const;

	/* other member functions */
	static bool verify_zip_code(const std::string &string);

	/* operator overloads */
	friend std::ostream& operator<<(std::ostream& outstream, const Address &a);
	friend std::ofstream& operator<<(std::ofstream& outstream, const Address &a);
	friend std::istream& operator>>(std::istream &instream, Address &a);
	friend std::ifstream& operator>>(std::ifstream &instream, Address &a);
};


bool operator==(const Address& lhs, const Address& rhs);

#endif // ADDRESS_H
