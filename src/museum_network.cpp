#include "../include/museum_network.h"

#include <iomanip>
#include <stack>

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

/* Repair Enterprises */
RepairEnterprise
MuseumNetwork::getBestRepairEnterprise(std::tuple<float, float> mcoord,
                                       float dist)
{
  stack<RepairEnterprise> temp;
  RepairEnterprise curr;

  bool found = false;
  while (!this->repair_ent.empty() && !found) {
    curr = repair_ent.top();
    if (utl::coord_dist(curr.get_coords(), mcoord) > dist) {
      temp.push(curr);
      repair_ent.pop();
    }
    else {
      found = true;
    }
  }

  while (!temp.empty()) {
    repair_ent.push(temp.top());
    temp.pop();
  }

  if (found)
    return curr;

  return RepairEnterprise();
}

std::priority_queue<RepairEnterprise>
MuseumNetwork::getRepairEnterprises() const
{
  return this->repair_ent;
}

vector<RepairEnterprise>
MuseumNetwork::getRepairEnterprisesvec() const
{
  priority_queue<RepairEnterprise> aux = this->repair_ent;
  vector<RepairEnterprise> result;
  result.reserve(aux.size());

  while (!aux.empty()) {
    result.push_back(aux.top());
    aux.pop();
  }

  return result;
}

void
MuseumNetwork::addRepairEnterprise(RepairEnterprise repair_enterprise)
{
  bool found                           = false;
  priority_queue<RepairEnterprise> aux = repair_ent;
  while (!aux.empty() && !found) {
    if (aux.top() == repair_enterprise)
      found = true;

    aux.pop();
  }

  if (found)
    throw(
      ObjectAlreadyExists(repair_enterprise.get_name(), "Repair Enteprise"));

  repair_ent.push(repair_enterprise);
}

void
MuseumNetwork::listRepairEnterprises(const vector<RepairEnterprise>& vec,
                                     const string& delim) const
{
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it;
    cout << delim;
  }

  cout << setw(MUSEUM_OUPUT_DELIM)
       << "Note: The folllowing repair enteprises are ordered by number of "
          "jobs successfully done"
       << endl;
}

void
MuseumNetwork::listRepairEnterprises(const string& delim) const
{
  this->listRepairEnterprises(getRepairEnterprisesvec(), delim);
}
void
MuseumNetwork::removeRepairEnterprise(const RepairEnterprise& repair_enterprise)
{
  bool found = false;
  priority_queue<RepairEnterprise> aux;

  while (!repair_ent.empty() && !found) {
    if (repair_enterprise == repair_ent.top())
      found = true;
    else
      aux.push(repair_ent.top());

    repair_ent.pop();
  }

  while (!aux.empty()) {
    repair_ent.push(aux.top());
    aux.pop();
  }

  if (!found)
    throw(NoSuchObject(repair_enterprise.get_name(), "Repair Enterprise"));
}

void
MuseumNetwork::removeRepairEnterprises(
  const vector<RepairEnterprise>& repair_enterprises)
{
  for (auto it = repair_enterprises.begin(); it != repair_enterprises.end();
       ++it)
    removeRepairEnterprise(*it);
}

void
MuseumNetwork::modifyRepairEnterprise(const RepairEnterprise& old_rep_enter,
                                      const RepairEnterprise& new_rep_enter)
{
  /* Check if new enteprise won't overwritte any of the existing ones */
  if (old_rep_enter != new_rep_enter) {
    bool found                           = false;
    priority_queue<RepairEnterprise> aux = repair_ent;
    while (!aux.empty() && !found) {
      if (aux.top() == new_rep_enter)
        found = true;

      aux.pop();
    }

    if (found)
      throw(ObjectAlreadyExists(new_rep_enter.get_name(), "Repair Enteprise"));
  }

  /* Find and replace old enteprise */
  removeRepairEnterprise(old_rep_enter);
  repair_ent.push(new_rep_enter);
}
void
MuseumNetwork::contactRepairEnterprise(const RepairEnterprise& rep_enter)
{
  RepairEnterprise new_enter = rep_enter;
  new_enter.set_numjobs(rep_enter.get_numjobs() + 1);
  this->modifyRepairEnterprise(rep_enter, new_enter);
}

/* Museums */

