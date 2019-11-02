#ifndef CARDS_H
#define CARDS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "address.h"
#include "date.h"

#define MAX_DAYS_BEFORE_RENEW 60  // can only renew card with max 60 days until expiration

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
	Card(const string &name, const string &contact, const unsigned int cc, const Date &birth_date, const Address &address);
	~Card() = default;

	bool isvalid() const;
	void renew();

	/* setters */
	void set_contact(const string &contact) { this->contact = contact; };
	void set_name(const string &name) { this->name = name; };
	void set_birth_date(const Date &d) { this->birth_date = d; };
	void set_address(const Address &a) { this->address = a; }

	/* getters */
	unsigned int get_cc() const;
	string get_contact() const;
	string get_name() const;
	Date get_creation_date() const;
	Date get_birth_date() const;
	Date get_expiration_date() const;
	Address get_address() const;
	virtual int get_type() const = 0;
	virtual float get_discount() const = 0;
	virtual float get_cost() const = 0;

	/* operator overloads */
	friend std::ostream& operator<<(std::ostream &outstream, const Card &c);
	friend std::ofstream& operator<<(std::ofstream &outstream, const Card &c);
	friend std::ifstream& operator>>(std::ifstream &instream, Card* &c);
};


class IndividualCard: public Card {  // type 0
private:
	static float discount;
	static float cost;
public:
	IndividualCard() = default;
	IndividualCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		: Card(name, contact, cc, birth_date, address) {};

	/* getters */
	int get_type() const { return 0; };
	float get_discount() const { return IndividualCard::discount; };
	float get_cost() const { return IndividualCard::cost; };
};


class UniCard: public Card {  // type 1
private:
	static float discount;
	static float cost;
public:
	UniCard() = default;
	UniCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* getters */
	int get_type() const { return 1; };
	float get_discount() const { return UniCard::discount; };
	float get_cost() const { return UniCard::cost; };
};


class SilverCard: public Card {  // type 2
private:
	static float discount;
	static float cost;
public:
	SilverCard() = default;
	SilverCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* getters */
	int get_type() const { return 2; };
	float get_discount() const { return SilverCard::discount; };
	float get_cost() const { return SilverCard::cost; };
};

#endif  // CARDS_H
