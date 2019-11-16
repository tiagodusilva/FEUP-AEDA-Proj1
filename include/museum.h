/** @file museum.h */
#ifndef MUSEUM_H
#define MUSEUM_H

#include "../include/address.h"
#include "../include/time.h"

/** @defgroup museum_grp Museum module */

/** @addtogroup	museum_grp
  *
  * @brief	Code related to the handling of a museum
  *
  * @{
  */


/** @brief	number of characters to use with std::setw() on Museum object information output */
#define MUSEUM_OUPUT_DELIM 15


/**
 * @brief    Class that represents the Museums associated with our Network
 */
class Museum {
private:
	/** @brief	the museum's name */
	std::string name;
	/** @brief	the museum's location */
	Address address;

	/** @brief	the museum's opening hour */
	Time open;
	/** @brief	the museum's closing hour */
	Time close;

	/** @brief	the museum's entry ticket cost */
	float entry_fee;

public:
	/* CONSTRUCTORS */
	/**
	 * @brief    Default constructor
	 */
	Museum() = default;
	/**
	 * @brief		 Complete Museum constructor
	 *
	 * @param name		 The name of the Museum
	 * @param open		 The opening Time of the Museum
	 * @param close		 The closing Time of the Museum
	 * @param entry_fee	  The entry fee of the Museum
	 * @param address	 The address of the Museum
	 */
	Museum(const std::string &name, const Time& open, const Time &close, float entry_fee, const Address &address);
	/**
	 * @brief    Default destructor
	 */
	~Museum() = default;

	/* GETTERS */
	/**
	 * @brief     Getter for the name
	 * @return    The name of this Museum
	 */
	std::string get_name() const;
	/**
	 * @brief     Getter for the opening Time
	 * @return    The opening Time of this Museum
	 */
	Time get_open() const;
	/**
	 * @brief     Getter for the closing Time
	 * @return    The closing Time of this Museum
	 */
	Time get_close() const;
	/**
	 * @brief     Getter for the entry fee
	 * @return    The entry fee of this Museum
	 */
	float get_fee() const;
	/**
	 * @brief     Getter for the Address
	 * @return    The Address of this Museum
	 */
	Address get_address() const;


    /* SETTERS */
    /**
     * @brief	Setter for the name
     * @param new_name	The new name for this Museum
     */
    void set_name(const std::string &new_name);
    /**
     * @brief	Setter for the opening Time
     * @param new_open	The new opening Time for this Museum
     */
    void set_open(const Time &new_open);
    /**
     * @brief	Setter for the closing Time
     * @param new_close	The new closing Time for this Museum
     */
    void set_close(const Time &new_close);
    /**
     * @brief	Setter for the entry fee
     * @param new_entry_fee	The new entry fee for this Museum
     */
    void set_fee(float new_entry_fee);


	/* OVERLOADED COMPARISON OPERATORS */
	/**
	 * @brief     Overloaded equality test operator
	 *
	 * @details   Two Museums are considered equal if their name and Address are the same
	 *
	 * @param	museum	The rightmost Museum to compare
	 *
	 * @return    True if both Museums' names and Addresses are equal\n
	 *	      False, otherwise
	 */
	inline bool operator== (const Museum &museum) const { return (this->name == museum.name) && (this->address == museum.address); };
	/**
	 * @brief     Overloaded inequality test operator
	 *
	 * @details   Two Museums are considered equal if their name and Address are the same
	 *
	 * @param	museum	The rightmost Museum to compare
	 *
	 * @return    True if both Museums' names and Addresses are equal\n
	 *	      False, otherwise
	 */
	inline bool operator!= (const Museum &museum) const { return !this->operator==(museum); };

	/* OVERLOADED INSERTION OPERATORS */
	/**
	 * @brief	       Overloaded ostream insertion operator
	 *
	 * @details	       Mainly used with std::cout to show formated information on screen
	 *
	 * @param outstream    Reference to the ostream object to insert info to
	 * @param ent	       Reference to the Museum object whose info will be inserted in the ostream
	 *
	 * @return	       Reference to the ostream object, 'outstream', passed in the parameters
	 */
	friend std::ostream& operator<<(std::ostream &outstream, const Museum &ent);
	/**
	 * @brief		Overloaded ofstream insertion operator
	 *
	 * @details		Used to save information on a file so it can be read again at a later date
	 *
	 * @param outfstream	Reference to the ofstream object to insert info to
	 * @param ent		Reference to Museum object whose info will be inserted in the ofstream
	 *
	 * @return		Reference to the ofstream object, 'outfstream', passed in the parameters
	 */
	friend std::ofstream& operator<<(std::ofstream &outfstream, const Museum &ent);

	/* OVERLOADED EXTRACTION OPERATORS */
	/**
	 * @brief	       Overloaded ifstream extraction operator
	 *
	 * @details	       Used to read information that has been saved to a file previously
	 *
	 * @param infstream    Reference to the ifstream object to extract info from
	 * @param ent	       Reference to Museum object where the read information is saved
	 *
	 * @return	       Reference to the ifstream object, 'infstream', passed in the parameters
	 */
	friend std::ifstream &operator>>(std::ifstream &infstream, Museum &ent);

	/* OTHER FUNCTIONS */
	/**
	 * @brief	Read a Museum from cin, outputting any user prompts to cout
	 *
	 * @param museum	Museum to read from cin\n
	 */
	static void cin_read_museum(Museum & museum);
};

/** @} */

#endif // MUSEUM_H