bool
MuseumNetwork::findMuseum(string museum_name, tuple<float, float> museum_coords)
{
  bool found = false;
  Museum mus(museum_name, Time(0, 0), Time(0, 0), 0, Address(), museum_coords);
  for (auto it = museums.begin(); it != museums.end(); ++it)
    if (*it == mus) {
      found = true;
      break;
    }

  return found;
}

void
MuseumNetwork::modifyMuseum(const Museum& old_museum, const Museum& new_museum)
{
  if (museums.find(old_museum) == museums.end())
    throw NoSuchObject(old_museum.get_name(), "Museum");

  /* If new museum won't replace the old one */
  if (old_museum != new_museum) {
    /* If it will override an existing museum in the network */
    if (museums.find(new_museum) != museums.end())
      throw ObjectAlreadyExists(new_museum.get_name(), "Museum");
  }

  this->museums.erase(old_museum);
  this->museums.insert(new_museum);
}

void
MuseumNetwork::removeMuseums(const set<Museum>& museums_to_delete)
{
  for (auto it = museums_to_delete.begin(); it != museums_to_delete.end(); ++it)
    removeMuseum(*it);
}

void
MuseumNetwork::removeMuseum(const Museum& museum)
{
  if (this->museums.find(museum) == museums.end())
    throw(NoSuchObject(museum.get_name(), "Museum"));

  /* Iterate through all workers and fire all of them that work in the museum to
   * be deleted */
  for (auto it = this->workers.begin(); it != this->workers.end(); ++it) {
    if (it->get_associated_museum() == museum.get_name() &&
        it->get_museum_coordinates() == museum.get_coords()) {
      StateWorker to_add = *it;
      to_add.fire();
      workers.erase(it);
      workers.insert(to_add);
    }
  }

  this->museums.erase(museum);
}

void
MuseumNetwork::listMuseums(const set<Museum>& museums_to_be_listed,
                           const string& delim) const
{
  for (const auto& museum : museums_to_be_listed) {
    cout << museum << delim;
  }
  cout << setw(MUSEUM_OUPUT_DELIM)
       << "Note: The folllowing museums are ordered by number of visits and, "
          "when tied, are ordered by alphabetical order"
       << endl;
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
  for (auto it = museums.begin(); it != museums.end(); ++it)
    if (*it == museum)
      throw ObjectAlreadyExists(museum.get_name(), "Museum");

  museums.insert(museum);
}

set<Museum>
MuseumNetwork::getMuseums() const
{
  return this->museums;
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

  for (auto it = workers.begin(); it != workers.end(); ++it)
    result.push_back(*it);

  return result;
}

void
MuseumNetwork::hireWorker(StateWorker worker, const Museum& mus)
{
  auto iter = workers.find(worker);

  if (iter == workers.end()) // If worker already registered
    throw NoSuchObject(to_string(worker.get_cc()), "Worker");

  /* Add worker as being hired */
  workers.erase(iter);
  worker.hire(mus.get_name(), mus.get_coords());
  workers.insert(worker);
}

void
MuseumNetwork::addWorker(StateWorker worker)
{
  // ta ta ta eu tive a ler isso agora ta ta
  auto iter = workers.find(worker);

  /* Search for museum of the worker */
  if (worker.ishired())
    if (!findMuseum(worker.get_associated_museum(),
                    worker.get_museum_coordinates()))
      throw NoSuchObject(worker.get_associated_museum(), "Worker's Museum");

  if (iter != workers.end()) // If worker already registered
    throw ObjectAlreadyExists(to_string(iter->get_cc()), "Worker");

  workers.insert(worker);
}

