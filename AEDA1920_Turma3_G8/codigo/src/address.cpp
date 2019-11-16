#include "../include/address.h"

#include "../include/exceptions.h"
#include "../include/utilities.h"

using namespace std;

Address::Address()
{
	this->street = "Undefined Street";
	this->zipCode = "XXXX-XXX";
	this->region = "Undefined Region";
}

Address::Address(const string &region)
{
	if (utl::isStrEmpty(region))
		throw InvalidObject("Address", "region must not be considered empty");

	this->street = "Undefined Street";
	this->zipCode = HALF_ADDR_ZIPCODE;
	this->region = region;
}

Address::Address(const string &street, const string &zipCode, const string &region)
{
	/* 0000-000 is not valid for zipcodes inputed by the user */
	if (zipCode == HALF_ADDR_ZIPCODE || !Address::verify_zip_code(zipCode) ||
	    utl::isStrEmpty(street) || utl::isStrEmpty(region))
		throw InvalidObject("Address", "zip code in the incorrect format or 0000-000");

	this->street = street;
	this->zipCode = zipCode;
	this->region = region;
}

string
Address::getStreet() const
{
	return this->street;
}

string
Address::getZipCode() const
{
	return this->zipCode;
}

string
Address::getRegion() const
{
	return this->region;
}

bool
Address::verify_zip_code(const string &zip)
{
	if (zip.size() != 8)
		return false;

	if (zip[4] != '-')
		return false;

	return isdigit(zip[0]) && isdigit(zip[1]) && isdigit(zip[2]) &&
		isdigit(zip[3]) && isdigit(zip[5]) && isdigit(zip[6]) && isdigit(zip[7]);
}

bool
operator==(const Address& lhs, const Address& rhs)
{
	if (lhs.getZipCode() == HALF_ADDR_ZIPCODE || rhs.getZipCode() == HALF_ADDR_ZIPCODE)
		return lhs.getRegion() == rhs.getRegion();

	return (lhs.getRegion() == rhs.getRegion() &&
		lhs.getStreet() == rhs.getStreet() &&
		lhs.getZipCode() == rhs.getZipCode());

}

std::ostream&
operator<<(std::ostream& outstream, const Address &a)
{
	if (a.zipCode == HALF_ADDR_ZIPCODE)
		outstream << a.region;
	else {
		outstream <<
			a.street << " / " <<
			a.zipCode << " / " <<
			a.region;
	}

	return outstream;
}


std::ofstream&
operator<<(std::ofstream& outstream, const Address &a)
{
	outstream << "" <<
		a.street << " :::::: " <<
		a.zipCode << " :::::: " <<
		a.region;

	return outstream;
}


std::istream&
operator>>(std::istream &instream, Address &a)
{
	try {
		//cout << "Address (street name/XXXX-XXX/region name  or  region)? ";

		/* check if address is well formed */
		string temp_address;
		getline(instream, temp_address);
		if (utl::isStrEmpty(temp_address))  // check if input is empty
			throw UserInputReadingFailure("Address given by user is empty");

		int div = temp_address.find("/");
		if (div == string::npos) {
			/* half address (only region) */
			a.street = "Undefined Street";
			a.zipCode = HALF_ADDR_ZIPCODE;
			a.region = utl::trim(temp_address);
			return instream;
		}

		/* full address */
		int div2 = temp_address.find("/", div + 1);
		if (div2 == string::npos)
			throw UserInputReadingFailure("Address given by user is malformed: " + temp_address);

		/* divide address into relevant parts */
		a.street = temp_address.substr(0, div);
		a.zipCode = temp_address.substr(div + 1, div2 - div - 1);
		a.region = temp_address.substr(div2 + 1);

		/* check if a valid zip-code was read */
		if (a.zipCode == HALF_ADDR_ZIPCODE || !Address::verify_zip_code(a.zipCode) ||
		    utl::isStrEmpty(a.street) || utl::isStrEmpty(a.region))
			throw UserInputReadingFailure("Address given by user is malformed (or 0000-000) or a field is considered an empty string: " + temp_address);

	}catch(const std::exception& e) {
		instream.setstate(ios::failbit);
		a.street = "Undefined Street";
		a.zipCode = "XXXX-XXX";
		a.region = "Undefined Region";

		cerr << e.what() << endl;
	}

	return instream;
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

		/* check if a valid zip-code was read */
		if (!Address::verify_zip_code(a.zipCode) ||
		    utl::isStrEmpty(a.street) || utl::isStrEmpty(a.region))
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
