/** @file cards.h */
#ifndef CARDS_H
#define CARDS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/exceptions.h"
#include "../include/utilities.h"
#include "address.h"
#include "date.h"

/** @addtogroup	museum_grp
 *
 * @{
 */

/** @brief	how old (in days) do you have to be in order to be able to get a
 * Silver card */
#define ELDERY_MIN_AGE (65 * 365)
/** @brief	can only renew card with max 60 days until expiration */
#define MAX_DAYS_BEFORE_RENEW 60
/** @brief	for formatted outputs */
#define CARDS_OUTPUT_DELIM 15

/** @brief	identifier of the Individual Card type */
#define INDIVIDUALCARD_TYPE 0
/** @brief	identifier of the UniCard Card type */
#define UNICARD_TYPE 1
/** @brief	identifier of the Silver Card type */
#define SILVERCARD_TYPE 2

/**
 * @brief	Abstract class to save and handle registered users information
 * and their cards
 */
class Card
{
private:
  /** @brief	the user's citizen card number */
  unsigned int cc;
  /** @brief	the user's name */
  std::string name;
  /** @brief	the user's contact (phone number or email, etc...) */
  std::string contact;
  /** @brief	the user's address */
  Address address;

  /** @brief	the user's birth date */
  Date birth_date;
  /** @brief	the user's Card creation date */
  Date creation_date;
  /** @brief	the user's Card expiration date */
  Date expiration_date;

public:
  /* CONSTRUCTORS */
  /**
   * @brief	Default constructor of the class Card
   *
   * @details	Card class is abstract so it can't be instantiated
   */
  Card() = default;
  /**
   * @brief	Full constructor of the class Card
   *
   * @details	Card class is abstract so it can't be instantiated
   *
   * @param name		Name of the user
   * @param contact	Contact of the user (can be an email address, phone
   * number, etc.)
   * @param cc		CC number of the user
   * @param birth_date	Date of birth of the user
   * @param address	User address
   */
  Card(const std::string& name,
       const std::string& contact,
       const unsigned int cc,
       const Date& birth_date,
       const Address& address);

  /* DESTRUCTOR */
  /** @brief	Default destructor for the class Card */
  virtual ~Card() = default;

  /* OTHER METHODS */
  /**
   * @brief	Read a card information from std::cin with prompts (given
   * through std::cout)
   *
   * @details	The function will create a new Card class of the correct type
   * and make the pointer point to it
   *
   * @param c	Pointer to a Card class
   */
  static void cin_read_card(Card*& c);
  /**
   * @brief	Check if the Card is not expired
   *
   * @return	true, if expiration_date appears chronologically later than the
   * current system date
   */
  bool isvalid() const;
  /**
   * @brief	Renews the user card
   *
   * @throws	TooEarlyToRenewCard	when the card is valid and there are
   * more than MAX_DAYS_BEFORE_RENEW until renewal
   */
  void renew();

  /* SETTERS */
  /**
   * @brief	Changes user's saved contact
   *
   * @param contact	new user contact
   */
  void set_contact(const std::string& contact)
  {
    if (!utl::isStrEmpty(contact))
      this->contact = contact;
    else
      throw UserInputReadingFailure("Empty contact!");
  }
  /**
   * @brief	Changes user's saved name
   *
   * @param name		new user name
   */
  void set_name(const std::string& name)
  {
    if (utl::isStrEmpty(name))
      this->name = name;
    else
      throw UserInputReadingFailure("Empty name!");
  }
  /**
   * @brief	Changes user's saved birth date
   *
   * @param d		new user birth date
   */
  void set_birth_date(const Date& d) { this->birth_date = d; }
  /**
   * @brief	Changes user's saved address
   *
   * @param a		new user saved address
   */
  void set_address(const Address& a) { this->address = a; }

  /* GETTERS */
  /**
   * @brief	get user's saved CC
   *
   * @return	user's CC
   */
  unsigned int get_cc() const;
  /**
   * @brief	get user's saved contact
   *
   * @return	user's contact
   */
  std::string get_contact() const;
  /**
   * @brief	get user's saved name
   *
   * @return	user's name
   */
  std::string get_name() const;
  /**
   * @brief	get user's saved creation date
   *
   * @return	card's creation date
   */
  Date get_creation_date() const;
  /**
   * @brief	get user's saved birth date
   *
   * @return	user's birth date
   */
  Date get_birth_date() const;
  /**
   * @brief	get user's saved expiration date
   *
   * @return	card's expiration date
   */
  Date get_expiration_date() const;
  /**
   * @brief	get user's saved address
   *
   * @return	user's address
   */
  Address get_address() const;
  /**
   * @brief	get user's card type
   *
   * @return	user's card type id
   */
  virtual int get_type() const = 0;

