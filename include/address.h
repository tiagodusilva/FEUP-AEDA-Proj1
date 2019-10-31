#ifndef ADDRESS_H
#define ADDRESS_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Address
{
private:
	std::string street, zipCode, region;
public:
	Address();
	Address(const string &street, const string &zipCode, const string &region);

	/* getters */
	std::string getStreet() const;
	std::string getZipCode() const;
	std::string getRegion() const;

	/* other member functions */
	static bool verify_zip_code(const string &string);

	/* operator overloads */
	friend std::ostream& operator<< (std::ostream& stream, const Address& address);
	friend std::ofstream& operator<< (std::ofstream& outstream, const Address& address);
	friend std::ifstream& operator>>(std::ifstream &instream, Address &a);
};

#endif // ADDRESS_H
