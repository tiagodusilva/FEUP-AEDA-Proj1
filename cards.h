#ifndef FEUP_AEDA_PROJ1_CARDS_H
#define FEUP_AEDA_PROJ1_CARDS_H

#include "date.h"

class Date;

class Card {
private:
    static Date expiration;
    static short discount;
    Date creation_date, expiration_date;
public:
    explicit Card(Date c_date);
};

class UniCard: Card {
private:
    static float cost;
public:
    explicit UniCard(Date c_date): Card(c_date) {};
};

class SilverCard: Card {
private:
    static float cost;
public:
    explicit SilverCard(Date c_date): Card(c_date) {};
};

class IndividualCard: Card {
private:
    static float cost;
public:
    explicit IndividualCard(Date c_date): Card(c_date) {};
};

#endif //FEUP_AEDA_PROJ1_CARDS_H
