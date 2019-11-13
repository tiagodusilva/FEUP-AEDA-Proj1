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
    static unsigned id_tracker;
    unsigned id, max_capacity;
    std::string name;
    float ticket_fee;
    Address address;
    Time time;
    Date date;
    std::set<unsigned> reservations;
    bool is_valid;

public:
    /**
     * @brief	Default constructor
     *
     * @details	Does not attribute a valid id to the event (id = 0)
     */
    Event() = default;

    /**
     * @brief    Complete Event constructor, assigns a completely new and unique ID to the Event
     *
     * @param name           The name of the Event
     * @param cost           The cost of the Event
     * @param max_capacity   The maximum capacity of the Event, this is, the maximum number of elements of the reservations set)
     * @param address        The address of the Event
     * @param time           The time an Event starts
     * @param date           The day of the Event
     * @param reservations   The set containing all the cc's of customers who have bought this Event (may not be members of the Network)\n
     *                       Defaults to an empty set
     * @param is_valid       A flag indicating if an Event is valid or not (to be used for various purposes by an enterprise)
     *                       Defaults to true
     */
    Event(const std::string& name, float cost, unsigned max_capacity, const Address& address, const Time &time, const Date &date, const std::set<unsigned> &reservations=std::set<unsigned>(), bool is_valid=true);
    /**
     * @brief    Default destructor
     */
    ~Event() = default;

    /**
     * @brief     Getter for the id
     *
     * @return    The id of this Event\n
     *            Id 0 has the special meaning of having been instantiated through the default constructor
     */
    unsigned get_id() const;

    /**
     * @brief     Getter for the entry fee
     *
     * @return    The entry fee of this Event
     */
    float get_fee() const;

    /**
     * @brief     Getter for the name
     *
     * @return    The name of this Event
     */
    std::string get_name() const;

    /**
     * @brief     Getter for the maximum capacity
     *
     * @return    The maximum capacity of this Event
     */
    unsigned get_max_capacity() const;

    /**
     * @brief     Getter for the current capacity (size of the reservations set)
     *
     * @return    The current capacity of this Event
     */
    unsigned get_current_capacity() const;

    /**
     * @brief     Getter for the address
     *
     * @return    The address of this Event
     */
    Address get_address() const;

    /**
     * @brief     Getter for the time
     *
     * @return    The time of this Event
     */
    Time get_time() const;

    /**
     * @brief     Getter for the date
     *
     * @return    The date of this Event
     */
    Date get_date() const;

    /**
     * @brief     Getter for the validity
     *
     * @return    The validity of this Event
     */
    bool get_validity() const;

    /**
     * @brief     Getter for the percentage of the Event's capacity
     *
     * @return    The fraction of the current capacity and maximum capacity, in percentage
     */
    float get_capacity_percentage() const;

    /**
     * @brief    Completely destructive method\n
     *           When called sets an Event's id to 0, aka an absolutely invalid Event\n
     *           WARNING: Once this method is called, there is no going back
     */
    void set_invalid_id();


    /**
     * @brief	Handles the purchase of this Event by an user
     *
     * @param	cc	The cc of the person trying to purchase this Event
     *
     * @throws	EventFull		Thrown if the Event is at max capacity
     * @throws	EventInvalid		Thrown if the is_valid flag of the Event is set to false
     * @throws	EventAlreadyBough	Thrown if the Event was already bough by the user with the provided cc
     */
    void purchase(unsigned cc);

    /**
     * @brief     Returns if the Event is completely full
     *
     * @return    True if the Event is completely full\n
     *             False, otherwise
     */
    bool is_full() const;

    /**
     * @brief     Returns if the Event is more than half-full
     *
     * @return    True if the Event is more than half-full\n
     *            False, otherwise
     */
    bool is_half_full() const;

    /**
     * @brief    Return if the Event has already started / is already over
     *
     * @return    True if the current Time and Date are past the Event's Time and Date\n
    *             False, otherwise
     */
    bool is_over() const;

    /**
     * @brief	Overloaded equality test operator
     *
     * @param	ev	The rightmost Event to compare
     *
     * @return	True if both Event's ids are equal\n
     *          False, otherwise
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
    inline bool operator!=(const Event &ev) const { return !this->operator==(ev); }

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
