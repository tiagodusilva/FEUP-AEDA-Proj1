/** @file museum_network.h */
#ifndef MUSEUM_NETWORK_H
#define MUSEUM_NETWORK_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "cards.h"
#include "enterprise.h"
#include "exceptions.h"
#include "museum.h"
#include "repairenterprise.h"
#include "stateworker.h"

/**
 * @mainpage	Second project for the AEDA chair (FEUP MIEIC 2019/2020)
 *
 * @section intro_sec	Chosen project theme: Cartão Museus de Portugal
 *
 * @subsection step1	Our UML diagram was drawn using https://www.draw.io
 *
 * @image html	UML_class_diagram.svg
 */

/** @addtogroup	museum_grp
 * @{
 */

/** @brief Hash functions for the StateWorker objects */
struct stateWorkerHash
{
  int operator()(const StateWorker& sw) const { return sw.get_cc(); }

  bool operator()(const StateWorker& lhs, const StateWorker& rhs) const
  {
    return (lhs == rhs);
  }
};

/** @brief StateWorker object hast table type */
typedef std::unordered_set<StateWorker, stateWorkerHash, stateWorkerHash>
  HashTabStateWorker;

/** @brief	Network that handles the Museums and the relationship with Event
 * companies */
class MuseumNetwork
{
private:
  /** @brief	List of the different discounts applied to Cards
   *  @note	Defaults to 25% off for every type of Card
   */
  float discount[3] = { 0.25, 0.25, 0.25 };
  /** @brief	List of the different Card's creation/renewal cost
   *  @note	Defaults to:\n
   *		54.90 for IndividualCard,\n
   *		32.45 for UniCard and\n
   *		30.00 for SilverCard
   */
  float cost[3] = { 54.90, 32.45, 30.00 };
  /** @brief	List of pointers to all the registered User's Cards */
  std::vector<Card*> cards;
  /** @brief	List of all the Enterprises associated with the MuseumNetwork */
  std::vector<Enterprise> enterprises;
  /** @brief	Set (BST) of all the Museums that are part of the Museum Network
   */
  /** @brief  BST containing the most visited museums */
  std::set<Museum> museums;
  /** @brief  Hash table containing all the state workers registers */
  HashTabStateWorker workers; // TODO
  /** @brief Pritority Queue containing all the repair enterprises, having the
   * one with the most repairs always at the top */
  std::priority_queue<RepairEnterprise> repair_ent; // TODO

  /**
   * @brief Searches for a Museum with the given museum_name and museum_coords
   * in the network
   *
   * @param museum_name	Name of the museum to search
   * @param museum_coords	Coordinates of the museum to search
   *
   * @return	True if the museum is found, false otherwise
   */
  bool findMuseum(std::string museum_name,
                  std::tuple<float, float> museum_coords);

public:
  /* CONSTRUCTORS */
  /**
   * @brief	Default constructor
   * @note	Has default values for each Card type cost and discount
   */
  MuseumNetwork() = default;
  /**
   * @brief	Constructor for the MuseumNetwork class
   *
   * @param card_vector		Vector of pointers to registered user Cards to
   * add to the Network
   * @param enterprise_vector	Vector of enterprises to add to the Network
   * @param museum_vector		Vector of museums to add to the Network
   */
  MuseumNetwork(std::vector<Card*>& card_vector,
                std::vector<Enterprise>& enterprise_vector,
                std::set<Museum>& museum_vector)
    : cards(card_vector)
    , enterprises(enterprise_vector)
    , museums(museum_vector)
  {}
  /**
   * @brief	Constructor for the MuseumNetwork class
   *
   * @param config_file_name	Name of the file to read the new Museum Network
   configuration from\n Including the names of the files that containing the new
   information
   */
  MuseumNetwork(std::string config_file_name)
  {
    this->importFiles(config_file_name);
  }

  ~MuseumNetwork() { this->removeCards(this->cards); }

