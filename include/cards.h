#ifndef CARDS_H
#define CARDS_H

#include <string>

#include "address.h"
#include "date.h"

using namespace std;

#define MAX_DAYS_BEFORE_RENEW 60  // can only renew card with max 60 days until expiration

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
	virtual short get_type() const = 0;
};

class IndividualCard: public Card {
private:
	static float discount;
	static float cost;
public:
	IndividualCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* getters */
	float get_discount() const { return IndividualCard::discount; };
	float get_cost() const { return IndividualCard::cost; };
	short get_type() const { return 0; };
};

class UniCard: public Card {
private:
	static float discount;
	static float cost;
public:
	UniCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* getters */
	float get_discount() const { return UniCard::discount; };
	float get_cost() const { return UniCard::cost; };
	short get_type() const { return 1; };
};

class SilverCard: public Card {
private:
	static float discount;
	static float cost;
public:
	SilverCard(const string &name, const string &contact, unsigned int cc, const Date &birth_date, const Address &address)
		:Card(name, contact, cc, birth_date, address) {};

	/* getters */
	float get_discount() const { return SilverCard::discount; };
	float get_cost() const { return SilverCard::cost; };
	short get_type() const { return 2; };
};

std::ostream& operator<<(std::ostream &outstream, const IndividualCard &c);
std::ofstream& operator<<(std::ofstream &outstream, const IndividualCard &c);

std::ostream& operator<<(std::ostream &outstream, const UniCard &c);
std::ofstream& operator<<(std::ofstream &outstream, const UniCard &c);

std::ostream& operator<<(std::ostream &outstream, const SilverCard &c);
std::ofstream& operator<<(std::ofstream &outstream, const SilverCard &c);

//std::ifstream& operator>>(std::ifstream &instream, const Card &c);

#endif  // CARDS_H
