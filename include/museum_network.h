#ifndef MUSEUM_NETWORK_H
#define MUSEUM_NETWORK_H

#include <iostream>
#include <vector>
#include <string>

#include "cards.h"
#include "enterprise.h"
#include "museum.h"

class MuseumNetwork{
private:
	/* Containers */
	std::vector<Card*> cards;
	std::vector<Enterprise> enterprises;
	std::vector<Museum> museums;

public:
	MuseumNetwork() = default;

	/* Methods for Cards */
	void addCard(Card* card);
	void removeCards(Card* card);
	void modifyCard(Card* card_to_be_changed);
	void listCards(Card* card);

	/* Methods for Enterprises */
	void addEnterprise(Enterprise enterprise);
	void removeEnterprises(const std::vector<Enterprise> &enterprises_to_be_removed);
	void modifyEnterprise(Enterprise enterprise_to_be_changed);
	void listEnterprise(const std::vector<Enterprise> &enterprises_to_be_listed);
	// First three are low priority

	/* Methods for Museums */
	void addMuseum(Museum museum);
	void removeMuseums(const std::vector<Museum> &museum_to_be_removed);
	void modifyMuseum(Museum museum_to_be_changed);
	void listMuseum(const std::vector<Museum> &museum_to_be_listed);

	/* Getters for menus */
	std::vector<const Card*> getCards() const;
	std::vector<Enterprise> getEnterprises() const;
	std::vector<Museum> getMuseums() const;
	std::vector<Event> getEvents() const; // Iterates through all enterprises to retreive all events

	/* File input and output */
	void updateEvents(std::string enterprise_file_name); // Reads new Enterprise file and updates it
	void importFiles(std::string network_file_name);
	void exportFiles(std::string network_file_name, std::string museum_file_name, std::string enterprise_file_name, std::string cards_file_name);

};


#endif	// MUSEUM_NETWORK_H