  /* METHODS FOR CARDS */
  /**
   * @brief	Add a new user Card to the network
   *
   * @param card	Pointer (to a new user Card) to be added to the network
   */
  void addCard(Card* card);
  /**
   * @brief	Search for the given Card on the network and remove it
   * @throws  ObjectAlreadyExists  Thrown if card is already in the network
   *
   * @param card	Pointer to the Card to find and remove from the network
   */
  void removeCard(const Card* card);
  /**
   * @brief	Search for the given Cards on the network and remove them
   *
   * @param cards_to_be_removed	Vector of pointers to the Cards to be removed
   * from the network
   */
  void removeCards(const std::vector<Card*>& cards_to_be_removed);
  /**
   * @brief	List all Cards resgistered in the network
   *
   * @param delim   String delimiter to be printed between cards.
   */
  void listCards(const std::string& delim = '\n' + std::string(64, '-') +
                                            '\n') const;
  /**
   * @brief	Lists all Cards present in the given vector
   *
   * @param delim   String delimiter to be printed between cards.
   * @param cards_to_be_listed   Vector of pointers to the Cards to be listed
   */
  void listCards(const std::vector<Card*>& cards_to_be_listed,
                 const std::string& delim = '\n' + std::string(64, '-') +
                                            '\n') const;

  /**
   * @brief   Getter for discount
   *
   * @param card_type   ID Specifier of the Card type
   *
   * @return   Discount associated with the given Card type
   */
  float getDiscount(const unsigned card_type) const;
  /**
   * @brief   Getter for cost
   *
   * @param card_type   ID Specifier of the Card type
   *
   * @return   Cost associated with the given Card type
   */
  float getCost(const unsigned card_type) const;
  /**
   * @brief	Imports cards written in a file to the Cards controlled by the
   * network
   *
   * @param cards_file_name	Name of the file associated with the Cards'
   * information
   */
  void importCards(const std::string& cards_file_name);
  /**
   * @brief	Exports all Cards registered in the network to a file
   *
   * @param cards_file_name	Name of the file that will be overwritten with
   * the cards' information
   */
  void exportCards(const std::string& cards_file_name) const;

  /* METHODS FOR ENTERPRISES */
  /**
   * @brief	Add a new Enterprise to the network
   * @throws  ObjectAlreadyExists  Thrown if the Enterprise is already in the
   * network
   * @param enterprise	Enterprise to be added to the network
   */
  void addEnterprise(Enterprise enterprise);

  /**
   * @brief	Search for the given Enterprise on the network and remove it
   *
   * @throws  NoSuchObject	Thrown if enterprise_to_be_removed doesn't exist
   * in the network
   * @param enterprise_to_be_removed	Enterprise to find and remove from the
   * network
   */
  void removeEnterprise(const Enterprise& enterprise_to_be_removed);
  /**
   * @brief	Search for the given Enterprises on the network and remove them
   *
   * @param enterprises_to_be_removed	Vector of Enterprises to be removed from
   * the network
   */
  void removeEnterprises(std::vector<Enterprise>& enterprises_to_be_removed);

  /**
   * @brief	Search for a given Enterprise and change its content to a new
   * given Enterprise (new_enterprise)
   *
   * @throws  NoSuchObject	Thrown if the old_enterprise doesn't exist in
   * the network
   * @throws  ObjectAlreadyExists	Thrown if the new_enterprise would
   * overwritte one of the already resgistred enterprises
   * @param old_enterprise	Enterprise that will be changed
   * @param new_enterprise	Enterprise whose content will replace the old
   * one
   */
  void modifyEnterprise(const Enterprise& old_enterprise,
                        const Enterprise& new_enterprise);

  /**
   * @brief	Lists all Enterprises present in the network
   *
   * @param delim   String delimiter to be printed between enterprises
   */
  void listEnterprises(const std::string& delim = '\n' + std::string(64, '-') +
                                                  '\n') const;
  /**
   * @brief	Lists all Enterprises in the given vector
   *
   * @param delim   String delimiter to be printed between enterprises
   * @param enterprises_to_be_listed   Vector of Enterprises to be listed
   */
  void listEnterprises(const std::vector<Enterprise>& enterprises_to_be_listed,
                       const std::string& delim = '\n' + std::string(64, '-') +
                                                  '\n') const;

  /**
   * @brief	Imports enterprises written in a file to the enteprises
   * controlled by the network
   *
   * @param enterprise_file_name	Name of the file associated with the
   * enterprises' information
   */
  void importEnterprises(const std::string& enterprise_file_name);
  /**
   * @brief	Exports all enteprises registered in the network to a file
   *
   * @param enterprise_file_name	Name of the file that will be
   * overwritten with the enterprises' information
   */
  void exportEnterprises(const std::string& enterprise_file_name) const;

  /* METHODS FOR MUSEUMS */
  /**
   * @brief	Add a new Museum to the network
   * @throws  ObjectAlreadyExists  Thrown if the Museum is already in the
   * network
   * @param museum	Museum to be added to the network
   */
  void addMuseum(Museum museum);

