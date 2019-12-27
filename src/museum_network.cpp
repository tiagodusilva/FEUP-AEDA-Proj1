#include "../include/museum_network.h"

#include <iomanip>

using namespace std;

/* Cards */

void
MuseumNetwork::addCard(Card* card)
{
  size_t i;
  for (i = 0; i < this->cards.size(); ++i) {
    if (*card == *(this->cards.at(i)))
      throw ObjectAlreadyExists(to_string(card->get_cc()), "Card");
  }
  this->cards.push_back(card);
}

void
MuseumNetwork::removeCard(const Card* card)
{
  vector<Card*>::iterator iter;
  iter = (find_if(this->cards.begin(), this->cards.end(), [&card](Card* lhs) {
    return (*lhs == *card);
  }));

  if (iter != this->cards.end()) { // If the card is found
    delete (*iter);
    cards.erase(iter);
  }
  else
    throw NoSuchObject(to_string(card->get_cc()), "Card");
}

void
MuseumNetwork::removeCards(const std::vector<Card*>& cards_to_be_removed)
{
  /* Given a vector of pointers to cards, remove all of the cards in the network
  are present in the given vector. */

  size_t i;
  for (i = 0; i < cards_to_be_removed.size(); ++i) {
    removeCard(cards_to_be_removed.at(i));
  }
}

void
MuseumNetwork::listCards(const std::vector<Card*>& cards_to_be_listed,
                         const string& delim) const
{
  size_t i;
  for (i = 0; i < cards_to_be_listed.size(); ++i) {
    cout << *(cards_to_be_listed.at(i));
    cout << delim;
  }
}

void
MuseumNetwork::listCards(const std::string& delim) const
{
  listCards(this->getCards(), delim);
}

void
MuseumNetwork::modifyMuseum(const Museum& old_museum, const Museum& new_museum)
{
  vector<Museum>::iterator iter;

  if (old_museum !=
      new_museum) { // if the new_museum won't replace the old_museum
    iter = find(museums.begin(), museums.end(), new_museum);
    if (iter !=
        museums.end()) // check if the new_museum won't overwritte any museum
      throw(ObjectAlreadyExists(new_museum.get_name(), "Museum"));
  }

  iter = find(museums.begin(), museums.end(), old_museum);

  if (iter == museums.end())
    throw NoSuchObject(old_museum.get_name(), "Museum");

  *iter = new_museum;
}

float
MuseumNetwork::getDiscount(const unsigned int card_type) const
{
  return (this->discount[card_type]);
}

float
MuseumNetwork::getCost(const unsigned int card_type) const
{
  return (this->cost[card_type]);
}

/* Enterprises */

void
MuseumNetwork::removeEnterprises(
  std::vector<Enterprise>& enterprises_to_be_removed)
{
  /* Given a vector of enterprises, remove all of the enterprises in the network
  are present in the given vector. */

  size_t i;
  for (i = 0; i < enterprises_to_be_removed.size(); ++i) {
    removeEnterprise(enterprises_to_be_removed.at(i));
  }
}

void
MuseumNetwork::removeEnterprise(const Enterprise& enterprise)
{
  vector<Enterprise>::iterator iter;
  iter =
    (find_if(this->enterprises.begin(),
             this->enterprises.end(),
             [&enterprise](Enterprise lhs) { return (lhs == enterprise); }));

  if (iter != this->enterprises.end()) // If the museum is found
    enterprises.erase(iter);
  else
    throw NoSuchObject(enterprise.get_name(), "Enterprise");
}
void
MuseumNetwork::listEnterprises(
  const std::vector<Enterprise>& enterprises_to_be_listed,
  const string& delim) const
{
  for (const auto& enterprise : enterprises_to_be_listed)
    cout << enterprise << delim;
}

void
MuseumNetwork::listEnterprises(const string& delim) const
{
  this->listEnterprises(this->getEnterprises(), delim);
}

void
MuseumNetwork::modifyEnterprise(const Enterprise& old_enterprise,
                                const Enterprise& new_enterprise)
{
  vector<Enterprise>::iterator iter;

  if (old_enterprise !=
      new_enterprise) { // if the new_enterprise won't replace the old_museum
    iter = find(enterprises.begin(), enterprises.end(), new_enterprise);
    if (iter !=
        enterprises
          .end()) // check if the new_enterprise won't overwritte any museum
      throw(ObjectAlreadyExists(new_enterprise.get_name(), "Enterprise"));
  }

  iter = find(enterprises.begin(), enterprises.end(), old_enterprise);

  if (iter == enterprises.end())
    throw NoSuchObject(old_enterprise.get_name(), "Enterprise");

  *iter = new_enterprise;
}

