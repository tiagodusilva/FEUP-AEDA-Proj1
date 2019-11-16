/** @file museum_network.h */
#ifndef MUSEUM_NETWORK_H
#define MUSEUM_NETWORK_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "cards.h"
#include "enterprise.h"
#include "exceptions.h"
#include "museum.h"

/** @addtogroup	museum_grp
  * @{
  */

class MuseumNetwork {
private:
	/** @brief	List of the different discounts applied to Cards */
	float discount[3];
	/** @brief	List of the different Card's creation/renewal cost */
	float cost[3];
	/** @brief	List of pointers to all the registered User's Cards */
	std::vector<Card*> cards;
	/** @brief	List of all the Enterprises associated with the Museum Network */
	std::vector<Enterprise> enterprises;
	/** @brief	List of all the Museums that are part of the Museum Network */
	std::vector<Museum> museums;

public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	MuseumNetwork() = default;
	/**
	 * @brief	Constructor for the MuseumNetwork class
	 *
	 * @param card_vector		Vector of pointers to registered user Cards to add to the Network
	 * @param enterprise_vector	Vector of enterprises to add to the Network
	 * @param museum_vector		Vector of museums to add to the Network
	 */
	MuseumNetwork(std::vector<Card*> &card_vector, std::vector<Enterprise> &enterprise_vector, std::vector<Museum> &museum_vector) :
		cards(card_vector), enterprises(enterprise_vector), museums(museum_vector) {}
	/**
	 * @brief	Constructor for the MuseumNetwork class
	 *
	 * @param config_file_name	Name of the file to read the new Museum Network configuration from\n
					Including the names of the files that containing the new information
	 */
	MuseumNetwork(std::string config_file_name) { this->importFiles(config_file_name); }


	/* METHODS FOR CARDS */
	/**
	 * @brief	Add a new user Card to the network
	 *
	 * @param card	Pointer (to a new user Card) to be added to the network
	 */
	void addCard(Card* card);
	/**
	 * @brief	Search for the given Card on the network and remove it
	 *
	 * @param card	Pointer to the Card to find and remove from the network
	 */
	void removeCard(const Card* card);
	/**
	 * @brief	Search for the given Cards on the network and remove them
	 *
	 * @param cards_to_be_removed	List of pointers to the Cards to be removed from the network
	 */
	void removeCards(const std::vector<Card*> &cards_to_be_removed);

	void listCards(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listCards(const std::vector<Card*> &cards_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	float getDiscount(const unsigned card_type) const;
	float getCost(const unsigned card_type) const;
	void importCards(std::string cards_file_name);
	void exportCards(std::string cards_file_name) const;


	/* Methods for Enterprises */
	void addEnterprise(Enterprise enterprise);

	void removeEnterprise(const Enterprise &enterprise_to_be_removed);
	void removeEnterprises(std::vector<Enterprise> &museum_to_be_removed);

	void modifyEnterprise(const Enterprise &old_enterprise, const Enterprise &new_enterprise);

	void listEnterprises(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listEnterprises(const std::vector<Enterprise> &enterprises_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void importEnterprises(std::string enterprise_file_name);
	void exportEnterprises(std::string enterprise_file_name) const;
	// First three are low priority


	/* Methods for Museums */
	void addMuseum(Museum museum);

	void removeMuseum(const Museum &museum_to_be_removed);
	void removeMuseums(std::vector<Museum> &museum_to_be_removed);

	void modifyMuseum(const Museum &old_museum, const Museum &new_museum);

	void listMuseums(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listMuseums(const std::vector<Museum> &museum_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void importMuseums(std::string museum_file_name);
	void exportMuseums(std::string museum_file_name) const;
	// First three are low priority


	/* Methods for Events */
	void listEvents(unsigned card_type, const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listEvents(const std::vector<Event> &events_to_be_listed,
			unsigned card_type, const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listEvents(const std::string &delim='\n' + std::string(64, '-') + '\n') const;
	void listEvents(const std::vector<Event> &events_to_be_listed,
			const std::string &delim='\n' + std::string(64, '-') + '\n') const;

	void addEvent(const Enterprise &enterprise, Event &event);

	void removeEvent(const Event &event_to_be_removed, Enterprise &enterprises);
	void removeEvents(std::vector<Event> &events_to_be_removed);

	void purchaseEvent(const unsigned cc, Event event);
	void updateEvents(std::string enterprise_file_name); // Reads new Enterprise file and updates it


	/* Getters for use with Menus */
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

/** @} */

#endif	// MUSEUM_NETWORK_H
