#ifndef MUSEUM_NETWORK_H
#define MUSEUM_NETWORK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "algorithm"
#include "cards.h"
#include "enterprise.h"
#include "exceptions.h"
#include "museum.h"

//TODO Tornar list static

class MuseumNetwork{
private:
	float individual_discount;
	float individual_cost;
	float silver_discount;
	float silver_cost;
	float uni_discount;
	float uni_cost;
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

	void removeCard(const Card* card);
	void removeCards(const std::vector<Card*> &cards_to_be_removed);

	void modifyCard(Card* card);

	void listCards(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listCards(const std::vector<Card*> &cards_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void importCards(std::string cards_file_name);
	void exportCards(std::string cards_file_name) const;


	/* Methods for Enterprises */
	void addEnterprise(Enterprise enterprise);

	void removeEnterprises(const std::vector<Enterprise> &enterprises_to_be_removed);

	void modifyEnterprise(Enterprise enterprise);

	void listEnterprises(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listEnterprises(const std::vector<Enterprise> &enterprises_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void importEnterprises(std::string enterprise_file_name);
	void exportEnterprises(std::string enterprise_file_name) const;
	// First three are low priority


	/* Methods for Museums */
	void addMuseum(Museum museum);

	void removeMuseums(const std::vector<Museum> &museum_to_be_removed);

	void modifyMuseum(Museum museum_to_be_changed);

	void listMuseums(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listMuseums(const std::vector<Museum> &museum_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void importMuseums(std::string museum_file_name);
	void exportMuseums(std::string museum_file_name) const;
	// First three are low priority


	/* Methods for Events */
	void listEvents(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listEvents(const std::vector<Event> &events_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void updateEvents(std::string enterprise_file_name); // Reads new Enterprise file and updates it


	/* Getters for Menus */
	std::vector<Card*> getCards() const { return this->cards; };
	std::vector<Enterprise> getEnterprises() const { return this->enterprises; };
	std::vector<Museum> getMuseums() const { return this->museums; };
	std::vector<Event> getEvents() const; // Iterates through all enterprises to retreive all events


	/* File input and output */
	void importFiles(std::string network_file_name);
	void exportFiles( std::string cards_file_name, std::string museum_file_name,
			std::string enterprise_file_name, std::string config_file_name="files/network_config.sadjson" ) const;

    friend std::ofstream& operator<<(std::ofstream &outfstream, const MuseumNetwork &network);
    friend std::ifstream &operator>>(std::ifstream &infstream, MuseumNetwork &network);
};


#endif	// MUSEUM_NETWORK_H