void
MuseumNetwork::addEnterprise(Enterprise enterprise)
{
  for (const auto& ent : this->enterprises) {
    if (enterprise == ent)
      throw ObjectAlreadyExists(ent.get_name(), "Enterprise");
  }

  this->enterprises.push_back(enterprise);
}

/* Museums */

void
MuseumNetwork::removeMuseums(std::vector<Museum>& museums_to_be_removed)
{
  /* Given a vector of museums, remove all of the museums in the network are
  present in the given vector. */

  size_t i;
  for (i = 0; i < museums_to_be_removed.size(); ++i) {
    removeMuseum(museums_to_be_removed.at(i));
  }
}

void
MuseumNetwork::removeMuseum(const Museum& museum)
{
  vector<Museum>::iterator iter;
  iter =
    (find_if(this->museums.begin(), this->museums.end(), [&museum](Museum lhs) {
      return (lhs == museum);
    }));

  if (iter != this->museums.end()) // If the museum is found
    museums.erase(iter);
  else
    throw NoSuchObject(museum.get_name(), "Museum");
}

void
MuseumNetwork::listMuseums(const std::vector<Museum>& museums_to_be_listed,
                           const string& delim) const
{
  size_t i;
  for (i = 0; i < museums_to_be_listed.size(); ++i) {
    cout << museums_to_be_listed.at(i);
    cout << delim;
  }
  cout << setw(MUSEUM_OUPUT_DELIM) << "Note: Museum fees are free for members\n"
       << endl;
}

void
MuseumNetwork::listMuseums(const string& delim) const
{
  this->listMuseums(this->getMuseums(), delim);
}

void
MuseumNetwork::addMuseum(Museum museum)
{
  size_t i;
  for (i = 0; i < this->museums.size(); ++i) {
    if (museum == this->museums.at(i))
      throw ObjectAlreadyExists(museum.get_name(), "Museum");
  }
  this->museums.push_back(museum);
}

/* Events */

void
MuseumNetwork::listEvents(const std::vector<Event>& events_to_be_listed,
                          const string& delim) const
{
  size_t i;
  for (i = 0; i < events_to_be_listed.size(); ++i) {
    cout << events_to_be_listed.at(i);
    cout << delim;
  }
}
void
MuseumNetwork::listEvents(const string& delim) const
{
  this->listEvents(getEvents(), delim);
}

void
MuseumNetwork::listEvents(const std::vector<Event>& events_to_be_listed,
                          unsigned card_type,
                          const string& delim) const
{
  size_t i;
  for (i = 0; i < events_to_be_listed.size(); ++i) {
    events_to_be_listed.at(i).print_with_discount(cout, getDiscount(card_type));
    cout << delim;
  }
}
void
MuseumNetwork::listEvents(unsigned card_type, const string& delim) const
{
  this->listEvents(getEvents(), card_type, delim);
}

vector<Event>
MuseumNetwork::getEvents() const
{
  size_t i;
  int number_events(0);
  /* get size of the vector so that it doesn't have to realocate memory */
  for (i = 0; i < enterprises.size(); ++i) {
    number_events += 1; // enterprises.at(i).get_events().size();
  }

  vector<Event> events;
  events.reserve(number_events + 1); // Allocate vector with number of events

  for (auto& ent : this->enterprises)  // Iterate through enterpises
    for (auto& x : ent.get_events()) { // Iterate through set of events
      events.push_back(x);
    }

  return events;
}

void
MuseumNetwork::addEvent(const Enterprise& enterprise, Event& event)
{
  /*vector<Enterprise>::iterator iter=find(enterprises.begin(),
     enterprises.end(),
                  [&event](const Enterprise &enter){
     return(enter.has_event(event.get_id())); });*/

  for (auto& ent : enterprises) {
    if (ent.has_event(
          event.get_id())) { // Verify if the event is already in the network
      throw InvalidObject("Event",
                          "Event with id " + to_string(event.get_id()) +
                            " is already in the Network");
    }
  }

  vector<Enterprise>::iterator iter =
    find(enterprises.begin(), enterprises.end(), enterprise);
  (*iter).add_event(event);
}

void
MuseumNetwork::removeEvents(std::vector<Event>& events_to_be_removed)
{
  /* Given a vector of events, remove all of the events in the network which are
  present in the given vector. */

  int i;
  for (i = 0; i < events_to_be_removed.size(); ++i) {
    vector<Enterprise>::iterator iter;
    Event event = events_to_be_removed.at(i);

    /* Search for enterprise which holds the event */
    iter = find_if(enterprises.begin(),
                   enterprises.end(),
                   [&event](const Enterprise& enterprise) {
                     return (enterprise.has_event(event.get_id()));
                   });

    if (iter == enterprises.end())
      throw NoSuchObject(to_string(event.get_id()), "Event");

    removeEvent(event, *iter);
  }
}

