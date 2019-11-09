#include "../include/museum_network.h"

using namespace std;



/* Cards */

void MuseumNetwork::addCard(Card* card) {
	int i;
	for (i = 0; i < this->cards.size(); ++i) {
		if(*card == *(this->cards.at(i)))
			throw(CardAlreadyExists(card->get_cc()));
	}
	this->cards.push_back(card);
}


void MuseumNetwork::removeCard(const Card *card) {
	vector<Card*>::iterator iter;
	iter = (find_if(this->cards.begin(), this->cards.end(),
			[&card](Card *lhs){return( *lhs == *card ); }));

	if(iter != this->cards.end()) // If the card is found
		cards.erase(iter);
	else
		throw(NoSuchCard(card->get_cc()));
}


void MuseumNetwork::removeCards(const std::vector<Card*> &cards_to_be_removed) {
	/* Given a vector of pointers to cards, remove all of the cards in the network are
	present in the given vector. */

	int i;
	for (i = 0; i < cards_to_be_removed.size(); ++i) {
		removeCard(cards_to_be_removed.at(i));
	}
}


void MuseumNetwork::modifyCard(Card* card_to_be_modified_to) {
	/* Modifies the card in the cards vector which has the same cc as the card_to_be_modified_to.
	   The data-members of the element of the vector will then be set to card_to_be_modified_to.
	*/
	vector<Card*>::iterator iter;
	iter = (find_if(this->cards.begin(), this->cards.end(),
			[&card_to_be_modified_to](Card *lhs){ return( *lhs == *card_to_be_modified_to ); }));

	if(iter != this->cards.end())
		(*iter) = card_to_be_modified_to;
	else
		throw(NoSuchCard(card_to_be_modified_to->get_cc()));
}


void MuseumNetwork::listCards(const std::vector<Card*> &cards_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < cards_to_be_listed.size(); ++i) {
		cout << *(cards_to_be_listed.at(i));
		cout << delim;
	}
}

void importCards(std::string cards_file_name);
void exportCards(std::string cards_file_name);



/* Enterprises */

void MuseumNetwork::listEnterprises(const std::vector<Enterprise> &enterprises_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < enterprises_to_be_listed.size(); ++i) {
		cout << enterprises_to_be_listed.at(i);
		cout << delim;
	}
}

void MuseumNetwork::listEnterprises(const string &delim) const {
	this->listEnterprises(this->getEnterprises(), delim);
}


void MuseumNetwork::addEnterprise(Enterprise enterprise) {
	int i;
	for (i = 0; i < this->enterprises.size(); ++i) {
		if(enterprise.get_name() == this->enterprises.at(i).get_name()) //TODO do with == operator
			throw(EnterpriseAlreadyExists(enterprise.get_name()));
	}
	this->enterprises.push_back(enterprise);
}



/* Museums */

void MuseumNetwork::listMuseums(const std::vector<Museum> &museums_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < museums_to_be_listed.size(); ++i) {
		cout << museums_to_be_listed.at(i);
		cout << delim;
	}
}

void MuseumNetwork::listMuseums(const string &delim) const {
	this->listMuseums(this->getMuseums(), delim);
}


void MuseumNetwork::addMuseum(Museum museum) {
	int i;
	for (i = 0; i < this->museums.size(); ++i) {
		if(museum.get_name() == this->museums.at(i).get_name()) //TODO do with == operator
			throw(MuseumAlreadyExists(museum.get_name()));
	}
	this->museums.push_back(museum);
}

/* Eventos */

void MuseumNetwork::listEvents(const std::vector<Event> &events_to_be_listed, const string &delim) const {
	int i;
	for (i = 0; i < events_to_be_listed.size(); ++i) {
		cout << events_to_be_listed.at(i);
		cout << delim;
	}
}

void MuseumNetwork::listEvents(const string &delim) const{
	this->listEvents(getEvents());
}

vector<Event> MuseumNetwork::getEvents() const {
	int i, number_events(0);
	/* get size of the vector so that it doesn't have to realocate memory */
	for (i = 0; i < enterprises.size(); ++i) {
		number_events += 1;//enterprises.at(i).get_events().size();
	}

	vector<Event> events;
	for (auto &ent: this->enterprises) // Iterate through enterpises
		for (auto &x: ent.get_events()) { // Iterate through set of events
			 events.push_back(x);
		}

	return events;
}
