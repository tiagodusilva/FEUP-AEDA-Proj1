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
	/* Constructors */
	MuseumNetwork() = default;
	MuseumNetwork(std::vector<Card*> card_vector, std::vector<Enterprise> enterprise_vector, std::vector<Museum> museum_vector) :
		cards(card_vector), enterprises(enterprise_vector), museums(museum_vector) {};
	MuseumNetwork(std::string museum_file_name) { this->importFiles(museum_file_name); };

	/* Methods for Cards */
	void addCard(Card* card);
	void removeCards(const std::vector<const Card*> &cards_to_be_removed);
	void modifyCard(Card* card_to_be_changed);
	void listCards(const std::vector<const Card*> &cards_to_be_listed);
	void importCards(std::string cards_file_name);
	void exportCards(std::string cards_file_name);

	/* Methods for Enterprises */
	void addEnterprise(Enterprise enterprise);
	void removeEnterprises(const std::vector<Enterprise> &enterprises_to_be_removed);
	void modifyEnterprise(Enterprise enterprise_to_be_changed);
	void listEnterprise(const std::vector<Enterprise> &enterprises_to_be_listed);
	void importEnterprises(std::string enterprise_file_name);
	void exportEnterprises(std::string enterprise_file_name);
	// First three are low priority

	/* Methods for Museums */
	void addMuseum(Museum museum);
	void removeMuseums(const std::vector<Museum> &museum_to_be_removed);
	void modifyMuseum(Museum museum_to_be_changed);
	void listMuseum(const std::vector<Museum> &museum_to_be_listed);
	void importMuseums(std::string museum_file_name);
	void exportMuseums(std::string museum_file_name);
	// First three are low priority

	/* Methods for Events */
	void listEvents(const std::vector<Event> &events_to_be_listed);
	void updateEvents(std::string enterprise_file_name); // Reads new Enterprise file and updates it

	/* Getters for Menus */
	std::vector<const Card*> getCards() const;
	std::vector<Enterprise> getEnterprises() const;
	std::vector<Museum> getMuseums() const;
	std::vector<Event> getEvents() const; // Iterates through all enterprises to retreive all events

	/* File input and output */
	void importFiles(std::string network_file_name);
	void exportFiles(std::string network_file_name, std::string museum_file_name, std::string enterprise_file_name, std::string cards_file_name);

};


#endif	// MUSEUM_NETWORK_H
