/** @file event.h */
#ifndef EVENT_H
#define EVENT_H

#include "../include/time.h"
#include "../include/date.h"
#include "../include/address.h"
#include <string>
#include <set>
#include <iostream>


/** @addtogroup	event_grp
  *
  * @{
  */

/** @brief	number of characters to use with std::setw() on Event object information output */
#define EVENT_OUPUT_DELIM 15

/**
 * @brief    Class that simulates all the information an enterprise would have about their events
 */
class Event {
private:
	/** @brief	Event class unique id tracker (incremented for every event created/inserted) */
	static unsigned id_tracker;
	/** @brief	event's unique id (different for every event) */
	unsigned id;
	/** @brief	event's maximum people capacity */
	unsigned max_capacity;
	/** @brief	event's name */
	std::string name;
	/** @brief	event's ticket price */
	float ticket_fee;
	/** @brief	event's location name */
	std::string location_name;
	/** @brief	event's location */
	Address address;
	/** @brief	event's starting time */
	Time time;
	/** @brief	event's date */
	Date date;
	/** @brief	CC of the users who bought at least 1 ticket (may have CC's of unregistered people) */
	std::set<unsigned> reservations;
	/** @brief	True, if the event is valid. False, otherwise
	 * @details  Currently is used to make an Event visible, but impossible to be purchased
	 */
	bool is_valid;

public:
	/**
	* @brief	Default constructor
	*
	* @details	Does not attribute a valid id to the event (id = 0)
	*/
	Event() = default;

	/**
	* @brief	 Complete Event constructor, assigns a completely new and unique ID to the Event
	*
	* @param name	     The name of the Event
	* @param cost	     The cost of the Event
	* @param max_capacity	The maximum capacity of the Event, this is, the maximum number of elements of the reservations set)
	* @param location_name	 The name of where this Event takes place
	* @param address	     The address of the Event
	* @param time	     The time an Event starts
	* @param date	     The day of the Event
	* @param reservations	The set containing all the cc's of customers who have bought this Event (may not be members of the Network)\n
	*			     Defaults to an empty set
	* @param is_valid	     A flag indicating if an Event is valid or not (to be used for various purposes by an enterprise)
	*			     Defaults to true
	*/
	Event(const std::string& name, float cost, unsigned max_capacity, const std::string &location_name, const Address& address, const Time &time, const Date &date, const std::set<unsigned> &reservations=std::set<unsigned>(), bool is_valid=true);
	/**
	* @brief	 Default destructor
	*/
	~Event() = default;

	/**
	* @brief	  Getter for the id
	*
	* @return	  The id of this Event\n
	*		  Id 0 has the special meaning of having been instantiated through the default constructor
	*/
	unsigned get_id() const;

	/**
	* @brief	  Getter for the entry fee
	*
	* @return	  The entry fee of this Event
	*/
	float get_fee() const;

	/**
	* @brief	  Getter for the name
	*
	* @return	  The name of this Event
	*/
	std::string get_name() const;

	/**
	* @brief	  Getter for the maximum capacity
	*
	* @return	  The maximum capacity of this Event
	*/
	unsigned get_max_capacity() const;

	/**
	* @brief	  Getter for the current capacity (size of the reservations set)
	*
	* @return	  The current capacity of this Event
	*/
	unsigned get_current_capacity() const;

	/**
	 * @brief     Getter for the location name
	 *
	 * @return    The location's name
	 */
	 std::string get_location_name() const;

	/**
	* @brief	  Getter for the address
	*
	* @return	  The address of this Event
	*/
	Address get_address() const;

	/**
	* @brief	  Getter for the time
	*
	* @return	  The time of this Event
	*/
	Time get_time() const;

	/**
	* @brief	  Getter for the date
	*
	* @return	  The date of this Event
	*/
	Date get_date() const;

	/**
	* @brief	  Getter for the validity
	*
	* @return	  The validity of this Event
	*/
	bool get_validity() const;

	/**
	* @brief	  Getter for the percentage of the Event's capacity
	*
	* @return	  The fraction of the current capacity and maximum capacity, in percentage
	*/
	float get_capacity_percentage() const;


	/* SETTERS */
    /**
     * @brief Setter for the maximum capacity
     *
     * @param new_capacity The new max capacity for this event
     */
    void set_max_capacity(unsigned new_capacity);
    /**
     * @brief Setter for the name of this Event
     *
     * @param new_name The new name for this Event
     */
    void set_name(const std::string &new_name);
    /**
     * @brief Setter for the ticket fee of this Event
     *
     * @param new_ticket_fee The new ticket fee for this Event
     */
    void set_ticket_fee(float new_ticket_fee);
    /**
     * @brief Setter for the location name of this Event
     *
     * @param new_location_name The new location name for this Event
     */
    void set_location_name(const std::string &new_location_name);
    /**
     * @brief Setter for the address of this Event
     *
     * @param new_address The new address for this Event
     */
    void set_address(const Address &new_address);
    /**
     * @brief Setter for the time of this Event
     *
     * @param new_time The new time for this Event
     */
    void set_time(const Time &new_time);
    /**
     * @brief Seter for the date of this Event
     *
     * @param new_date The new date for this Event
     */
    void set_date(const Date &new_date);
	/**
	* @brief	 When called sets an Event's id to 0, aka an absolutely invalid Event\n
	*		     WARNING: Once this method is called, there is no going back
	*
	* @details	 Completely destructive method (irreversible)
	*/
	void set_invalid_id();
	/**
	 * @brief Setter for the is_valid flag of this Event
	 * @details This method is not destructive (can be reverted)
	 * @param new_is_valid The new is_valid flag for this Event
	 */
    void set_validity(bool new_is_valid);


