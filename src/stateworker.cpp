#include "../include/stateworker.h"

#include <iomanip>

using namespace std;

StateWorker::StateWorker(const std::string name,
                         const std::string& contact,
                         const unsigned int cc,
                         const Date& birth_date,
                         const Address& address)
{
  this->name       = name;
  this->contact    = contact;
  this->cc         = cc;
  this->birth_date = birth_date;
  this->address    = address;

  /* associated museum */
  this->is_hired            = false;
  this->associated_museum   = "";
  get<0>(this->coordinates) = 0;
  get<1>(this->coordinates) = 0;
}

/* GETTERS */
bool
StateWorker::ishired() const
{
  return this->is_hired;
}

void
StateWorker::hire(std::string museum_name,
                  std::tuple<float, float> museum_coord)
{
  if (this->ishired())
    throw UserInputReadingFailure("This worker is already hired.");
  else {
    this->is_hired          = true;
    this->associated_museum = museum_name;
    this->coordinates       = museum_coord;
  }
}

void
StateWorker::fire()
{
  if (this->ishired()) {
    this->is_hired            = false;
    this->associated_museum   = "";
    get<0>(this->coordinates) = 0;
    get<1>(this->coordinates) = 0;
  }
  else
    throw UserInputReadingFailure(
      "This worker doesn't work for the state currently.");
}

unsigned int
StateWorker::get_cc() const
{
  return this->cc;
}

std::string
StateWorker::get_contact() const
{
  return this->contact;
}

std::string
StateWorker::get_name() const
{
  return this->name;
}

Date
StateWorker::get_birth_date() const
{
  return this->birth_date;
}

Address
StateWorker::get_address() const
{
  return this->address;
}

std::string
StateWorker::get_associated_museum() const
{
	return this->associated_museum;
}

std::tuple<float, float>
StateWorker::get_museum_coordinates() const
{
	return this->coordinates;
}

/* OPERATOR OVERLOAD */
bool
operator==(const StateWorker& lhs, const StateWorker& rhs)
{
  return (lhs.cc == rhs.cc);
}

bool
operator!=(const StateWorker& lhs, const StateWorker& rhs)
{
  return !(lhs == rhs);
}

/* OTHER FUNCTIONS */
void
StateWorker::cin_read_worker(StateWorker& w)
{
  try {
    /* name */
    std::cout << "Name? ";
    getline(std::cin, w.name);
    if (utl::isStrEmpty(w.name))
      throw UserInputReadingFailure("given name is empty");

    /* get birth date */
    cout << "Date of birth (year/month/day)? ";
    std::cin >> w.birth_date;
    if (cin.fail())
      throw "Birth date reading failed";

    /* CC */
    std::cout << "CC (without control characters)? ";
    std::string temp_cc;
    getline(std::cin, temp_cc);
    if (utl::isNum(temp_cc))
      w.cc = stoi(temp_cc);
    else
      throw UserInputReadingFailure("given CC is not a number: " + temp_cc);

    /* contact */
    std::cout << "Contact (email or phone number prefered)? ";
    getline(std::cin, w.contact);
    if (utl::isStrEmpty(w.contact))
      throw UserInputReadingFailure("given contact is empty");

    /* address */
    cout << "Address (street name/XXXX-XXX/region name  or	region)? ";
    std::cin >> w.address;
    if (cin.fail())
      throw "Address reading failed";

    /* hiring status */
    string ans = "";
    do {
      cout << "Is this worker being/currently hired? (y/n/q) ";
      getline(std::cin, ans);
    } while (ans != "Y" && ans != "N" && ans != "y" && ans != "n" &&
             ans != "q" && ans != "Q");

    if (ans == "q" || ans == "Q")
      throw UserInputReadingFailure(
        "Quit in the middle of the worker creation operation");

    if (ans == "Y" || ans == "y") {
      w.is_hired = true;
      cout << "Associated museum name: ";
      getline(std::cin, w.associated_museum);
      if (utl::isStrEmpty(w.associated_museum))
        throw UserInputReadingFailure("Tried to associate to an invalid museum");

      cout << "GPS coordinates:\n"
           << "  X: ";
      cin >> get<0>(w.coordinates);
      utl::ignore(cin);
      cout << "  Y: ";
      cin >> get<1>(w.coordinates);
      utl::ignore(cin);
      if (cin.fail())
        throw UserInputReadingFailure("given coordinates are not numbers");
    }
    else {
      w.is_hired            = false;
      w.associated_museum   = "";
      get<0>(w.coordinates) = 0;
      get<1>(w.coordinates) = 0;
    }
  }
  catch (char const* e) {
    /* In this case the exception has already been taken care of by another
     * function/class/method */
    w = StateWorker();
  }
  catch (const std::exception& e) {
    w = StateWorker();

    std::cin.setstate(std::ios::failbit);

    std::cerr << e.what() << endl;
  }
}