  /**
   * @brief Searches for each museum in a given set in the network and deletes
   * them
   *
   * @param museums_to_delete	Set of museums to find and delete from the
   * network
   */
  void removeMuseums(const std::set<Museum>& museums_to_delete);
  /**
   * @brief	Search for the given Museum on the network and remove it.
   * All workers present in the network that work in the museum_to_be_removed
   * will be fired
   *
   * @throws  NoSuchObject  Thrown if museum_to_be_removed doesn't exist in the
   * network
   * @param museum_to_be_removed	Museum to find and remove from the
   * network
   */
  void removeMuseum(const Museum& museum_to_be_removed);

  /**
   * @brief	Search for a given Museum and change its content to a new given
   * Museum (new_museum)
   *
   * @throws  NoSuchObject  Thrown if the old_museum doesn't exist in the
   * network
   * @throws  ObjectAlreadyExists	Thrown if the new_museum would
   * overwritte one of the already resgistred museums
   * @param old_museum	Museum that will be changed
   * @param new_museum	Museum whose content will replace the old one
   */
  void modifyMuseum(const Museum& old_museum, const Museum& new_museum);

  /**
   * @brief	Lists all Museums present in the network
   *
   * @param delim   String delimiter to be printed between museums
   */
  void listMuseums(const std::string& delim = '\n' + std::string(64, '-') +
                                              '\n') const;
  /**
   * @brief	Lists all Museums in the given vector
   *
   * @param delim   String delimiter to be printed between museums
   * @param museum_to_be_listed	Vector of Museums to be listed
   */
  void listMuseums(const std::set<Museum>& museum_to_be_listed,
                   const std::string& delim = '\n' + std::string(64, '-') +
                                              '\n') const;

  /**
   * @brief	Imports museums written in a file to the museums controlled by
   * the network
   *
   * @param museum_file_name	Name of the file associated with the museums'
   * information
   */
  void importMuseums(const std::string& museum_file_name);
  /**
   * @brief	Exports all museums registered in the network to a file
   *
   * @param museum_file_name	Name of the file that will be overwritten with
   * the museums' information
   */
  void exportMuseums(const std::string& museum_file_name) const;

  /* METHODS FOR EVENTS */

  /**
   * @brief	Lists all Events present in the network with a discount
   * associated with a given card type
   *
   * @param card_type	  ID specifier of the card type
   * @param delim   String delimiter to be printed between Events
   */
  void listEvents(unsigned card_type,
                  const std::string& delim = '\n' + std::string(64, '-') +
                                             '\n') const;
  /**
   * @brief	Lists all Events present in a given vector with a discount
   * associated with a given card type
   *
   * @param events_to_be_listed	  Vector of Events that will be listed
   * @param card_type	  ID specifier of the card type
   * @param delim   String delimiter to be printed between Events
   */
  void listEvents(const std::vector<Event>& events_to_be_listed,
                  unsigned card_type,
                  const std::string& delim = '\n' + std::string(64, '-') +
                                             '\n') const;

  /**
   * @brief	Lists all Events present in the network with no discount
   *
   * @param delim   String delimiter to be printed between Events
   */
  void listEvents(const std::string& delim = '\n' + std::string(64, '-') +
                                             '\n') const;
  /**
   * @brief	Lists all Events present in a given vector with no discount
   *
   * @param events_to_be_listed	  Vector of Events that will be listed
   * @param delim   String delimiter to be printed between Events
   */
  void listEvents(const std::vector<Event>& events_to_be_listed,
                  const std::string& delim = '\n' + std::string(64, '-') +
                                             '\n') const;

  /**
   * @brief	Search for a given enterprise and add a given event to that
   * enterprise
   *
   * @param event		Event to be added
   * @param enterprise	Enterprise in which the Event will be added
   */
  void addEvent(const Enterprise& enterprise, Event& event);

  /**
   * @brief	Search for a given enterprise. Search for a given event in that
   * enterprise. Remove that event in the enterprise.
   *
   * @param event_to_be_removed	Event to be removed
   * @param enterprise	Enterprise which holds the to be removed event
   */
  void removeEvent(const Event& event_to_be_removed, Enterprise& enterprise);
  /**
   * @brief	Remove all events in a given vector from the network.
   *
   * @param events_to_be_removed	Vector of events to be removed
   */
  void removeEvents(std::vector<Event>& events_to_be_removed);

  /**
   * @brief	Search for a given Event and change its content to a new given
   * Event (new_evenevent)
   *
   * @throws  NoSuchObject	Thrown if old_event doesn't exist in the network
   * @param old_event		Event that will be changed
   * @param new_event	Event whose content will replace the old one
   */
  void modifyEvent(const Event& old_event, const Event& new_event);