void
MuseumNetwork::listWorkers(const vector<StateWorker>& vec,
                           const string& delim) const
{
  for (auto it = vec.begin(); it != vec.end(); ++it) {
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
  for (size_t i = 0; i < workers_to_be_removed.size(); ++i)
    removeWorker(workers_to_be_removed.at(i));
}

void
MuseumNetwork::modifyWorker(const StateWorker& old_worker,
                            const StateWorker& new_worker)
{
  if (new_worker.ishired())
    if (!findMuseum(new_worker.get_associated_museum(),
                    new_worker.get_museum_coordinates()))
      throw(
        NoSuchObject(new_worker.get_associated_museum(), "Worker's Museum"));

  if (workers.find(old_worker) == workers.end())
    throw NoSuchObject(old_worker.get_name(), "Worker");

  /* If new_worker won't replace old_worker */
  if (old_worker != new_worker)
    if (workers.find(new_worker) !=
        workers.end()) // If new_worker will override an existing worker
      throw ObjectAlreadyExists(new_worker.get_name(), "Worker");

  workers.erase(old_worker);
  workers.insert(new_worker);
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
  set<Museum> set_museums;

  input_stream >> museum_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < museum_cnt; ++i) {
    Museum museum;
    input_stream >> museum;
    if (input_stream.fail())
      throw FileReadingFailed(museum_file_name);
    set_museums.insert(museum);
    utl::ignore(input_stream);
  }

  this->museums = set_museums;
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
  HashTabStateWorker aux;

  input_stream >> worker_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < worker_cnt; ++i) {
    StateWorker worker;
    input_stream >> worker;

    sucess = (aux.insert(worker)).second;

    if (input_stream.fail() || !sucess)
      throw FileReadingFailed(worker_file_name);
    utl::ignore(input_stream);
  }

  workers = aux;
}

void
MuseumNetwork::importRepairEnterprises(
  const std::string& repair_enterprise_file_name)
{
  ifstream input_stream(repair_enterprise_file_name);
  int repair_cnt;
  priority_queue<RepairEnterprise> pq_repair;

  input_stream >> repair_cnt;
  utl::ignore(input_stream);
  for (int i = 0; i < repair_cnt; ++i) {
    RepairEnterprise repair;
    input_stream >> repair;
    if (input_stream.fail())
      throw FileReadingFailed(repair_enterprise_file_name);
    pq_repair.push(repair);
    utl::ignore(input_stream);
  }

  this->repair_ent = pq_repair;
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

  output_stream << "" << this->museums.size() << endl;
  for (const auto& museum : this->museums) {
    output_stream << museum << endl;
  }
}

void
MuseumNetwork::exportEnterprises(const std::string& enterprises_file_name) const
{
  ofstream output_stream(enterprises_file_name);

  unsigned int enterprises_cnt = this->enterprises.size();
  output_stream << "" << enterprises_cnt << endl;

  for (size_t i = 0; i < enterprises_cnt; ++i)
    output_stream << enterprises.at(i);
}

void
MuseumNetwork::exportWorkers(const std::string& worker_file_name) const
{
  ofstream output_stream(worker_file_name);

  unsigned int worker_cnt = this->workers.size();
  output_stream << "" << worker_cnt << endl;
  for (auto it = workers.begin(); it != workers.end(); ++it)
    output_stream << *it << endl;
}

void
MuseumNetwork::exportRepairEnterprises(
  const std::string& repair_enterprise_file_name) const
{
  ofstream output_stream(repair_enterprise_file_name);
  priority_queue<RepairEnterprise> aux = this->repair_ent;

  output_stream << "" << aux.size() << endl;
  while (!aux.empty()) {
    output_stream << aux.top() << endl;
    aux.pop();
  }
}

void
MuseumNetwork::exportFiles(const string& cards_file_name,
                           const string& museum_file_name,
                           const string& enterprise_file_name,
                           const string& repair_enterprise_file_name,
                           const string& worker_file_name,
                           const std::string& config_file_name) const
{
  ofstream output_stream(config_file_name);
  output_stream << "cards_file_name: " << cards_file_name << endl;
  output_stream << "museum_file_name: " << museum_file_name << endl;
  output_stream << "enterprise_file_name: " << enterprise_file_name << endl;
  output_stream << "repair_enterprise_file_name: "
                << repair_enterprise_file_name << endl;
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
  this->exportRepairEnterprises(repair_enterprise_file_name);
  this->exportWorkers(worker_file_name);
}

void
MuseumNetwork::importFiles(const string& network_file_name)
{
  ifstream input_stream(network_file_name);
  string museum_file_name, enterprise_file_name, cards_file_name,
    repair_enterprise_file_name, worker_file_name;
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
  input_stream >> repair_enterprise_file_name;
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
  if (!utl::file_exists(repair_enterprise_file_name))
    throw FileNotFound(repair_enterprise_file_name);

  this->importCards(cards_file_name);
  this->importMuseums(museum_file_name);
  this->importEnterprises(enterprise_file_name);
  this->importRepairEnterprises(repair_enterprise_file_name);
  this->importWorkers(worker_file_name);
}