/* INSERTION/EXTRACTION OPERATORS OVERLOAD */
std::ostream&
operator<<(std::ostream& outstream, const StateWorker& w)
{
  outstream << left << setw(WORKER_OUTPUT_DELIM) << "Name"
            << " : " << right << w.name << endl
            << left << setw(WORKER_OUTPUT_DELIM) << "CC"
            << " : " << right << w.cc << endl
            << left << setw(WORKER_OUTPUT_DELIM) << "Contact"
            << " : " << right << w.contact << endl
            << left << setw(WORKER_OUTPUT_DELIM) << "Address"
            << " : " << right << w.address << endl
            << left << setw(WORKER_OUTPUT_DELIM) << "Birth date"
            << " : " << right << w.birth_date << endl;

  if (w.is_hired) {
    outstream << left << setw(WORKER_OUTPUT_DELIM) << "Is hired"
              << " : " << right << "yes" << endl
              << left << setw(WORKER_OUTPUT_DELIM) << "Associated museum"
              << " : " << right << w.associated_museum << endl
              << left << setw(WORKER_OUTPUT_DELIM) << "Museum GPS coords"
              << " : " << right << "(" << get<0>(w.coordinates) << ", "
              << get<1>(w.coordinates) << ")" << endl;
  }
  else
    outstream << left << setw(WORKER_OUTPUT_DELIM) << "Is hired"
              << " : " << right << "no";

  return outstream;
}

std::ofstream&
operator<<(std::ofstream& outstream, const StateWorker& w)
{
  outstream << w.name << endl;
  outstream << to_string(w.cc) << endl;
  outstream << w.contact << endl;
  outstream << w.address << endl;
  outstream << w.birth_date << endl;

  /* hiring status */
  outstream << to_string(w.is_hired);
  if (w.is_hired) {
	  outstream << endl << w.associated_museum << endl;
    outstream << fixed << setprecision(2) << get<0>(w.coordinates) << endl;
    outstream << fixed << setprecision(2) << get<1>(w.coordinates);
  }

  return outstream;
}

std::ifstream&
operator>>(std::ifstream& instream, StateWorker& w)
{
  try {
    /* name */
    getline(instream, w.name);
    if (utl::isStrEmpty(w.name))
      throw FileReadingFailed("given name is empty");

    /* CC */
    std::string temp_cc;
    getline(instream, temp_cc);
    if (utl::isNum(temp_cc))
      w.cc = stoi(temp_cc);
    else
      throw FileReadingFailed("Given CC is not a number: " + temp_cc);

    /* contact */
    getline(instream, w.contact);
    if (utl::isStrEmpty(w.contact))
      throw FileReadingFailed("given name is empty");

    /* address */
    instream >> w.address;
    if (instream.fail()) {
      cerr << "F";
      throw "Address reading failed";
    }

    /* date */
    instream >> w.birth_date;
    if (instream.fail())
      throw "Birth date reading failed";

    /* hiring status */
    instream >> w.is_hired;
    utl::ignore(instream); // TODO Rosetti
    if (w.is_hired) {
      getline(instream, w.associated_museum);
      if (utl::isStrEmpty(w.associated_museum))
        throw FileReadingFailed("given associated museum name is empty");

      instream >> get<0>(w.coordinates);
      instream >> get<1>(w.coordinates);
      if (instream.fail())
        throw "Coordinates reading failure";
    }
  }
  catch (char const* e) {
    /* In this case the exception has already been taken care of by another
     * function/class/method */
    w = StateWorker();
  }
  catch (const std::exception& e) {
    w = StateWorker();

    instream.setstate(std::ios::failbit);

    std::cerr << e.what() << endl;
  }

  return instream;
}
