#ifndef CARDS_H
#define CARDS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "address.h"
#include "date.h"
#include "../include/exceptions.h"
#include "../include/utilities.h"

/** @brief	how old (in days) do you have to be in order to be able to get a Silver card */
#define ELDERY_MIN_AGE (65 * 365)
/** @brief	can only renew card with max 60 days until expiration */
#define MAX_DAYS_BEFORE_RENEW 60
/** @brief	for formatted outputs */
#define CARDS_OUTPUT_DELIM 15

/** @brief	identifier of the Individual Card type */
#define INDIVIDUALCARD_TYPE 0
/** @brief	identifier of the UniCard Card type */
#define UNICARD_TYPE 1
/** @brief	identifier of the Silver Card type */
#define SILVERCARD_TYPE 2


/**
 * @brief	Abstract class to save and handle registered users information and their cards
 */
class Card {
private:
	unsigned int cc;
	std::string contact, name;
	Date creation_date, birth_date, expiration_date;
	Address address;
public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor of the class Time
	 *
	 * @details	Card class is abstract so it can't be instantiated
	 */
	Card() = default;
	/**
	 * @brief	Full constructor of the class Card
	 *
	 * @details	Card class is abstract so it can't be instantiated
	 *
	 * @param name		Name of the user
	 * @param contact	Contact of the user (can be an email address, phone number, etc.)
	 * @param cc		CC number of the user
	 * @param birth_date	Date of birth of the user
	 * @param address	User address
	 */
	Card(const std::string &name, const std::string &contact, const unsigned int cc, const Date &birth_date, const Address &address);

	/* DESTRUCTOR */
	/**
	 * @brief	Default destructor for the class Card
	 */
	virtual ~Card() = default;

	/* OTHER METHODS */
	/**
	 * @brief	Read a card information from std::cin with prompts (given through the std::cout)
	 *
	 * @details	The function will create a new Card class of the current type and make the pointer point to it
	 *
	 * @param c	Pointer to a Card class
	 */
	static void cin_read_card(Card* &c);

	/**
	 * @brief	Check if the Card is not expired
	 *
	 * @return	true, if expiration_date appears chronologically later than the current system date
	 */
	bool isvalid() const;
	/**
	 * @brief	Renews the user card
	 *
	 * @throws	TooEarlyToRenewCard	when the card is valid and there are more than MAX_DAYS_BEFORE_RENEW until renewal
	 */
	void renew();

	/* setters */
	/**
	 * @brief	Changes user's saved contact
	 *
	 * @param contact	new user contact
	 */
	void set_contact(const std::string &contact) { this->contact = contact; };
	/**
	 * @brief	Changes user's saved name
	 *
	 * @param name		new user name
	 */
	void set_name(const std::string &name) { this->name = name; };
	/**
	 * @brief	Changes user's saved birth date
	 *
	 * @param d		new user birth date
	 */
	void set_birth_date(const Date &d) { this->birth_date = d; };
	/**
	 * @brief	Changes user's saved address
	 *
	 * @param a		new user saved address
	 */
	void set_address(const Address &a) { this->address = a; }

	/* getters */
	/**
	 * @brief	get user's saved CC
	 *
	 * @return	user's CC
	 */
	unsigned int get_cc() const;
	/**
	 * @brief	get user's saved contact
	 *
	 * @return	user's contact
	 */
	std::string get_contact() const;
	/**
	 * @brief	get user's saved name
	 *
	 * @return	user's name
	 */
	std::string get_name() const;
	/**
	 * @brief	get user's saved creation date
	 *
	 * @return	card's creation date
	 */
	Date get_creation_date() const;
	/**
	 * @brief	get user's saved birth date
	 *
	 * @return	user's birth date
	 */
	Date get_birth_date() const;
	/**
	 * @brief	get user's saved expiration date
	 *
	 * @return	card's expiration date
	 */
	Date get_expiration_date() const;
	/**
	 * @brief	get user's saved address
	 *
	 * @return	user's address
	 */
	Address get_address() const;
	/**
	 * @brief	get user's card type
	 *
	 * @return	user's card type id
	 */
	virtual int get_type() const = 0;

	/* INSERTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded ostream insertion operator
	 *
	 * @details	Mainly used with std::cout to show formated information on screen
	 *
	 * @param outstream	Reference to the ostream object to insert info to
	 * @param t		Reference to the Card object whose info will be inserted in the ostream
	 *
	 * @return	Reference to the ostream object, 'outstream', passed in the parameters
	 */
	friend std::ostream& operator<<(std::ostream &outstream, const Card &c);
	/**
	 * @brief	Overloaded ofstream insertion operator
	 *
	 * @details	Used to save information on a file so it can be read again at a later date
	 *
	 * @param outstream	Reference to the ofstream object to insert info to
	 * @param t		Reference to the Card object whose info will be inserted in the ofstream
	 *
	 * @return	Reference to the ofstream object, 'outstream', passed in the parameters
	 */
	friend std::ofstream& operator<<(std::ofstream &outstream, const Card &c);
	friend std::ifstream& operator>>(std::ifstream &instream, Card* &c);
};


class IndividualCard: public Card {  // type 0
public:
	IndividualCard() = default;
	IndividualCard(const std::string &name, const std::string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		: Card(name, contact, cc, birth_date, address) {};

	/* GETTERS */
	/**
	 * @brief	get user's card type
	 *
	 * @return	user's card type id
	 */
	int get_type() const { return INDIVIDUALCARD_TYPE; };
};


class UniCard: public Card {  // type 1
public:
	UniCard() = default;
	UniCard(const std::string &name, const std::string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* GETTERS */
	/**
	 * @brief	get user's card type
	 *
	 * @return	user's card type id
	 */
	int get_type() const { return UNICARD_TYPE; };
};


class SilverCard: public Card {  // type 2
public:
	SilverCard() = default;
	SilverCard(const std::string &name, const std::string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* GETTERS */
	/**
	 * @brief	get user's card type
	 *
	 * @return	user's card type id
	 */
	int get_type() const { return SILVERCARD_TYPE; };
};

/* COMPARISON OPERATOR OVERLOAD */
/**
 * @brief	Overloaded equality test operator
 *
 * @param lhs	Reference to one of the Card objects to be tested
 * @param rhs	Reference to one of the Card objects to be tested
 *
 * @return	true, if the 2 objects have the same CC\n
		false, otherwise
 */
bool operator==(const Card& lhs, const Card& rhs);
/**
 * @brief	Overloaded inequality test operator
 *
 * @param lhs	Reference to one of the Card objects to be tested
 * @param rhs	Reference to one of the Card objects to be tested
 *
 * @return	true, if the 2 objects have different CC's\n
		false, otherwise
 */
bool operator!=(const Card& lhs, const Card& rhs);

#endif	// CARDS_H
