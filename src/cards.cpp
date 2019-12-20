#include "../include/cards.h"

#include <iomanip>

using namespace std;

Card::Card(const string& name,
           const string& contact,
           const unsigned int cc,
           const Date& birth_date,
           const Address& address)
  : creation_date()
  , expiration_date()
{
  this->name       = name;
  this->contact    = contact;
  this->cc         = cc;
  this->birth_date = birth_date;
  this->address    = address;

  this->expiration_date
    .ffyear(); // expiration date is 1 year from creation date
}

bool
Card::isvalid() const
{
  /* compare expiration date with current date */
  return this->expiration_date >= Date();
}

void
Card::renew()
{
  /* renewing adds 1 more year to the validity period of a card */
  /* check is card is already expired */
  if (this->isvalid()) {
    if ((Date() - this->expiration_date) <= MAX_DAYS_BEFORE_RENEW)
      this->expiration_date.ffyear();
    else
      throw TooEarlyToRenewCard(this->name);
  }
  else {
    this->expiration_date = Date(); // compare with current date
    this->expiration_date.ffyear(); // move expiration date to 1 year from now
  }
}

/* getters */
unsigned int
Card::get_cc() const
{
  return this->cc;
}

string
Card::get_contact() const
{
  return this->contact;
}

string
Card::get_name() const
{
  return this->name;
}

Date
Card::get_creation_date() const
{
  return this->creation_date;
}

Date
Card::get_birth_date() const
{
  return this->birth_date;
}

Date
Card::get_expiration_date() const
{
  return this->expiration_date;
}

Address
Card::get_address() const
{
  return this->address;
}

/* operator overload */
bool
operator==(const Card& lhs, const Card& rhs)
{
  return lhs.get_cc() == rhs.get_cc();
}

bool
operator!=(const Card& lhs, const Card& rhs)
{
  return !(lhs == rhs);
}

ostream&
operator<<(ostream& outstream, const Card& c)
{
  static const string type[3] = { "Individual Card",
                                  "University Card",
                                  "Silver Card" };

  outstream << left << setw(CARDS_OUTPUT_DELIM) << "Name"
            << " : " << right << c.name << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "Type"
            << " : " << right << type[c.get_type()] << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "CC"
            << " : " << right << c.cc << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "Contact"
            << " : " << right << c.contact << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "Address"
            << " : " << right << c.address << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "Birth date"
            << " : " << right << c.birth_date << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "Creation date"
            << " : " << right << c.creation_date << endl
            << left << setw(CARDS_OUTPUT_DELIM) << "Expiration date"
            << " : " << right << c.expiration_date;

  return outstream;
}

std::ofstream&
operator<<(std::ofstream& outstream, const Card& c)
{
  outstream << c.name << endl;
  outstream << to_string(c.get_type()) << endl;
  outstream << to_string(c.cc) << endl;
  outstream << c.contact << endl;
  outstream << c.address << endl;
  outstream << c.birth_date << endl;
  outstream << c.creation_date << endl;
  outstream << c.expiration_date;

  return outstream;
}

std::ifstream&
operator>>(std::ifstream& instream, Card*& c)
{
  c = nullptr;
  try {
    string temp_str;
    getline(instream, temp_str);

    /* type */
    int type;
    instream >> type;
    utl::ignore(instream);
    if (instream.fail())
      throw FileReadingFailed("Birth date reading failed");

    /* instanciate right class */
    if (type == INDIVIDUALCARD_TYPE)
      c = new IndividualCard;
    else if (type == UNICARD_TYPE)
      c = new UniCard;
    else if (type == SILVERCARD_TYPE)
      c = new SilverCard;
    else
      throw FileReadingFailed("No such card type");

    if (c == nullptr) // checking if memory allocation was successful
      throw FileReadingFailed("Failed allocating memory");

    /* name */
    c->name = temp_str;
    if (utl::isStrEmpty(c->name))
      throw FileReadingFailed("given name is empty");

    /* CC */
    std::string temp_cc;
    getline(instream, temp_cc);
    if (utl::isNum(temp_cc))
      c->cc = stoi(temp_cc);
    else
      throw FileReadingFailed("Given CC is not a number: " + temp_cc);

    /* contact */
    getline(instream, c->contact);
    if (utl::isStrEmpty(c->contact))
      throw FileReadingFailed("given name is empty");

    /* address */
    instream >> c->address;
    if (instream.fail())
      throw "Address reading failed";

    /* date */
    instream >> c->birth_date;
    if (instream.fail())
      throw "Birth date reading failed";
    instream >> c->creation_date;
    if (instream.fail())
      throw "Creation date reading failed";
    instream >> c->expiration_date;
    if (instream.fail())
      throw "Expiration date reading failed";
  }
  catch (char const* e) {
    /* In this case the exception has already been taken care of by another
     * function/class/method */
    if (c != nullptr) {
      delete (c);
      c = nullptr;
    }
  }
  catch (const std::exception& e) {
    if (c != nullptr) {
      delete (c);
      c = nullptr;
    }

    instream.setstate(std::ios::failbit);

    std::cerr << e.what() << endl;
  }

  return instream;
}

void
Card::cin_read_card(Card*& c)
{
  c = nullptr;
  try {
    /* get birth date */
    cout << "Date of birth (year/month/day)? ";
    Date temp_bday;
    std::cin >> temp_bday;
    if (cin.fail())
      throw "Birth date reading failed";

    /* instanciate right type of card */
    if (Date() - temp_bday >= ELDERY_MIN_AGE)
      c = new SilverCard;
    else {
      std::cout << "Are you an university student (Y/N)? ";
      char is_uni;
      std::cin >> is_uni;
      utl::ignore(std::cin);

      if (is_uni == 'Y' || is_uni == 'y')
        c = new UniCard;
      else
        c = new IndividualCard;
    }
    if (c == nullptr) // checking if memory allocation was successful
      throw "Failed Card memory allocation";

    c->birth_date = temp_bday;

    /* name */
    std::cout << "Name? ";
    getline(std::cin, c->name);
    if (utl::isStrEmpty(c->name))
      throw UserInputReadingFailure("given name is empty");

    /* CC */
    std::cout << "CC (without control characters)? ";
    std::string temp_cc;
    getline(std::cin, temp_cc);
    if (utl::isNum(temp_cc))
      c->cc = stoi(temp_cc);
    else
      throw UserInputReadingFailure("given CC is not a number: " + temp_cc);

    /* contact */
    std::cout << "Contact (email or phone number prefered)? ";
    getline(std::cin, c->contact);
    if (utl::isStrEmpty(c->contact))
      throw UserInputReadingFailure("given contact is empty");

    /* address */
    cout << "Address (street name/XXXX-XXX/region name  or	region)? ";
    std::cin >> c->address;
    if (cin.fail())
      throw "Address reading failed";

    /* creation date is now */
    Date temp_now;
    c->creation_date = temp_now;

    /* expiration date is 1 year from now */
    temp_now.ffyear();
    c->expiration_date = temp_now;
  }
  catch (char const* e) {
    /* In this case the exception has already been taken care of by another
     * function/class/method */

    if (c != nullptr) {
      delete (c);
      c = nullptr;
    }
  }
  catch (const std::exception& e) {
    if (c != nullptr) {
      delete (c);
      c = nullptr;
    }

    std::cin.setstate(std::ios::failbit);

    std::cerr << e.what() << endl;
  }
}
