#include "../include/address.h"

#include "../include/exceptions.h"

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

bool Address::verify_zip_code(const string &zip) {
    if (zip.size() != 8)
        return false;

    if (zip[4] != '-')
        return false;

    return isdigit(zip[0]) && isdigit(zip[1]) && isdigit(zip[2]) &&
           isdigit(zip[3]) && isdigit(zip[5]) && isdigit(zip[6]) && isdigit(zip[7]);
}

std::ostream&
operator<<(std::ostream& stream, const Address& address)
{
	stream <<
	    address.street << " / " <<
	    address.zipCode << " / " <<
	    address.region;

	return stream;
}

std::ofstream&
operator<< (std::ofstream& outstream, const Address& address)
{
	outstream <<
		address.street << " :::::: " <<
		address.zipCode << " :::::: " <<
		address.region;

	return outstream;
}

std::ifstream&
operator>>(std::ifstream &instream, Address &a)
{
	try {
		string temp_str;
		getline(instream, temp_str);

		int div = temp_str.find(" :::::: ");
		int div2 = temp_str.find(" :::::: ", div + 1);
		if (div == string::npos || div2 == string::npos)
			throw FileReadingFailed("address: " + temp_str);

		a.street = temp_str.substr(0, div);
		a.zipCode = temp_str.substr(div + 8, div2 - div - 8);
		a.region = temp_str.substr(div2 + 8);

		if (!Address::verify_zip_code(a.zipCode))  // check if a valid zip-code was read
			throw FileReadingFailed("address: " + temp_str);

	}catch(const std::exception& e) {
		instream.setstate(ios::failbit);
		a.street = "Undefined Street";
		a.zipCode = "XXXX-XXX";
		a.region = "Undefined Region";

		cerr << e.what() << endl;
	}

	return instream;
}
