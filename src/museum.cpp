#include "../include/museum.h"
#include "../include/exceptions.h"
#include "../include/utilities.h"

#include <iomanip>

using namespace std;

Museum::Museum(const string& name,
               const Time& open,
               const Time& close,
               float entry_fee,
               const Address& address,
               const std::tuple<float, float>& coord)
  : nvisits()
{
  this->name        = name;
  this->open        = open;
  this->close       = close;
  this->entry_fee   = entry_fee;
  this->address     = address;
  this->coordinates = coord;
}

/* GETTERS */
string
Museum::get_name() const
{
  return this->name;
}

Time
Museum::get_open() const
{
  return this->open;
}

Time
Museum::get_close() const
{
  return this->close;
}

float
Museum::get_fee() const
{
  return this->entry_fee;
}

Address
Museum::get_address() const
{
  return this->address;
}

std::tuple<float, float>
Museum::get_coords() const
{
  return this->coordinates;
}

unsigned int
Museum::get_numvisits() const
{
  return this->nvisits;
}

/* SETTERS */
void
Museum::set_open(const Time& new_open)
{
  if (new_open > this->close)
    throw UserInputReadingFailure(
      "Museum's opening time must be before the closing time");
  this->open = new_open;
}

void
Museum::set_close(const Time& new_close)
{
  if (this->open > new_close)
    throw UserInputReadingFailure(
      "Museum's closing time must be after the opening time");
  this->close = new_close;
}

void
Museum::set_fee(float new_entry_fee)
{
  if (new_entry_fee < 0)
    throw UserInputReadingFailure("Museum's entry fee must not be negative");
  this->entry_fee = new_entry_fee;
}

void
Museum::set_numvisits(unsigned int nvisits)
{
	this->nvisits = nvisits;
}

/* STREAMS */
std::ostream&
operator<<(std::ostream& outstream, const Museum& museum)
{
  outstream << left << setw(MUSEUM_OUPUT_DELIM) << "Name"
            << " : " << right << museum.name << endl
            << left << setw(MUSEUM_OUPUT_DELIM) << "Opening Hours"
            << " : " << right << museum.open << " to " << museum.close << endl
            << left << setw(MUSEUM_OUPUT_DELIM) << "Entry Fee"
            << " : " << right << museum.entry_fee << endl
            << left << setw(MUSEUM_OUPUT_DELIM) << "Address"
            << " : " << right << museum.address << endl
            << left << setw(MUSEUM_OUPUT_DELIM) << "GPS Coords"
            << " : " << right << "(" << get<0>(museum.coordinates) << ", "
            << get<1>(museum.coordinates) << ")" << endl
            << left << setw(MUSEUM_OUPUT_DELIM) << "Num of visits"
            << " : " << right << museum.nvisits;

  return outstream;
}

std::ofstream&
operator<<(std::ofstream& outfstream, const Museum& museum)
{
  outfstream << museum.name << endl;
  outfstream << museum.open << endl;
  outfstream << museum.close << endl;
  outfstream << fixed << setprecision(2) << museum.entry_fee << endl;
  outfstream << museum.address << endl;
  outfstream << fixed << setprecision(2) << get<0>(museum.coordinates) << endl;
  outfstream << fixed << setprecision(2) << get<1>(museum.coordinates) << endl;
  outfstream << to_string(museum.nvisits);

  return outfstream;
}

std::ifstream&
operator>>(std::ifstream& infstream, Museum& museum)
{
  try {
    // NAME
    getline(infstream, museum.name);

    // OPEN
    infstream >> museum.open;

    // CLOSE
    infstream >> museum.close;

    if (museum.close < museum.open) {
      cout << museum.open << endl << museum.close << endl;
      throw FileReadingFailed("Museum must not open after closing");
    }

    // ENTRY FEE
    infstream >> museum.entry_fee;
    utl::ignore(infstream);
    if (museum.entry_fee < 0)
      throw FileReadingFailed("Museum's entry fee cannot be negative");

    // ADDRESS
    infstream >> museum.address;

    // COORDINATES
    infstream >> get<0>(museum.coordinates);
    infstream >> get<1>(museum.coordinates);

    // NUMBER OF VISITS
    infstream >> museum.nvisits;
  }
  catch (std::exception& e) {
    infstream.setstate(ios::failbit);
    cerr << e.what();
  }

  return infstream;
}

void
Museum::cin_read_museum(Museum& museum)
{
  try {
    /* name */
    std::cout << "Name? ";
    getline(std::cin, museum.name);
    if (utl::isStrEmpty(museum.name))
      throw UserInputReadingFailure("given name is empty");

    /* address */
    cout << "Address (street name/XXXX-XXX/region name  or  region)? ";
    std::cin >> museum.address;
    if (cin.fail())
      throw "Address reading failed";

    /* coordinates */
    cout << "GPS coordinates:\n"
         << "  X: ";
    cin >> get<0>(museum.coordinates);
    utl::ignore(cin);
    cout << "  Y: ";
    cin >> get<1>(museum.coordinates);
    utl::ignore(cin);
    if (cin.fail())
      throw UserInputReadingFailure("given coordinates are not numbers");

    /* entry fee */
    std::cout << "Event's entry fee? ";
    std::cin >> museum.entry_fee;
    utl::ignore(cin);
    if (cin.fail())
      throw UserInputReadingFailure("given name is empty");
    if (museum.entry_fee < 0)
      throw UserInputReadingFailure("Museum's entry fee must not be negative");

    /* opening time */
    cout << "Opening time of the Museum (h:m)? ";
    std::cin >> museum.open;
    if (cin.fail())
      throw "Event time reading failed";

    /* closing time */
    cout << "Closing time of the Museum (h:m)? ";
    std::cin >> museum.close;
    if (cin.fail())
      throw "Event time reading failed";

    if (museum.close < museum.open)
      throw UserInputReadingFailure("Museum must not open after closing");

    /* number of times this museum has been visited */
    std::cout << "Number of visits? ";
    std::cin >> museum.nvisits;
    utl::ignore(cin);
    if (cin.fail())
      throw UserInputReadingFailure("given number of visits is invalid");
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

void
Museum::visit_museum(unsigned int npeople)
{
  this->nvisits += npeople;
}
