#include "../include/enterprise.h"
#include "../include/exceptions.h"
#include "../include/utilities.h"

#include <iomanip>

using namespace std;

/* PRIVATE */

Event
Enterprise::pop(unsigned id)
{
  // Apparently sets always return const iterators... so yeah... about that
  // one... This method was born to ease that pain
  for (const auto& ev : this->events) {
    if (ev == id) {
      Event aux = ev; // We need this copy to be returned
      this->events.erase(ev);
      return aux;
    }
  }

  if (id != 0)
    throw NoSuchObject(to_string(id), "Event");

  return Event();
}

/* PUBLIC */
BaseEnterprise::BaseEnterprise(const string& name,
                               const string& contact,
                               const Address& address)
{
  this->name    = name;
  this->contact = contact;
  this->address = address;
}

Enterprise::Enterprise(const string& name,
                       const string& contact,
                       const Address& address,
                       const set<Event>& events)
  : BaseEnterprise(name, contact, address)
{
  this->events = events;
}

/* GETTERS */

string
BaseEnterprise::get_name() const
{
  return this->name;
}

string
BaseEnterprise::get_contact() const
{
  return this->contact;
}

Address
BaseEnterprise::get_address() const
{
  return this->address;
}

const set<Event>&
Enterprise::get_events() const
{
  return this->events;
}

const Event&
Enterprise::get_event(unsigned id) const
{
  for (const auto& ev : this->events) {
    if (ev == id)
      return ev;
  }

  throw NoSuchObject(to_string(id), "Event");
}

/* SETTERS */
void
BaseEnterprise::set_name(const std::string& new_name)
{
  if (utl::isStrEmpty(new_name))
    throw UserInputReadingFailure(
      "Name must not be be considered an empty string");
  this->name = new_name;
}

void
BaseEnterprise::set_contact(const std::string& new_contact)
{
  if (utl::isStrEmpty(new_contact))
    throw UserInputReadingFailure(
      "Contact must not be be considered an empty string");
  this->contact = new_contact;
}

void
BaseEnterprise::set_address(const Address& new_address)
{
  this->address = new_address;
}

/* EVENT SETTERS */
void
Enterprise::event_set_max_capacity(unsigned id, unsigned new_max_capacity)
{
  Event ev = this->pop(id);
  ev.set_max_capacity(new_max_capacity);
  this->events.insert(ev);
}

void
Enterprise::event_set_name(unsigned id, const std::string& new_name)
{
  Event ev = this->pop(id);
  ev.set_name(new_name);
  this->events.insert(ev);
}

void
Enterprise::event_set_ticket_fee(unsigned id, float new_ticket_fee)
{
  Event ev = this->pop(id);
  ev.set_ticket_fee(new_ticket_fee);
  this->events.insert(ev);
}

void
Enterprise::event_set_location_name(unsigned id,
                                    const std::string& new_location_name)
{
  Event ev = this->pop(id);
  ev.set_location_name(new_location_name);
  this->events.insert(ev);
}

void
Enterprise::event_set_address(unsigned id, const Address& new_address)
{
  Event ev = this->pop(id);
  ev.set_address(new_address);
  this->events.insert(ev);
}

void
Enterprise::event_set_time(unsigned id, const Time& new_time)
{
  Event ev = this->pop(id);
  ev.set_time(new_time);
  this->events.insert(ev);
}

void
Enterprise::event_set_date(unsigned id, const Date& new_date)
{
  Event ev = this->pop(id);
  ev.set_date(new_date);
  this->events.insert(ev);
}

void
Enterprise::event_set_validity(unsigned id, bool new_is_valid)
{
  Event ev = this->pop(id);
  ev.set_validity(new_is_valid);
  this->events.insert(ev);
}

/* OTHER PUBLIC METHODS */
void
Enterprise::add_event(Event& ev)
{
  // Redundant checks, better safe than sorry
  if (ev.get_id() == 0)
    throw InvalidObject("Event", "event cannot have id 0");

  if (this->has_event(ev.get_id()))
    // If this is thrown, some really fck up shit happened
    throw ObjectAlreadyExists((to_string(ev.get_id())), "event");

  this->events.insert(ev);

  // Make its id invalid (0), in order to prevent multiple equal ids
  ev.set_invalid_id();
}

void
Enterprise::remove_event(unsigned id)
{
  this->pop(id);
}

bool
Enterprise::has_event(unsigned id) const
{
  for (const auto& ev : this->events) {
    if (ev == id)
      return true;
  }
  return false;
}

void
Enterprise::purchase_event(unsigned id, unsigned cc)
{
  Event aux = this->pop(id);
  aux.purchase(cc);
  this->events.insert(aux);
}

std::ostream&
operator<<(std::ostream& outstream, const BaseEnterprise& ent)
{
  outstream << left << setw(ENTERPRISE_OUPUT_DELIM) << "Name"
            << " : " << right << ent.name << endl
            << left << setw(ENTERPRISE_OUPUT_DELIM) << "Contact"
            << " : " << right << ent.contact << endl
            << left << setw(ENTERPRISE_OUPUT_DELIM) << "Address"
            << " : " << right << ent.address;

  return outstream;
}

std::ostream&
operator<<(std::ostream& outstream, const Enterprise& ent)
{
  outstream << (BaseEnterprise)ent << endl;
  outstream << left << setw(ENTERPRISE_OUPUT_DELIM) << "Num of Events"
            << " : " << right << ent.events.size();

  return outstream;
}

std::ofstream&
operator<<(std::ofstream& outfstream, const BaseEnterprise& ent)
{
  outfstream << ent.name << endl;
  outfstream << ent.contact << endl;
  outfstream << ent.address;
  return outfstream;
}

std::ofstream&
operator<<(std::ofstream& outfstream, const Enterprise& ent)
{
  outfstream << (BaseEnterprise)ent << endl;

  outfstream << to_string(ent.events.size()) << endl;
  for (const auto& ev : ent.events) {
    outfstream << ev << endl;
  }
  return outfstream;
}

std::ifstream&
operator>>(std::ifstream& infstream, BaseEnterprise& ent)
{
  try {
    // NAME
    getline(infstream, ent.name);

    // CONTACT
    getline(infstream, ent.contact);

    // ADDRESS
    infstream >> ent.address;
  }
  catch (std::exception& e) {
    infstream.setstate(ios::failbit);
    cerr << e.what();
  }

  return infstream;
}

std::ifstream&
operator>>(std::ifstream& infstream, Enterprise& ent)
{
  try {
    // NAME
    getline(infstream, ent.name);

    // CONTACT
    getline(infstream, ent.contact);

    // ADDRESS
    infstream >> ent.address;

    // EVENTS
    int num_events;
    infstream >> num_events;
    utl::ignore(infstream);

    Event auxEv;
    for (; num_events > 0; --num_events) {
      infstream >> auxEv;
      ent.events.insert(auxEv);
    }
  }
  catch (std::exception& e) {
    infstream.setstate(ios::failbit);
    cerr << e.what();
  }

  return infstream;
}

void
Enterprise::cin_read_enterprise(Enterprise& ent)
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

    ent.events = set<Event>();
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
