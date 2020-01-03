/** @file enterprise.h */
#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include <set>
#include <string>

#include "../include/address.h"
#include "../include/event.h"

/** @defgroup event_grp Event module */

/** @brief	number of characters to use with std::setw() on Enterprise
 * object information output */
#define ENTERPRISE_OUPUT_DELIM 15

/** @addtogroup	museum_grp
 * @{
 */

/** @brief  Base enterprise object */
class BaseEnterprise
{
protected:
  /** @brief	enterprise's name */
  std::string name;
  /** @brief	enterprise's contact (phone number or email, etc...) */
  std::string contact;
  /** @brief	enterprise's main address */
  Address address;

public:
  /* CONSTRUCTORS */
  /** @brief	default constructor for the BaseEnterprise class */
  BaseEnterprise() = default;
  /**
   * @brief Complete Enterprise constructor
   *
   * @param name		  The name of the Enterprise
   * @param contact	  The contact of the Enterprise
   * @param address	  The address of the Enterprise
   */
  BaseEnterprise(const std::string& name,
                 const std::string& contact,
                 const Address& address);
  /** @brief    Default destructor */
  ~BaseEnterprise() = default;

  /* GETTERS */
  /**
   * @brief     Getter for the name
   * @return    The name of this Enterprise
   */
  std::string get_name() const;
  /**
   * @brief     Getter for the contact
   * @return    The contact of this Enterprise
   */
  std::string get_contact() const;
  /**
   * @brief     Getter for the address
   * @return    The address of this Enterprise
   */
  Address get_address() const;

  /* SETTERS */
  /**
   * @brief     Setter for the name
   * @param  new_name The new name for this Enterprise
   */
  void set_name(const std::string& new_name);
  /**
   * @brief     Setter for the contact
   * @param   new_contact  The new contact for this Enterprise
   */
  void set_contact(const std::string& new_contact);
  /**
   * @brief     Setter for the address
   * @param  new_address	The new address for this Enterprise
   */
  void set_address(const Address& new_address);

  /* OVERLOADED COMPARISON OPERATORS */
  /**
   * @brief     Overloaded equality test operator
   *
   * @details   As all of our enterprises must be registered in our country,
   *their names will ALWAYS be different by law, therefore we only need to
   *compare their names
   *
   * @param	ent	The rightmost Enterprise to compare
   *
   * @return	True if both Enterprises' names are equal\n
   *		False, otherwise
   */
  inline bool operator==(const BaseEnterprise& ent) const
  {
    return this->name == ent.name;
  };
  /**
   * @brief     Overloaded inequality test operator
   *
   * @details   As all of our enterprises must be registered in our country,
   *their names will ALWAYS be different by law, therefore we only need to
   *compare their names
   *
   * @param	ent	The rightmost Enterprise to compare
   *
   * @return    True if both Enterprises' names are different\n
   *	      False, otherwise
   */
  inline bool operator!=(const BaseEnterprise& ent) const
  {
    return !this->operator==(ent);
  };

  /* OVERLOADED INSERTION OPERATOR */
  /**
   * @brief	       Overloaded ostream insertion operator
   *
   * @details	       Mainly used with std::cout to show formated information
   * on screen
   *
   * @param outstream    Reference to the ostream object to insert info to
   * @param ent	       Reference to the Enterprise object whose info will be
   * inserted in the ostream
   *
   * @return	       Reference to the ostream object, 'outstream', passed in
   * the parameters
   */
  friend std::ostream& operator<<(std::ostream& outstream,
                                  const BaseEnterprise& ent);
  /**
   * @brief		Overloaded ofstream insertion operator
   *
   * @details		Used to save information on a file so it can be read
   * again at a later date
   *
   * @param outfstream	Reference to the ofstream object to insert info to
   * @param ent		Reference to Enterprise object whose info will be
   * inserted in the ofstream
   *
   * @return		Reference to the ofstream object, 'outfstream', passed
   * in the parameters
   */
  friend std::ofstream& operator<<(std::ofstream& outfstream,
                                   const BaseEnterprise& ent);

