/** @file stateworker.h */
#ifndef STATEWORKER_H
#define STATEWORKER_H

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#include "address.h"
#include "date.h"
#include "exceptions.h"
#include "utilities.h"

/** @addtogroup	museum_grp
 *
 * @{
 */

/** @brief	for formatted outputs */
#define WORKER_OUTPUT_DELIM 17

/** @brief  Object that saves the information of a state worker. */
class StateWorker
{
private:
  /** @brief	the worker's citizen card number */
  unsigned int cc;
  /** @brief	the worker's name */
  std::string name;
  /** @brief	the worker's work contact (phone number or email, etc...) */
  std::string contact;
  /** @brief	the worker's birth date */
  Date birth_date;
  /** @brief	the worker's address */
  Address address;
  /** @brief  Indicates if this worker is currently hired */
  bool is_hired;
  /** @brief  Name of the museum where this person works */
  std::string associated_museum;
  /** @brief  GPS decimal coordinates of the associated museum */
  std::tuple<float, float> coordinates;

public:
  /* CONSTRUCTORS */
  /** @brief  Default constructor for the StateWorker class. */
  StateWorker() = default;
  /**
   * @brief Constructor for the StateWorker class.
   *
   * @param name        Name of the worker
   * @param contact     Work contact of the worker
   * @param cc          CC number of the worker
   * @param birth_date  Birth date of the worker
   * @param address     Address of the worker
   */
  StateWorker(const std::string name,
              const std::string& contact,
              const unsigned int cc,
              const Date& birth_date,
              const Address& address);

  /* DESTRUCTOR */
  /** @brief	Default destructor for the class Card */
  virtual ~StateWorker() = default;

  /* OTHER METHODS */
  /**
   * @brief Read a worker's information from std::cin with prompts (given though
   * std::cout)
   *
   * @param w Output of the created StateWorker
   */
  static void cin_read_worker(StateWorker& w);
  /**
   * @brief Indicates if the given worker is currently hired by anyone the
   * museum_network
   *
   * @return  true, if the worker is hired,\n
   *          false, otherwise.
   */
  bool ishired() const;
  /**
   * @brief Hire this worker
   *
   * @param museum_name Name of the museum associated with this worker.
   * @param museum_coord Coords of the museum associated with this worker.
   */
  void hire(std::string museum_name, std::tuple<float, float>museum_coord);
  /** @brief Fire this worker */
  void fire();

  /* SETTERS */
  /**
   * @brief	Changes worker's saved contact
   *
   * @param contact new worker work contact
   */
  void set_contact(const std::string& contact)
  {
    if (!utl::isStrEmpty(contact))
      this->contact = contact;
    else
      throw UserInputReadingFailure("Empty contact!");
  }
  /**
   * @brief	Changes worker's saved name
   *
   * @param name  new worker name
   */
  void set_name(const std::string& name)
  {
    if (!utl::isStrEmpty(name))
      this->name = name;
    else
      throw UserInputReadingFailure("Empty name!");
  }
  /**
   * @brief	Changes worker's saved birth date
   *
   * @param d new worker birth date
   */
  void set_birth_date(const Date& d) { this->birth_date = d; }
  /**
   * @brief	Changes worker's saved address
   *
   * @param a	new worker saved address
   */
  void set_address(const Address& a) { this->address = a; }

  /* GETTERS */
  /**
   * @brief get worker's saved CC
   *
   * @return  worker's CC
   */
  unsigned int get_cc() const;
  /**
   * @brief	get worker's saved contact
   *
   * @return	worker's contact
   */
  std::string get_contact() const;
  /**
   * @brief	get worker's saved name
   *
   * @return	worker's name
   */
  std::string get_name() const;
  /**
   * @brief	get worker's saved birth date
   *
   * @return	worker's birth date
   */
  Date get_birth_date() const;
  /**
   * @brief	get worker's saved address
   *
   * @return	worker's address
   */
  Address get_address() const;
  /**
   * @brief	get worker's saved museum name
   *
   * @return	worker's museum name
   */
  std::string get_associated_museum() const;

  /**
   * @brief	get worker's saved museum coordinates
   *
   * @return	worker's museum coordinates
   */
  std::tuple<float, float> get_museum_coordinates() const;

  /* INSERTION OPERATOR OVERLOAD */
  /**
   * @brief	Overloaded ostream insertion operator
   *
   * @details	Mainly used with std::cout to show formated information on
   * screen
   *
   * @param outstream	Reference to the ostream object to insert info to
   * @param w		      Reference to the StateWorker object whose info
   * will be inserted in the ostream
   *
   * @return	Reference to the ostream object, 'outstream', passed in the
   * parameters
   */
  friend std::ostream& operator<<(std::ostream& outstream,
                                  const StateWorker& w);
  /**
   * @brief	Overloaded ofstream insertion operator
   *
   * @details	Used to save information on a file so it can be read again at a
   * later date
   *
   * @param outstream	Reference to the ofstream object to insert info to
   * @param w		      Reference to the StateWorker object whose info
   * will be inserted in the ofstream
   *
   * @return	Reference to the ofstream object, 'outstream', passed in the
   * parameters
   */
  friend std::ofstream& operator<<(std::ofstream& outstream,
                                   const StateWorker& w);
  /**
   * @brief	Overloaded ifstream extraction operator
   *
   * @details	Used to read information that has been saved to a file
   * previously
   *
   * @param instream	Reference to the ifstream object to extract info from
   * @param w		      Reference to the StateWorker object where the
   * read information is saved
   *
   * @return	Reference to the ifstream object, 'instream', passed in the
   * parameters
   */
  friend std::ifstream& operator>>(std::ifstream& instream, StateWorker& w);

  /* COMPARISON OPERATOR OVERLOAD */
  /** @relatesalso StateWorker
   * @brief	Overloaded equality test operator
   *
   * @param lhs	Reference to one of the StateWorker objects to be tested
   * @param rhs	Reference to one of the StateWorker objects to be tested
   *
   * @return	true, if the 2 objects have the same CC\n
              false, otherwise
   */
  friend bool operator==(const StateWorker& lhs, const StateWorker& rhs);
  /** @relatesalso StateWorker
   * @brief	Overloaded inequality test operator
   *
   * @param lhs	Reference to one of the StateWorker objects to be tested
   * @param rhs	Reference to one of the StateWorker objects to be tested
   *
   * @return	true, if the 2 objects have different CC's\n
              false, otherwise
   */
  friend bool operator!=(const StateWorker& lhs, const StateWorker& rhs);
};

/** @} */

#endif // STATEWORKER_H
