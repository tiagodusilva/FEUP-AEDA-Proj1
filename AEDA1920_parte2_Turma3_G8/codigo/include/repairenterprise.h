/** @file repairenterprise.h */
#ifndef REPAIRENTERPRISE_H
#define REPAIRENTERPRISE_H

#include <string>
#include <tuple>

#include "../include/address.h"
#include "../include/enterprise.h"

#define REPAIRENTER_OUTPUT_DELIM 15

/** @addtogroup	museum_grp
 * @{
 */

/** @brief  Enterprise that provides repair services to a museum. */
class RepairEnterprise : public BaseEnterprise
{
private:
  /** @brief  Number of jobs done for the network. */
  unsigned int njobs;
  /** @brief  GPS decimal coordinates of the enterprise. */
  std::tuple<float, float> coordinates;

public:
  /* CONSTRUCTORS */
  RepairEnterprise() = default;
  /**
   * @brief Complete Enterprise constructor.
   *
   * @param name		The name of the Enterprise.
   * @param contact	The contact of the Enterprise.
   * @param address	The address of the Enterprise.
   * @param coord	  The address coordinates of the Enterprise.
   * @param njobs   The number of jobs done by the Enterprise.
   */
  RepairEnterprise(const std::string& name,
                   const std::string& contact,
                   const Address& address,
                   const std::tuple<float, float> coord,
                   const unsigned int njobs = 0);
  /** @brief  Default destructor */
  ~RepairEnterprise() = default;

  /* GETTERS */
  std::tuple<float, float> get_coords() const { return this->coordinates; }
  unsigned int get_numjobs() const { return this->njobs; }

  /* SETTERS */
  void set_coords(std::tuple<float, float> coords);
  void set_numjobs(unsigned int num_jobs);

  /* OTHER */
  /** @brief  Increase this enterprise number of jobs done for the network. */
  void hire() { ++this->njobs; }
  /**
   * @brief   Overloaded less-than operator.
   * @note    Mostly used to organize RepairEnterprise in min-heaps.
   *
   * @param rhs Reference to one of the RepairEnterprise object to compare.
   *
   * @return  true, if lhs is considered less-than rhs,\n
   *          false, otherwise.
   */
  bool operator<(const RepairEnterprise& rhs) const
  {
    return (this->njobs < rhs.njobs);
  }

  /* OVERLOADED INSERTION OPERATOR */
  /**
   * @brief Overloaded ostream insertion operator
   *
   * @details Mainly used with std::cout to show formated information
   *          on screen
   *
   * @param outstream Reference to the ostream object to insert info to
   * @param ent	      Reference to the Enterprise object whose info will be
   *                  inserted in the ostream
   *
   * @return  Reference to the ostream object, 'outstream', passed in
   *          the parameters
   */
  friend std::ostream& operator<<(std::ostream& outstream,
                                  const RepairEnterprise& ent);
  /**
   * @brief Overloaded ofstream insertion operator
   *
   * @details Used to save information on a file so it can be read
   *          again at a later date
   *
   * @param outfstream  Reference to the ofstream object to insert info to
   * @param ent		      Reference to Enterprise object whose info will be
   *                    inserted in the ofstream
   *
   * @return  Reference to the ofstream object, 'outfstream', passed
   *          in the parameters
   */
  friend std::ofstream& operator<<(std::ofstream& outfstream,
                                   const RepairEnterprise& ent);
  /* OVERLOAD EXTRACTION OPERATOR */
  /**
   * @brief Overloaded ifstream extraction operator
   *
   * @details Used to read information that has been saved to a file
   *          previously
   *
   * @param infstream Reference to the ifstream object to extract info from
   * @param ent	      Reference to Enterprise object where the read information
   *                  is saved
   *
   * @return  Reference to the ifstream object, 'infstream', passed in the
   * parameters
   */
  friend std::ifstream& operator>>(std::ifstream& infstream,
                                   RepairEnterprise& ent);

  /* READ ENTERPRISE FROM STD::CIN */
  /**
   * @brief	Read an Enterprise from cin, outputting any user prompts to cout
   *
   * @param	ent	Enterprise to read from cin\n
   */
  static void cin_read_repairenterprise(RepairEnterprise& ent);
};

/** @} */

#endif // REPAIRENTERPRISE_H