	/**
	* @brief	Handles the purchase of this Event by an user
	*
	* @param cc	The cc of the person trying to purchase this Event
	*
	* @throws InvalidObject	Thrown if the Event is at max capacity\n
	*			Thrown if the is_valid flag of the Event is set to false\n
	*			Thrown if the Event was already bough by the user with the provided cc
	*/
	void purchase(unsigned cc);

	/**
	* @brief	  Returns if the Event is completely full
	*
	* @return	True if the Event is completely full\n
	*		False, otherwise
	*/
	bool is_full() const;

	/**
	* @brief	  Returns if the Event is more than half-full
	*
	* @return	  True if the Event is more than half-full\n
	*		  False, otherwise
	*/
	bool is_half_full() const;

	/**
	* @brief	 Return if the Event has already started / is already over
	*
	* @return	  True if the current Time and Date are past the Event's Time and Date\n
	*		  False, otherwise
	*/
	bool is_over() const;

	/**
	* @brief	Overloaded equality test operator
	*
	* @param	ev	The rightmost Event to compare
	*
	* @return	True if both Event's ids are equal\n
	*		False, otherwise
	*/
	inline bool operator==(const Event &ev) const { return this->id == ev.id; };

	/**
	* @brief	Overloaded inequality test operator
	*
	* @param	ev	The rightmost Event to compare
	*
	* @return	True if both Event's ids are different\n
	*		False, otherwise
	*/
	inline bool operator!=(const Event &ev) const { return !this->operator==(ev); };

	/**
	* @brief	Overloaded lesser than test operator
	*
	* @param	ev	The rightmost Event to compare
	*
	* @return	True if the leftmost Event has a lower id than the rightmost Event\n
	*		False, otherwise
	*/
	inline bool operator<(const Event &ev) const { return this->id < ev.id; };


	/**
	* @brief	Prints an Event to an ostream\n
	*		Prints the Event alongside its discounted entry fee
	*
	* @param	outstream	Reference to the ostream object to insert info to
	* @param	discount	The discount to apply to the event\n
	*		Should be in the range [0, 1], but if higher will actually increase the Event's entry fee
	*/
	void print_with_discount(std::ostream &outstream, float discount=0.0) const;

	/**
	* @brief	Overloaded ostream insertion operator
	*
	* @details	Mainly used with std::cout to show formated information on screen
	*
	* @param	outstream	Reference to the ostream object to insert info to
	* @param	ev	Reference to Event object whose info will be inserted in the ostream
	*
	* @return	Reference to the ostream object, 'outstream', passed in the parameters
	*/
	friend std::ostream& operator<<(std::ostream &outstream, const Event &ev);

	/**
	* @brief	Overloaded ofstream insertion operator
	*
	* @details	Used to save information on a file so it can be read again at a later date
	*
	* @param outfstream	Reference to the ofstream object to insert info to
	* @param ev		Reference to Event object whose info will be inserted in the ofstream
	*
	* @return	Reference to the ofstream object, 'outfstream', passed in the parameters
	*/
	friend std::ofstream& operator<<(std::ofstream &outfstream, const Event &ev);

	/**
	* @brief	Overloaded ifstream extraction operator
	*
	* @details	Used to read information that has been saved to a file previously
	*
	* @param	infstream	Reference to the ifstream object to extract info from
	* @param	ev		Reference to Time object where the read information is saved
	*
	* @return	Reference to the ifstream object, 'instream', passed in the parameters
	*/
	friend std::ifstream &operator>>(std::ifstream &infstream, Event &ev);

	/**
	* @brief	Read an Event from cin, outputting any user prompts to cout
	*
	* @param	ev	Event to read from cin\n
	*			The Event will only have a valid id if the read operation was successful (cin's fail flag set to true)\n
	*			Otherwise, the Event's id is 0
	*/
	static void cin_read_event(Event &ev);

	};

	/** @relatesalso	Event
	 * @brief	Overloaded equality test operator
	 *
	 * @param	ev	Reference to the Event object to be tested
	 * @param	id	Id to be tested
	 *
	 * @return	True,  if the Event object's id and the unsigned id are the same\n
	 *		False, otherwise
	 */
	inline bool operator==(const Event& ev, const unsigned id) { return ev.get_id() == id; };

	/** @relatesalso	Event
	 * @brief	Overloaded equality test operator
	 *
	 * @param	id	Id to be teste
	 * @param	ev	Reference to the Event object to be tested
	 *
	 * @return	True,  if the Event object's id and the unsigned id are the same\n
	 *		False, otherwise
	 */
	inline bool operator==(const unsigned id, const Event& ev) { return operator==(ev, id); };

	/** @relatesalso	Event
	 * @brief	Overloaded equality test operator
	 *
	 * @param ev	Reference to the Event object to be tested
	 * @param id	Id to be teste
	 *
	 * @return	True,  if the Event object's id and the unsigned id are the same\n
	 *		False, otherwise
	 */
	inline bool operator!=(const Event& ev, const unsigned id) { return ev.get_id() != id; };

	/** @relatesalso	Event
	 * @brief	Overloaded equality test operator
	 *
	 * @param	id	Id to be teste
	 * @param	ev	Reference to the Event object to be tested
	 *
	 * @return	True,  if the Event object's id and the unsigned id are the same\n
	 *		False, otherwise
	 */
	inline bool operator!=(const unsigned id, const Event& ev) { return operator!=(ev, id); };

/** @} */

#endif // EVENT_H