  /**
   * @brief	Search for the Card which holds a given cc. Effectuates a
   * purchase by that Card of a given event
   *
   * @param cc	Cc of the card that will effectuate the purchase
   * @param event		Event to be purchased
   */
  void purchaseEvent(const unsigned cc, Event event);

  /* METHODS FOR WORKERS */

  /**
   * @brief	Add a new StateWorker to the network.
   * @throws  ObjectAlreadyExists  Thrown if the StateWorker is already in the
   * network
   * @param worker	Worker to be added to the network
   */
  void addWorker(StateWorker worker);

  /**
   * @brief Searches for a given worker in the network and hires it to a given
   * museum
   *
   * @param worker	Worker to hire
   * @param mus		Museum that the worker will work in
   */
  void hireWorker(StateWorker worker, const Museum& mus);

  /**
   * @brief	Lists all Workers present in the network
   *
   * @param delim   String delimiter to be printed between Workers
   */
  void listWorkers(const std::string& delim = '\n' + std::string(64, '-') +
                                              '\n') const;

  /**
   * @brief	Lists all Workers present in a given vector
   *
   * @param vec	  Vector of StateWorker that will be listed
   * @param delim   String delimiter to be printed between Workers
   */
  void listWorkers(const std::vector<StateWorker>& vec,
                   const std::string& delim = '\n' + std::string(64, '-') +
                                              '\n') const;

  /**
   * @brief	Remove a given StateWorker from the network
   *
   * @throws  NoSuchObject  Thrown if workeworkere_removed doesn't exist in the
   * network
   * @param worker_to_be_removed	Worker to find and remove from the
   * network
   */
  void removeWorker(const StateWorker& worker_to_be_removed);

  /**
   * @brief	Search for the given Workers on the network and remove them
   *
   * @param workers_to_be_removed	Vector of StateWorker to be removed from
   * the network
   */
  void removeWorkers(const std::vector<StateWorker>& workers_to_be_removed);

  /**
   * @brief	Search for a given StateWorker and change its content to a new
   given
   * Worker (new_worker)
   *
   * @throws  NoSuchObject  Thrown if the old_worker doesn't exist in the
   * network or the new_worker is being employed in a museum that isn't in the
   networ
   k
   * @throws  ObjectAlreadyExists	Thrown if the new_worker would
   * overwritte one of the already resgistred workers
   * @param old_worker	Worker that will be changed
   * @param new_worker	Worker whose content will replace the old one
   */
  void modifyWorker(const StateWorker& old_worker,
                    const StateWorker& new_worker);

  /**
   * @brief	Imports Workers written in a file to the workers
   * controlled by the network
   *
   * @param worker_file_name	Name of the file associated with the
   * StateWorker(s)' information
   */
  void importWorkers(const std::string& worker_file_name);

  /**
   * @brief	Exports all workers registered in the network to a file
   *
   * @param worker_file_name	Name of the file that will be
   * overwritten with the StateWorker(s)' information
   */
  void exportWorkers(const std::string& worker_file_name) const;

