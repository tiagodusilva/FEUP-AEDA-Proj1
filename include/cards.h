#ifndef CARDS_H
#define CARDS_H

#include "date.h"

class Date;

class Card {
private:
	static Date expiration;
	static short discount;
	Date creation_date, expiration_date;
public:
	// rapido imagina o construtor com explicit imagina.. AI puta que pareu o windows update
	Card(Date c_date);
	bool isvalid() const;
	void renew() const;
};

class UniCard: Card {
private:
	static float cost;
	static short type;
public:
	UniCard(Date c_date): Card(c_date) {};
};

class SilverCard: Card {
private:
	static float cost;
	static short type;
public:
	SilverCard(Date c_date): Card(c_date) {};
};

class IndividualCard: Card {
private:
	static float cost;
	static short type;
public:
	IndividualCard(Date c_date): Card(c_date) {};
};

#endif  // CARDS_H