  /* OVERLOAD EXTRACTION OPERATOR */
  /**
   * @brief	       Overloaded ifstream extraction operator
   *
   * @details	       Used to read information that has been saved to a file
   * previously
   *
   * @param infstream    Reference to the ifstream object to extract info from
   * @param ent	       Reference to Enterprise object where the read information
   * is saved
   *
   * @return	       Reference to the ifstream object, 'infstream', passed in
   * the parameters
   */
  friend std::ifstream& operator>>(std::ifstream& infstream,
                                   BaseEnterprise& ent);
};

/** @} */

/** @addtogroup	event_grp
 *
 * @brief	Code related to the handling and saving of events and their
 * enterprises
 *
 * @{
 */

/**@brief Class that simulates the Event Enterprises our Network would have
 *        established contracts with */
class Enterprise : public BaseEnterprise
{
private:
  /** @brief	enterprise's currently registered events */
  std::set<Event> events;
  /**
   * @brief     Searches for Event with id, removes it from the set and returns
   *            it
   * @param id  The id of the Event to remove from the set
   * @throws    NoSuchObject  Thrown if the Event with the specified id was not
   *            found
   * @return    Event with id, removed from the set
   */
  Event pop(unsigned id);

public:
  /* CONSTRUCTORS */
  /**
   * @brief    Default constructor
   */
  Enterprise() = default;
  /**
   * @brief Complete Enterprise constructor
   *
   * @param name		  The name of the Enterprise
   * @param contact	  The contact of the Enterprise
   * @param address	  The address of the Enterprise
   * @param events	  The set of all Events managed by this Enterprise\n
   *			            Defaults to an empty set
   */
  Enterprise(const std::string& name,
             const std::string& contact,
             const Address& address,
             const std::set<Event>& events = std::set<Event>());
  /**
   * @brief    Default destructor
   */
  ~Enterprise() = default;

  /* GETTERS */
  /**
   * @brief     Getter for the Events
   * @return    The set of Events this Enterprise manages\n
   *	      Const reference to ensures this is read only data
   */
  const std::set<Event>& get_events() const;
  /**
   * @brief     Getter for a specific Event
   *
   * @param id  The id of the Event to return
   *
   * @return    The Event with the specified id (if found)\n
   *	      Const reference to ensure this is read only data\n
   *	      If the Enterprise does not have this Event, it will throw a
   *EventNotFound exception
   */
  const Event& get_event(unsigned id) const;

  /* EVENT SETTERS */
  /**
   * @brief Setter for the maximum capacity of the Event with id
   *
   * @param id	Id of the Event to change
   * @param new_max_capacity The new max capacity for the Event with id
   *
   * @throws  NoSuchObject  Thrown if the Event with the specified id was not
   * found
   */
  void event_set_max_capacity(unsigned id, unsigned new_max_capacity);
  /**
   * @brief	Setter for the name of the Event with id
   *
   * @param id	Id of the Event to change
   * @param new_name	The new name for the Event with id
   *
   * @throws NoSuchObject	Thrown if the Event with the specified ID was
   * not found
   */
  void event_set_name(unsigned id, const std::string& new_name);
  /**
   * @brief Setter for the ticket fee of the Event with id
   *
   * @param id	Id of the Event to change
   *
   * @throws NoSuchObject Thrown if the Event with the specified ID was not
   * found
   *
   * @param new_ticket_fee The new ticket fee for the Event with id
   */
  void event_set_ticket_fee(unsigned id, float new_ticket_fee);
  /**
   * @brief Setter for the location name of the Event with id
   *
   * @param id	Id of the Event to change
   *
   * @throws NoSuchObject Thrown if the Event with the specified ID was not
   * found
   *
   * @param new_location_name The new location name for the Event with id
   */
  void event_set_location_name(unsigned id,
                               const std::string& new_location_name);
  /**
   * @brief Setter for the address of the Event with id
   *
   * @param id	Id of the Event to change
   *
   * @throws NoSuchObject Thrown if the Event with the specified ID was not
   * found
   *
   * @param new_address The new address for the Event with id
   */
  void event_set_address(unsigned id, const Address& new_address);
  /**
   * @brief Setter for the time of the Event with id
   *
   * @param id	Id of the Event to change
   *
   * @throws NoSuchObject Thrown if the Event with the specified ID was not
   * found
   *
   * @param new_time The new time for the Event with id
   */
  void event_set_time(unsigned id, const Time& new_time);
  /**
   * @brief Seter for the date of the Event with id
   *
   * @param id	Id of the Event to change
   *
   * @throws NoSuchObject Thrown if the Event with the specified ID was not
   * found
   *
   * @param new_date The new date for the Event with id
   */
  void event_set_date(unsigned id, const Date& new_date);
  /**
   * @brief	Setter for the is_valid flag of the Event with id
   * @details	This method is not destructive (can be reverted)
   *
   * @param id		Id of the Event to change
   * @param new_is_valid	The new is_valid flag for the Event with id
   */
  void event_set_validity(unsigned id, bool new_is_valid);

