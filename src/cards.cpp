#include "../include/cards.h"

/* We were careful and this call will never throw an exception (except if the system doesn't have any memory allocated) */
Date Card::expiration = Date(1, 0, 0);
short Card::discount = 25;
float IndividualCard::cost = 54.90;
float UniCard::cost = 32.45;
float SilverCard::cost = 30.00;
short IndividualCard::type = 0;
short UniCard::type = 1;
short SilverCard::type = 2;

Card::Card(Date c_date)
{
	creation_date = c_date;
	expiration_date = c_date;
}

bool
Card::isvalid() const
{
	/* get current date */
	Date currentdate;
	currentdate.now();

	if (expiration_date < currentdate)
		return true;

	return false;
}

void
Card::renew() const
{
	// TODO SO PODER RENOVAR A QUANDO FALTAR 2 MESES PARA FIM DO PRAZO
	/* check is card is already expired */
	if (this->isvalid())
		this->expiration_date = this->expiration_date + expiration;

	else {
		Date currentdate;
		currentdate.now();  // get current date

		this->expiration_date = currentdate + expiration;
	}
}