void
MuseumNetwork::removeEvent(const Event& event, Enterprise& enterprise)
{
  enterprise.remove_event(event.get_id());
}

void
MuseumNetwork::modifyEvent(const Event& old_event, const Event& new_event)
{
  bool found = false;
  vector<Enterprise>::iterator iter;
  iter = find_if(
    enterprises.begin(), enterprises.end(), [&old_event](Enterprise enter) {
      return (enter.has_event(old_event.get_id()));
    });

  if (iter == enterprises.end()) // if event isn't on any enterprise
    throw NoSuchObject(to_string(old_event.get_id()), "Event");

  /* Modify event */
  unsigned old_id = old_event.get_id();
  (*iter).event_set_name(old_id, new_event.get_name());
  (*iter).event_set_date(old_id, new_event.get_date());
  (*iter).event_set_time(old_id, new_event.get_time());
  (*iter).event_set_address(old_id, new_event.get_address());
  (*iter).event_set_ticket_fee(old_id, new_event.get_fee());
  (*iter).event_set_max_capacity(old_id, new_event.get_max_capacity());
  (*iter).event_set_location_name(old_id, new_event.get_location_name());

  if (new_event.get_validity() !=
      old_event.get_validity()) { // Check if validity needs to be modified{
    utl::pauseConsole();
    (*iter).event_set_validity(old_id, new_event.get_validity());
  }
}

void
MuseumNetwork::purchaseEvent(const unsigned cc, Event event)
{
  int i;
  for (i = 0; i < this->enterprises.size(); ++i) {
    if (enterprises.at(i).has_event(event.get_id())) {
      enterprises.at(i).purchase_event(event.get_id(), cc);
      return;
    }
  }
  throw NoSuchObject(to_string(event.get_id()), "Event");
}


/* Worker */

vector<StateWorker>
MuseumNetwork::getWorkers() const
{
	vector<StateWorker> result;
	result.reserve(workers.size());

	for(auto it=workers.begin(); it != workers.end(); ++it)
		result.push_back(*it);

	return result;
}

void
MuseumNetwork::addWorker(StateWorker worker)
{
  bool sucess = (this->workers.insert(worker)).second;

  if (!sucess)
	  throw(ObjectAlreadyExists(to_string(worker.get_cc()), "Worker"));
}

void
MuseumNetwork::listWorkers(const vector<StateWorker> &vec, const string& delim) const
{
	for(auto it=vec.begin(); it != vec.end(); ++it)
	{
		cout << (*it);
		cout << delim;
	}
}

void
MuseumNetwork::listWorkers(const string& delim) const
{
	this->listWorkers(getWorkers(), delim);
}

void
MuseumNetwork::removeWorker(const StateWorker& worker_to_be_removed)
{
	this->workers.erase(worker_to_be_removed);
}

void
MuseumNetwork::removeWorkers(const vector<StateWorker>& workers_to_be_removed)
{
	for(size_t i=0; i<workers_to_be_removed.size(); ++i)
		removeWorker(workers_to_be_removed.at(i));
}

/* File Methods */

void
MuseumNetwork::importCards(const std::string& cards_file_name)
{
  ifstream input_stream(cards_file_name);
  int card_cnt;
  vector<Card*> vec_cards;

  input_stream >> card_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < card_cnt; ++i) {
    Card* card;
    input_stream >> card;
    if (input_stream.fail())
      throw FileReadingFailed(cards_file_name);
    vec_cards.push_back(card);
  }

  this->cards = vec_cards;
}

void
MuseumNetwork::importMuseums(const std::string& museum_file_name)
{
  ifstream input_stream(museum_file_name);
  int museum_cnt;
  vector<Museum> vec_museums;

  input_stream >> museum_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < museum_cnt; ++i) {
    Museum museum;
    input_stream >> museum;
    if (input_stream.fail())
      throw FileReadingFailed(museum_file_name);
    vec_museums.push_back(museum);
  }

  this->museums = vec_museums;
}

void
MuseumNetwork::importEnterprises(const std::string& enterprise_file_name)
{
  ifstream input_stream(enterprise_file_name);
  int enterprise_cnt;
  vector<Enterprise> vec_enterprises;

  input_stream >> enterprise_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < enterprise_cnt; ++i) {
    Enterprise enterprise;
    input_stream >> enterprise;
    if (input_stream.fail())
      throw FileReadingFailed(enterprise_file_name);
    vec_enterprises.push_back(enterprise);
  }

  this->enterprises = vec_enterprises;
}