  /* OTHER PUBLIC METHODS */
  /**
   * @brief	   Adds an Event to the Enterprise
   *
   * @param ev	    Event to add to the Enterprise\n
   *		    If the Event is added successfully, the Event's id will
   *permanently be set to 0, to guarantee the uniqueness of every Event
   *
   * @throws InvalidObject	If the event id is 0
   * @throws ObjectAlreadyExists	Thrown if the Event already exists in
   *the Enterprise\n That said, if it does get thrown, something really odd is
   *going on
   */
  void add_event(Event& ev);
  /**
   * @brief	   Removes an Event from the Enterprise or works as garbage
   *collector (id=0)
   *
   * @details	   If successful, the event will be removed from memory\n
   *		   If id is set to 0, it will remove the event with id 0 (aka
   *completely invalid), also known as garbage collection, because there can
   *only one event with id 0 at a time inside an enterprise
   *
   * @param id	   Id of the event to remove, if id is 0, it will work as a
   *garbage collector (read description)
   *
   * @throws    NoSuchObject	Only throws this exception when not in garbage
   *collection mode (id != 0), if this Enterprise does not have an Event with
   *the specified id
   */
  void remove_event(unsigned id);
  /**
   * @brief     Checks for the existence of a specific Event
   *
   * @param id  The id of the Event to find
   *
   * @return    True if the Enterprise has an Event with the specifiec id\n
   *	      False otherwise
   */
  bool has_event(unsigned id) const;
  /**
   * @brief     Checks for the existence of a specific Event
   *
   * @param id  The id of the Event to be purchased
   * @param cc  The cc of the user trying to purchase this Event
   *
   * @throws    Any exception thrown by Event::purchase()
   * @throws    EventNotFound if the Enterprise does not have the Event
   * specifiec in the id
   */
  void purchase_event(unsigned id, unsigned cc);

  /* OVERLOADED INSERTION OPERATOR */
  /**
   * @brief	       Overloaded ostream insertion operator
   *
   * @details	       Mainly used with std::cout to show formated information
   * on screen
   *
   * @param outstream    Reference to the ostream object to insert info to
   * @param ent	       Reference to the Enterprise object whose info will be
   * inserted in the ostream
   *
   * @return	       Reference to the ostream object, 'outstream', passed in
   * the parameters
   */
  friend std::ostream& operator<<(std::ostream& outstream,
                                  const Enterprise& ent);
  /**
   * @brief		Overloaded ofstream insertion operator
   *
   * @details		Used to save information on a file so it can be read
   * again at a later date
   *
   * @param outfstream	Reference to the ofstream object to insert info to
   * @param ent		Reference to Enterprise object whose info will be
   * inserted in the ofstream
   *
   * @return		Reference to the ofstream object, 'outfstream', passed
   * in the parameters
   */
  friend std::ofstream& operator<<(std::ofstream& outfstream,
                                   const Enterprise& ent);
  /* OVERLOAD EXTRACTION OPERATOR */
  /**
   * @brief	       Overloaded ifstream extraction operator
   *
   * @details	       Used to read information that has been saved to a file
   * previously
   *
   * @param infstream    Reference to the ifstream object to extract info from
   * @param ent	       Reference to Enterprise object where the read information
   * is saved
   *
   * @return	       Reference to the ifstream object, 'infstream', passed in
   * the parameters
   */
  friend std::ifstream& operator>>(std::ifstream& infstream, Enterprise& ent);

  /* READ ENTERPRISE FROM STD::CIN */
  /**
   * @brief	Read an Enterprise from cin, outputting any user prompts to cout
   *
   * @param	ent	Enterprise to read from cin\n
   */
  static void cin_read_enterprise(Enterprise& ent);
};

/** @} */

#endif // ENTERPRISE_H
