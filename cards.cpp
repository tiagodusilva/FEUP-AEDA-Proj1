#include "cards.h"

// We were careful and this call will never throw an exception (except if the system doesn't have any memory allocated)
Date Card::expiration = Date(1, 0, 0);
short Card::discount = 25;
float UniCard::cost = 32.45;
float SilverCard::cost = 30.00;
float IndividualCard::cost = 54.90;

Card::Card(Date c_date) {
    creation_date = c_date;
    expiration_date = c_date;
}
