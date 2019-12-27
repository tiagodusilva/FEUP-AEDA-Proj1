#include <iomanip>
#include <iostream>

#include "../include/exceptions.h"
#include "../include/repairenterprise.h"
#include "../include/utilities.h"

using namespace std;

RepairEnterprise::RepairEnterprise(const std::string& name,
                                   const std::string& contact,
                                   const Address& address,
                                   const std::tuple<float, float> coord,
                                   const unsigned int njobs)
  : BaseEnterprise(name, contact, address)
{
  this->coordinates = coord;
  this->njobs       = njobs;
}

void
RepairEnterprise::set_coords(tuple<float, float> coords)
{
  this->coordinates = coords;
}

void
RepairEnterprise::set_numjobs(unsigned int num_jobs)
{
	this->njobs = num_jobs;
}

std::ostream&
operator<<(std::ostream& outstream, const RepairEnterprise& ent)
{
  outstream << (BaseEnterprise)ent << endl;
  outstream << left << setw(ENTERPRISE_OUPUT_DELIM) << "Num of jobs done"
            << " : " << right << ent.njobs << endl
            << left << setw(ENTERPRISE_OUPUT_DELIM) << "GPS Coords"
            << " : " << right << "(" << get<0>(ent.coordinates) << ", "
            << get<1>(ent.coordinates) << ")" << endl
            << left << setw(ENTERPRISE_OUPUT_DELIM) << "Num of jobs"
            << " : " << right << ent.njobs;

  return outstream;
}

std::ofstream&
operator<<(std::ofstream& outfstream, const RepairEnterprise& ent)
{
  outfstream << (BaseEnterprise)ent << endl;
  outfstream << fixed << setprecision(2) << get<0>(ent.coordinates) << endl;
  outfstream << fixed << setprecision(2) << get<1>(ent.coordinates) << endl;
  outfstream << to_string(ent.njobs);

  return outfstream;
}

std::ifstream&
operator>>(std::ifstream& infstream, RepairEnterprise& ent)
{
  try {
    // NAME
    getline(infstream, ent.name);

    // CONTACT
    getline(infstream, ent.contact);

    // ADDRESS
    infstream >> ent.address;

    // COORDINATES
    infstream >> get<0>(ent.coordinates);
    infstream >> get<1>(ent.coordinates);

    // NUMBER OF JOBS DONE
    infstream >> ent.njobs;
  }
  catch (std::exception& e) {
    infstream.setstate(ios::failbit);
    cerr << e.what();
  }

  return infstream;
}

void
RepairEnterprise::cin_read_repairenterprise(RepairEnterprise& ent)
{
  try {
    /* name */
    std::cout << "Name? ";
    getline(std::cin, ent.name);
    if (utl::isStrEmpty(ent.name))
      throw UserInputReadingFailure("given name is empty");

    /* contact */
    std::cout << "Contact (email or phone number prefered)? ";
    getline(std::cin, ent.contact);
    if (utl::isStrEmpty(ent.contact))
      throw UserInputReadingFailure("given contact is empty");

    /* address */
    cout << "Address (street name/XXXX-XXX/region name  or  region)? ";
    std::cin >> ent.address;
    if (cin.fail())
      throw "Address reading failed";

    /* coordinates */
    cout << "GPS coordinates:\n"
         << "  X: ";
    cin >> get<0>(ent.coordinates);
    utl::ignore(cin);
    cout << "  Y: ";
    cin >> get<1>(ent.coordinates);
    utl::ignore(cin);
    if (cin.fail())
      throw UserInputReadingFailure("given coordinates are not numbers");

    /* number of jobs done */
    ent.njobs = 0;
  }
  catch (const char* e) {
    // In this case, the exception would have already been handled
    std::cin.setstate(std::ios::failbit);
  }
  catch (const std::exception& e) {
    std::cin.setstate(std::ios::failbit);
    std::cerr << e.what() << endl;
  }
}
