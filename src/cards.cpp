#include "../include/cards.h"

#include <algorithm>
#include <sstream>
#include <iomanip>

#include "../include/exceptions.h"
#include "../include/utilities.h"

using namespace std;

float IndividualCard::cost = 54.90;
float IndividualCard::discount = 0.25;
float UniCard::cost = 32.45;
float UniCard::discount = 0.25;
float SilverCard::cost = 30.00;
float SilverCard::discount = 0.25;

Card::Card(const string &name, const string &contact, const unsigned int cc, const Date &birth_date, const Address &address)
	:creation_date(), expiration_date()
{
	this->name = name;
	this->contact = contact;
	this->cc = cc;
	this->birth_date = birth_date;
	this->address = address;

	this->expiration_date.ffyear();  // expiration date is 1 year from creation date
}


bool
Card::isvalid() const
{
	/* compare expiration date with current date */
	return this->expiration_date <= Date();
}


void
Card::renew()
{
	/* renewing adds 1 more year to the validity period of a card */
	try {
		/* check is card is already expired */
		if (this->isvalid()){
			if ((Date() - this->expiration_date) <= MAX_DAYS_BEFORE_RENEW)
				this->expiration_date.ffyear();
			else
				throw TooEarlyToRenewCard(this->name);
		}
		else {
			this->expiration_date = Date();  // compare with current date
			this->expiration_date.ffyear();  // move expiration date to 1 year from now
		}

	}catch(const std::exception& e) {
		// Do stuff here if necessary
		cerr << e.what() << endl;
	}

}


/* getters */
unsigned int
Card::get_cc() const
{
	return this->cc;
}

string
Card::get_contact() const
{
	return this->contact;
}

string
Card::get_name() const
{
	return this->name;
}

Date
Card::get_creation_date() const
{
	return this->creation_date;
}

Date
Card::get_birth_date() const
{
	return this->birth_date;
}

Date
Card::get_expiration_date() const
{
	return this->expiration_date;
}

Address
Card::get_address() const
{
	return this->address;
}

/* operator overload */
ostream&
operator<<(ostream &outstream, const Card &c)
{
	static const string type[3] = {"Individual Card", "University Card", "Silver Card"};

	outstream <<
		left << setw(CARDS_OUTPUT_DELIM) << "Name"	      << " : " << right << c.name << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "Type"	      << " : " << right << type[c.get_type()] << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "CC"	      << " : " << right << c.cc << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "Contact"	      << " : " << right << c.contact  << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "Address"	      << " : " << right << c.address << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "Birth date"      << " : " << right << c.birth_date << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "Creation date"   << " : " << right << c.creation_date << endl <<
		left << setw(CARDS_OUTPUT_DELIM) << "Expiration date" << " : " << right << c.expiration_date;

	return outstream;
}


std::ofstream&
operator<<(std::ofstream &outstream, const Card &c)
{
	outstream << c.name		     << endl;
	outstream << to_string(c.get_type()) << endl;
	outstream << to_string(c.cc)	     << endl;
	outstream << c.contact		     << endl;
	outstream << c.address		     << endl;
	outstream << c.birth_date	     << endl;
	outstream << c.creation_date	     << endl;
	outstream << c.expiration_date;

	return outstream;
}


std::ifstream&
operator>>(std::ifstream &instream, Card* &c)
{
	try {
		string temp_str;
		getline(instream, temp_str);

		/* instanciate right class */
		int type;
		instream >> type; utl::ignore(instream);
		if (type == 0)
			c = new IndividualCard;
		else if (type == 1)
			c = new UniCard;
		else if (type == 2)
			c = new SilverCard;
		else
			throw FileReadingFailed("No such card type");

		c->name = temp_str;
		instream >> c->cc; utl::ignore(instream);
		getline(instream, c->contact);
		instream >> c->address;
		instream >> c->birth_date;
		instream >> c->creation_date;
		instream >> c->expiration_date;

	}catch(const std::exception& e) {
		c = nullptr;
		instream.setstate(ios::failbit);

		cerr << e.what();
	}
	return instream;
}
