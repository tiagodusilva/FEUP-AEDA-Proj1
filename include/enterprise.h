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
    std::string name;
    std::string contact;
    Address address;
    std::set<Event> events;

public:
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


    /**
     * @brief          Adds an Event to the Enterprise\n
     *                 If successful, the destructor of ev will be called
     *
     * @throws   EventAlreadyExists Thrown if the Event already exists in the Enterprise\n
     *                              That said, if it does get thrown, something really odd is going on
     *
     * @param ev        Event to add to the Enterprise\n
     *                  If the Event is added successfully, the Event's id will permanently be set to 0, to guarantee the uniqueness of every Event
     *
     */
    void add_event(Event &ev);

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


    /**
     * @brief     Overloaded equality test operator
     *
     * @details   As all of our enterprises must be registered in our country, their names will ALWAYS be
     *            different by law, therefore we only need to compare their names
     *
     * @param     The rightmost Enterprise to compare
     *
     * @return    True if both Enterprises' names are equal\n
     *            False, otherwise
     */
    inline bool operator== (const Enterprise &ent) { return this->name == ent.name; };

    /**
     * @brief     Overloaded inequality test operator
     *
     * @details   As all of our enterprises must be registered in our country, their names will ALWAYS be
     *            different by law, therefore we only need to compare their names
     *
     * @param     The rightmost Enterprise to compare
     *
     * @return    True if both Enterprises' names are different\n
     *            False, otherwise
     */
    inline bool operator!= (const Enterprise &ent) { return !this->operator==(ent); };


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

    /**
     * @brief       Read an Enterprise from cin, outputting any user prompts to cout
     *
     * @param ev    Enterprise to read from cin\n
     */
    static void cin_read_enterprise(Enterprise &ent);

};

/** @} */

#endif // ENTERPRISE_H