  /* METHODS FOR REPAIR ENTEPRISES */
  /**
   * @brief		Add a new RepairEnterprise to the network
   * @throws	ObjectAlreadyExists  Thrown if the RepairEnterprise is already
   * in the network
   * @param repair_enterprise	RepairEnterprise to be added to the network
   */
  void addRepairEnterprise(RepairEnterprise repair_enterprise);
  /**
   * @brief	Lists all RepairEnterprises present in the network
   *
   * @param delim   String delimiter to be printed between RepairEnterprises
   */
  void listRepairEnterprises(const std::string& delim = '\n' +
                                                        std::string(64, '-') +
                                                        '\n') const;
  /**
   * @brief	Lists all RepairEnterprises present in a given vector
   *
   * @param vec	  Vector of RepairEnterprises that will be listed
   * @param delim   String delimiter to be printed between RepEnterprises
   */
  void listRepairEnterprises(const std::vector<RepairEnterprise>& vec,
                             const std::string& delim = '\n' +
                                                        std::string(64, '-') +
                                                        '\n') const;
  /**
   * @brief	Remove a given RepairEnterprise from the network
   *
   * @throws  NoSuchObject  Thrown if the given RepairEnterprise doesn't exist
   * in the network
   * @param repair_enterprise	RepairEnterprise to find and remove from the
   * network
   */
  void removeRepairEnterprise(const RepairEnterprise& repair_enterprise);
  /**
   * @brief	Search for the given RepairEnterprises on the network and remove
   * them
   *
   * @param repair_enterprises	Vector of RepairEnterprises to be removed from
   * the network
   */
  void removeRepairEnterprises(
    const std::vector<RepairEnterprise>& repair_enterprises);
  /**
   * @brief	Search for a given RepairEnterprise and change its content to a
   * new given RepairEnterprise (old_rep_enter)
   *
   * @throws  NoSuchObject  Thrown if the old_rep_enter doesn't exist in the
   * network
   * @throws  ObjectAlreadyExists	Thrown if the new_rep_enter would
   * overwritte one of the already resgistred RepairEnterprises
   * @param old_rep_enter	RepairEnterprise that will be changed
   * @param new_rep_enter	RepairEnterprise whose content will replace the
   * old one
   */
  void modifyRepairEnterprise(const RepairEnterprise& old_rep_enter,
                              const RepairEnterprise& new_rep_enter);
  /**
   * @brief	Contacts a given RepairEnterprise to do a maintenance service,
   * increasing its number of jobs
   *
   * @param rep_enter	RepairEnterprise to contact
   */
  void contactRepairEnterprise(const RepairEnterprise& rep_enter);
  /**
   * @brief	Imports repair enterprises written in a file to the repair
   * enterprises controlled by the network
   *
   * @param repair_enterprise_file_name	Name of the file associated with the
   * repair enterprises' information
   */
  void importRepairEnterprises(const std::string& repair_enterprise_file_name);
  /**
   * @brief	Exports all repair enterprises registered in the network to a
   * file
   *
   * @param repair_enterprise_file_name	Name of the file that will be
   * overwritten with the repair enterprises' information
   */
  void exportRepairEnterprises(
    const std::string& repair_enterprise_file_name) const;

  /* GETTERS */

  /**
   * @brief	Getter for all Cards subscribed in the network
   *
   * @return	Vector of pointers to all Cards subscribed in the network
   */
  std::vector<Card*> getCards() const { return this->cards; };
  RepairEnterprise getBestRepairEnterprise(std::tuple<float, float> mcoord,
                                           float dist);
  /**
   * @brief	Getter for all Enterprises present in the network
   *
   * @return	Vector of all Enterprises present in the network
   */
  std::vector<Enterprise> getEnterprises() const { return this->enterprises; };
  /**
   * @brief	Getter for all RepairEnterprises present in the network
   *
   * @return	Vector of all RepairEnterprises present in the network
   */
  std::priority_queue<RepairEnterprise> getRepairEnterprises() const;
  /**
   * @brief	Getter for all RepairEnterprises present in the network (in a
   * vector)
   *
   * @return	Vector of all RepairEnterprises present in the network (in a
   * vector)
   */
  std::vector<RepairEnterprise> getRepairEnterprisesvec() const;
  /**
   * @brief	Getter for all Museums present in the network
   *
   * @return	Vector of all Museums present in the network
   */
  std::set<Museum> getMuseums() const;
  /**
   * @brief	Getter for all Events present in the network
   *
   * @return	Vector of all Events present in the network
   */
  std::vector<Event> getEvents()
    const; // Iterates through all enterprises to retreive all events

  /**
   * @brief	Getter for all Workers present in the network
   *
   * @return Vector of all Workers present in the network
   */
  std::vector<StateWorker> getWorkers() const;

  /**
   * @brief	Imports network configuarions for a given file name.
   *			Imports all other files related to museums, cards and
   *enterprises.
   *
   * @param network_file_name	Name of the file associated with the network
   *configuarion
   */
  void importFiles(const std::string& network_file_name);
  /**
   * @brief Exports current network information to 4 files (cards, museum,
   * enterprise and config) whose names are given
   *
   * @param cards_file_name	            Name of the cards file to export to
   * @param museum_file_name	          Name of the museum file to export to
   * @param enterprise_file_name	      Name of the enterprise file to export
   * to
   * @param repair_enterprise_file_name Name of the museum file to export to
   * @param worker_file_name	          Name of the enterprise file to export
   * to
   * @param config_file_name	          Name of the config file to export to
   */
  void exportFiles(
    const std::string& cards_file_name,
    const std::string& museum_file_name,
    const std::string& enterprise_file_name,
    const std::string& repair_enterprise_file_name,
    const std::string& worker_file_name,
    const std::string& config_file_name = "files/network_config.sadjson") const;
};

/** @} */

#endif // MUSEUM_NETWORK_H