void
MuseumNetwork::importWorkers(const std::string& worker_file_name)
{
  ifstream input_stream(worker_file_name);
  bool sucess;
  unsigned worker_cnt;

  input_stream >> worker_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < worker_cnt; ++i) {
    StateWorker worker;
    input_stream >> worker;

	sucess = (workers.insert(worker)).second;

    if (input_stream.fail() || !sucess)
	{
	  workers.clear();
      throw FileReadingFailed(worker_file_name);
	}
    utl::ignore(input_stream);
  }
}

void
MuseumNetwork::exportCards(const std::string& cards_file_name) const
{
  ofstream output_stream(cards_file_name);

  unsigned int card_cnt = this->cards.size();
  output_stream << "" << card_cnt << endl;
  for (size_t i = 0; i < card_cnt; ++i)
    output_stream << *(cards.at(i)) << endl;
}

void
MuseumNetwork::exportMuseums(const std::string& museum_file_name) const
{
  ofstream output_stream(museum_file_name);

  unsigned int museums_cnt = this->museums.size();
  output_stream << "" << museums_cnt << endl;
  for (size_t i = 0; i < museums_cnt; ++i)
    output_stream << museums.at(i) << endl;
}

void
MuseumNetwork::exportEnterprises(const std::string& enterprises_file_name) const
{
  ofstream output_stream(enterprises_file_name);

  unsigned int enterprises_cnt = this->enterprises.size();
  output_stream << "" << enterprises_cnt << endl;

  for (size_t i = 0; i < enterprises_cnt; ++i)
    output_stream << enterprises.at(i) << endl;
}

void
MuseumNetwork::exportWorkers(const std::string& worker_file_name) const
{
  ofstream output_stream(worker_file_name);

  unsigned int worker_cnt = this->workers.size();
  output_stream << "" << worker_cnt << endl;
  for (auto it=workers.begin(); it != workers.end(); ++it)
    output_stream << *it << endl;
}

void
MuseumNetwork::exportFiles(const string& cards_file_name,
                           const string& museum_file_name,
                           const string& enterprise_file_name,
						   const string& worker_file_name,
						   const string& config_file_name) const
{
  ofstream output_stream(config_file_name);
  output_stream << "cards_file_name: " << cards_file_name << endl;
  output_stream << "museum_file_name: " << museum_file_name << endl;
  output_stream << "enterprise_file_name: " << enterprise_file_name << endl;
  output_stream << "worker_file_name: " << worker_file_name << endl;
  output_stream << "individual::cost: " << cost[0] << endl;
  output_stream << "individual::discount: " << discount[0] << endl;
  output_stream << "silver::cost: " << cost[1] << endl;
  output_stream << "silver::discount: " << discount[1] << endl;
  output_stream << "uni::cost: " << cost[2] << endl;
  output_stream << "uni::discount: " << discount[2] << endl;

  this->exportCards(cards_file_name);
  this->exportMuseums(museum_file_name);
  this->exportEnterprises(enterprise_file_name);
  this->exportWorkers(worker_file_name);
}

void
MuseumNetwork::importFiles(const string& network_file_name)
{
  ifstream input_stream(network_file_name);
  string museum_file_name, enterprise_file_name, cards_file_name, worker_file_name;
  string temp_str;

  input_stream >> temp_str;
  input_stream >> cards_file_name;
  utl::ignore(input_stream);

  input_stream >> temp_str;
  input_stream >> museum_file_name;
  utl::ignore(input_stream);
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> enterprise_file_name;
  utl::ignore(input_stream);
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> worker_file_name;
  utl::ignore(input_stream);
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> this->cost[0];
  utl::ignore(input_stream); // individual cost
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> this->discount[0];
  utl::ignore(input_stream); // individual discount
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> this->cost[1];
  utl::ignore(input_stream); // silver cost
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> this->discount[1];
  utl::ignore(input_stream); // silver discount
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> this->cost[2];
  utl::ignore(input_stream); // uni cost
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  input_stream >> temp_str;
  input_stream >> this->discount[2];
  utl::ignore(input_stream); // uni discount
  if (input_stream.fail())
    throw FileReadingFailed(network_file_name);

  if (!utl::file_exists(network_file_name))
    throw FileNotFound(network_file_name);
  if (!utl::file_exists(museum_file_name))
    throw FileNotFound(museum_file_name);
  if (!utl::file_exists(enterprise_file_name))
    throw FileNotFound(enterprise_file_name);
  if (!utl::file_exists(cards_file_name))
    throw FileNotFound(cards_file_name);

  this->importCards(cards_file_name);
  this->importMuseums(museum_file_name);
  this->importEnterprises(enterprise_file_name);
  this->importWorkers(worker_file_name);
}
