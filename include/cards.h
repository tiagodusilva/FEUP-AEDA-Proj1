#ifndef CARDS_H
#define CARDS_H

#include <string>

#include "address.h"
#include "date.h"

using namespace std;

class Card {
private:
	unsigned int cc;
	string contact, name;
	Date creation_date, birth_date, expiration_date;
	Address address;
public:
	// rapido imagina o construtor com explicit imagina.. AI puta que pareu o windows update
	/* constructures */
	Card() = default;
	Card(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address);
	~Card() = default;

	bool isvalid() const;
	void renew();

	/* getters */
	unsigned int get_cc() const;
	string get_contact() const;
	string get_name() const;
	Date get_creation_date() const;
	Date get_birth_date() const;
	Date get_expiration_date() const;
	Address get_address() const;
	virtual short get_type() const;
};

class UniCard: Card {
private:
	static float discount;
	static float cost;
public:
	UniCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	short get_type() const {return 1;};
};

class SilverCard: Card {
private:
	static float discount;
	static float cost;
public:
	SilverCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	short get_type() const {return 2;};
};

class IndividualCard: Card {
private:
	static float discount;
	static float cost;
public:
	IndividualCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	short get_type() const {return 0;};
};

#endif  // CARDS_H
