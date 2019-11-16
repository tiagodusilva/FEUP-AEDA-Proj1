/** @file address.h */
#ifndef ADDRESS_H
#define ADDRESS_H

#include <fstream>
#include <iostream>
#include <string>

/** @defgroup address_grp Address module */

/** @addtogroup	address_grp
  *
  * @brief	Code related to the handling, saving and comparisons of Addresses
  *
  * @{
  */

/** @brief	Half-address' zip-code (reserved for addresses that only have a set region) */
#define HALF_ADDR_ZIPCODE "0000-000"

/**
 * @brief	Class that saves and handles address information in our project
 *
 * @details	There are 2 types of addresses: full-addresses (referred just as addresses), containing the full information\n
 *		and half-addresses containing only a region (identified by the 0000-000 zip-code)
 */
class Address
{
private:
	/** @brief	the address' street (undefined for half-address and instances of the default constructor) */
	std::string street;
	/** @brief	the address' street zip-code (0000-000 for half-address and XXXX-XXX for instance of the default constructor) */
	std::string zipCode;
	/** @brief	the address' region (undefined for instances of the default constructor) */
	std::string region;
public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor of the class Address
	 *
	 * @details	Creates an Address object that contains default undefined information
	 */
	Address();
	/**
	 * @brief	Constructor of the class Address for half-addresses
	 *
	 * @param region	representing the region that identifies an half-address
	 *
	 * @throw InvalidObject	when the given region can be considered an empty field
	 */
	Address(const std::string &region);
	/**
	 * @brief	Constructor of the class Address
	 *
	 * @param street	representing the address' street
	 * @param zipCode	representing the address' zip-code
	 * @param region	representing the address' region
	 *
	 * @throw InvalidObject	when the given region or street can be considered an empty field or the zip-code is invalid (also can't use the half-address reserved zip-code here)
	 */
	Address(const std::string &street, const std::string &zipCode, const std::string &region);

	/* GETTERS */
	/**
	 * @brief	Getter for the saved street information
	 *
	 * @return	address' street information currently saved in the class
	 */
	std::string getStreet() const;
	/**
	 * @brief	Getter for the saved zip-code information
	 *
	 * @return	address' zip-code information currently saved in the class
	 */
	std::string getZipCode() const;
	/**
	 * @brief	Getter for the saved region information
	 *
	 * @return	address' region information currently saved in the class
	 */
	std::string getRegion() const;

	/* OTHER MEMBER FUNCTIONS */
	/**
	 * @brief	Checks whether or not a given zip-code is considered valid
	 *
	 * @param zip	Reference to the zip-code to be tested
	 *
	 * @return	true, if the given zip-code is not 0000-000 and is of the XXXX-XXX format\n
	 *		false, otherwise
	 */
	static bool verify_zip_code(const std::string &zip);

	/* INSERTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded ostream insertion operator
	 *
	 * @details	Mainly used with std::cout to show formated information on screen
	 *
	 * @param outstream	Reference to the ostream object to insert info to
	 * @param a		Reference to the Address object whose info will be inserted in the ostream
	 *
	 * @return	Reference to the ostream object, 'outstream', passed in the parameters
	 */
	friend std::ostream& operator<<(std::ostream& outstream, const Address &a);
	/**
	 * @brief	Overloaded ofstream insertion operator
	 *
	 * @details	Used to save information on a file so it can be read again at a later date
	 *
	 * @param outstream	Reference to the ofstream object to insert info to
	 * @param a		Reference to the Address object whose info will be inserted in the ofstream
	 *
	 * @return	Reference to the ofstream object, 'outstream', passed in the parameters
	 */
	friend std::ofstream& operator<<(std::ofstream& outstream, const Address &a);

	/* EXTRACTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded istream extraction operator
	 *
	 * @details	Mainly used with std::cin to get information from the user
	 *
	 * @param instream	Reference to the istream object to extract info from
	 * @param a		Reference to the Address object where the read information is saved
	 *
	 * @return	Reference to the istream object, 'instream', passed in the parameters
	 */
	friend std::istream& operator>>(std::istream &instream, Address &a);
	/**
	 * @brief	Overloaded ifstream extraction operator
	 *
	 * @details	Used to read information that has been saved to a file previously
	 *
	 * @param instream	Reference to the ifstream object to extract info from
	 * @param a		Reference to the Address object where the read information is saved
	 *
	 * @return	Reference to the ifstream object, 'instream', passed in the parameters
	 */
	friend std::ifstream& operator>>(std::ifstream &instream, Address &a);
};

/* COMPARISON OPERATOR OVERLOAD */
/** @relatesalso Address
 * @brief	Overloaded equality test operator
 *
 * @param lhs	Reference to one of the Address objects to be tested
 * @param rhs	Reference to one of the Address objects to be tested
 *
 * @return	true, if the 2 Address objects have the same values for street, zip-code and region\n
 *		false, otherwise
 */
bool operator==(const Address& lhs, const Address& rhs);

/** @} */

#endif // ADDRESS_H