  /* INSERTION OPERATOR OVERLOAD */
  /**
   * @brief	Overloaded ostream insertion operator
   *
   * @details	Mainly used with std::cout to show formated information on
   * screen
   *
   * @param outstream	Reference to the ostream object to insert info to
   * @param c		Reference to the Card object whose info will be inserted
   * in the ostream
   *
   * @return	Reference to the ostream object, 'outstream', passed in the
   * parameters
   */
  friend std::ostream& operator<<(std::ostream& outstream, const Card& c);
  /**
   * @brief	Overloaded ofstream insertion operator
   *
   * @details	Used to save information on a file so it can be read again at a
   * later date
   *
   * @param outstream	Reference to the ofstream object to insert info to
   * @param c		Reference to the Card object whose info will be inserted
   * in the ofstream
   *
   * @return	Reference to the ofstream object, 'outstream', passed in the
   * parameters
   */
  friend std::ofstream& operator<<(std::ofstream& outstream, const Card& c);
  /**
   * @brief	Overloaded ifstream extraction operator
   *
   * @details	Used to read information that has been saved to a file
   * previously
   *
   * @param instream	Reference to the ifstream object to extract info from
   * @param c		Reference to the Card object where the read information
   * is saved
   *
   * @return	Reference to the ifstream object, 'instream', passed in the
   * parameters
   */
  friend std::ifstream& operator>>(std::ifstream& instream, Card*& c);
};

/* TYPE 0 */
/**
 * @brief	Saves and handles a normal user's card and information
 */
class IndividualCard : public Card
{
public:
  /* CONSTRUCTORS */
  /**
   * @brief	Default constructor of the class IndividualCard class
   */
  IndividualCard() = default;
  /**
   * @brief	Create an IndividualCard object with the given information
   *
   * @param name		user's name
   * @param contact	user's contact (can be email, phone number, etc.)
   * @param cc		user's CC number
   * @param birth_date	user's birth date
   * @param address	user's address
   */
  IndividualCard(const std::string& name,
                 const std::string& contact,
                 unsigned int cc,
                 const Date& birth_date,
                 const Address& address)
    : Card(name, contact, cc, birth_date, address){};

  /* GETTERS */
  /**
   * @brief	get user's card type
   *
   * @return	user's card type id
   */
  int get_type() const { return INDIVIDUALCARD_TYPE; };
};

/* TYPE 1 */
/**
 * @brief	Saves and handles a university student's card and information
 */
class UniCard : public Card
{
public:
  /* CONSTRUCTORS */
  /**
   * @brief	Default constructor of the class UniCard class
   */
  UniCard() = default;
  /**
   * @brief	Create an UniCard object with the given information
   *
   * @param name		user's name
   * @param contact	user's contact (can be email, phone number, etc.)
   * @param cc		user's CC number
   * @param birth_date	user's birth date
   * @param address	user's address
   */
  UniCard(const std::string& name,
          const std::string& contact,
          unsigned int cc,
          const Date& birth_date,
          const Address& address)
    : Card(name, contact, cc, birth_date, address){};

  /* GETTERS */
  /**
   * @brief	get user's card type
   *
   * @return	user's card type id
   */
  int get_type() const { return UNICARD_TYPE; };
};

/* TYPE 2 */
/**
 * @brief	Saves and handles a senior user's card and information
 */
class SilverCard : public Card
{ // type 2
public:
  /* CONSTRUCTORS */
  /**
   * @brief	Default constructor of the class SilverCard class
   */
  SilverCard() = default;
  /**
   * @brief	Create an SilverCard object with the given information
   *
   * @param name		user's name
   * @param contact	user's contact (can be email, phone number, etc.)
   * @param cc		user's CC number
   * @param birth_date	user's birth date
   * @param address	user's address
   */
  SilverCard(const std::string& name,
             const std::string& contact,
             unsigned int cc,
             const Date& birth_date,
             const Address& address)
    : Card(name, contact, cc, birth_date, address){};

  /* GETTERS */
  /**
   * @brief	get user's card type
   *
   * @return	user's card type id
   */
  int get_type() const { return SILVERCARD_TYPE; };
};

/* COMPARISON OPERATOR OVERLOAD */
/** @relatesalso Card
 * @brief	Overloaded equality test operator
 *
 * @param lhs	Reference to one of the Card objects to be tested
 * @param rhs	Reference to one of the Card objects to be tested
 *
 * @return	true, if the 2 objects have the same CC\n
                false, otherwise
 */
bool operator==(const Card& lhs, const Card& rhs);
/** @relatesalso Card
 * @brief	Overloaded inequality test operator
 *
 * @param lhs	Reference to one of the Card objects to be tested
 * @param rhs	Reference to one of the Card objects to be tested
 *
 * @return	true, if the 2 objects have different CC's\n
                false, otherwise
 */
bool operator!=(const Card& lhs, const Card& rhs);

/** @} */

#endif // CARDS_H
