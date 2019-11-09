#include "../include/museum_network.h"

using namespace std;


/* Methods for Cards */
void MuseumNetwork::addCard(Card* card){
	int i;
	for (i = 0; i < this->cards.size(); ++i) {
		if(card->get_cc() == this->cards.at(i)->get_cc())
			throw(CardAlreadyExists(card->get_cc()));
	}
	this->cards.push_back(card);
}

void MuseumNetwork::removeCard(const Card *card_to_be_removed){
	vector<Card*>::iterator iter;
	iter = (find_if(this->cards.begin(), this->cards.end(),
			[&card_to_be_removed](Card *lhs){return( *lhs == *card_to_be_removed ); }));

	if(iter != this->cards.end()) // If the card is found
		cards.erase(iter);
	else
		throw(NoSuchCard(card_to_be_removed->get_cc()));
}

void MuseumNetwork::removeCards(const std::vector<Card*> &cards_to_be_removed){
	/* Given a vector of pointers to cards, remove all of the cards in the network are
	present in the given vector. */
	int i;
	for (i = 0; i < cards_to_be_removed.size(); ++i) {
		removeCard(cards_to_be_removed.at(i));
	}
}
void modifyCard(Card* card_to_be_changed);
void MuseumNetwork::listCards(const std::vector<Card*> &cards_to_be_listed, const string &delim) const{
	int i;
	for (i = 0; i < this->cards.size(); ++i) {
		cout << *(cards.at(i));
		cout << delim;
	}
}
void importCards(std::string cards_file_name);
void exportCards(std::string cards_file_name);
