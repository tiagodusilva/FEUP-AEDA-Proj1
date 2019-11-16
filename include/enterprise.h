/** @file enterprise.h */
#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include "../include/address.h"
#include "../include/event.h"
#include "set"
#include <string>

/** @defgroup event_grp Enterprise and Event module */

/** @addtogroup	event_grp
  *
  * @brief	Code related to the handling and saving of enterprises and their events
  *
  * @{
  */

/** @brief	number of characters to use with std::setw() on Enterprise object information output */
#define ENTERPRISE_OUPUT_DELIM 15

/**
 * @brief    Class that simulates the Enterprises our Network would have established contracts with
 */
class Enterprise {
private:
	/** @brief	enterprise's name */
	std::string name;
	/** @brief	enterprise's contact (phone number or email, etc...) */
	std::string contact;
	/** @brief	enterprise's main address */
	Address address;
	/** @brief	enterprise's currently registered events */
	std::set<Event> events;

public:
	/* CONSTRUCTORS */
	/**
	* @brief    Default constructor
	*/
	Enterprise() = default;
	/**
	* @brief                Complete Enterprise constructor
	*
	* @param name           The name of the Enterprise
	* @param contact        The contact of the Enterprise
	* @param address        The address of the Enterprise
	* @param events         The set of all Events managed by this Enterprise\n
	*                       Defaults to an empty set
	*/
	Enterprise(const std::string &name, const std::string &contact, const Address &address, const std::set<Event> &events = std::set<Event>());
	/**
	* @brief    Default destructor
	*/
	~Enterprise() = default;

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
	/**
	* @brief     Getter for the Events
	* @return    The set of Events this Enterprise manages\name
	*            Const reference to ensures this is read only data
	*/
	const std::set<Event>& get_events() const;
	/**
	* @brief     Getter for a specific Event
	*
	* @param id  The id of the Event to return
	*
	* @return    The Event with the specified id (if found)\n
	*            Const reference to ensure this is read only data
	*            If the Enterprise does not have this Event, it will throw a EventNotFound exception
	*/
	const Event& get_event(unsigned id) const;

	/* OTHER PUBLIC METHODS */
	/**
	* @brief          Adds an Event to the Enterprise
	*
	* @param ev        Event to add to the Enterprise\n
	*                  If the Event is added successfully, the Event's id will permanently be set to 0, to guarantee the uniqueness of every Event
	*
	* @throws   EventAlreadyExists Thrown if the Event already exists in the Enterprise\n
	*                              That said, if it does get thrown, something really odd is going on
	*/
	void add_event(Event &ev);
	/**
	* @brief          Removes an Event from the Enterprise or works as garbage collector (id=0)
	*
	* @details        If successful, the event will be removed from memory\n
	*                 If id is set to 0, it will remove the event with id 0 (aka completely invalid),
	*                 also known as garbage collection, because there can only one event with id 0 at
	*                 a time inside an enterprise
	*
	* @param id       Id of the event to remove, if id is 0, it will work as a garbage collector (read description)
	*
	* @throws    EventNotFound   Only throws this exception when not in garbage collection mode (id != 0), if
	*                            this Enterprise does not have an Event with the specified id
	*/
	void remove_event(unsigned id);
	/**
	* @brief     Checks for the existence of a specific Event
	*
	* @param id  The id of the Event to find
	*
	* @return    True if the Enterprise has an Event with the specifiec id\n
	*            False otherwise
	*/
	bool has_event(unsigned id) const;
	/**
	* @brief     Checks for the existence of a specific Event
	*
	* @param id  The id of the Event to be purchased
	* @param cc  The cc of the user trying to purchase this Event
	*
	* @throws    Any exception thrown by Event::purchase()
	* @throws    EventNotFound if the Enterprise does not have the Event specifiec in the id
	*/
	void purchase_event(unsigned id, unsigned cc);

	/* OVERLOADED COMPARISON OPERATORS */
	/**
	* @brief     Overloaded equality test operator
	*
	* @details   As all of our enterprises must be registered in our country, their names will ALWAYS be
	*            different by law, therefore we only need to compare their names
	*
	* @param	ent	The rightmost Enterprise to compare
	*
	* @return	True if both Enterprises' names are equal\n
	*		False, otherwise
	*/
	inline bool operator== (const Enterprise &ent) { return this->name == ent.name; };
	/**
	* @brief     Overloaded inequality test operator
	*
	* @details   As all of our enterprises must be registered in our country, their names will ALWAYS be
	*            different by law, therefore we only need to compare their names
	*
	* @param	ent	The rightmost Enterprise to compare
	*
	* @return    True if both Enterprises' names are different\n
	*            False, otherwise
	*/
	inline bool operator!= (const Enterprise &ent) { return !this->operator==(ent); };

	/* OVERLOADED INSERTION OPERATOR */
	/**
	* @brief              Overloaded ostream insertion operator
	*
	* @details            Mainly used with std::cout to show formated information on screen
	*
	* @param outstream    Reference to the ostream object to insert info to
	* @param ent          Reference to the Enterprise object whose info will be inserted in the ostream
	*
	* @return             Reference to the ostream object, 'outstream', passed in the parameters
	*/
	friend std::ostream& operator<<(std::ostream &outstream, const Enterprise &ent);
	/**
	* @brief               Overloaded ofstream insertion operator
	*
	* @details             Used to save information on a file so it can be read again at a later date
	*
	* @param outfstream    Reference to the ofstream object to insert info to
	* @param ent           Reference to Enterprise object whose info will be inserted in the ofstream
	*
	* @return              Reference to the ofstream object, 'outfstream', passed in the parameters
	*/
	friend std::ofstream& operator<<(std::ofstream &outfstream, const Enterprise &ent);
	/* OVERLOAD EXTRACTION OPERATOR */
	/**
	* @brief              Overloaded ifstream extraction operator
	*
	* @details            Used to read information that has been saved to a file previously
	*
	* @param infstream    Reference to the ifstream object to extract info from
	* @param ent          Reference to Enterprise object where the read information is saved
	*
	* @return             Reference to the ifstream object, 'infstream', passed in the parameters
	*/
	friend std::ifstream &operator>>(std::ifstream &infstream, Enterprise &ent);

	/* READ ENTERPRISE FROM STD::CIN */
	/**
	* @brief	Read an Enterprise from cin, outputting any user prompts to cout
	*
	* @param	ent	Enterprise to read from cin\n
	*/
	static void cin_read_enterprise(Enterprise &ent);

};

/** @} */

#endif // ENTERPRISE_H
