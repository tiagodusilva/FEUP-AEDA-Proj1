#include <iomanip>

#include "../include/interfaces.h"
#include "../include/utilities.h"

using namespace std;

/*
 * ADMIN INTERFACE
 */
AdminInterface::AdminInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	cout << "Login as the Admin!" << endl;
	utl::pauseConsole();
}

void
AdminInterface::show()
{
	/* Filters with museums are different from other filters.
	 * This is due to the fact that we need to take into account the set proprieties when filtering
	 * (we must filter eveything at once).
	 * As such, all of the museum filters are packed in one single function (called in a menu).
	 * The design of the menus didn't consider this, and as such there is some repetition of code
	*/

	/* Sort Cards */
	MenuSelectFilter<vector<Card*>> CardsSortName("By name",
			[](vector<Card*> &vec){
				sort(vec.begin(), vec.end(), [](Card* c1, Card* c2){ return c1->get_name() < c2->get_name(); }); });
	MenuSelectFilter<vector<Card*>> CardsSortCC("By CC",
			[](vector<Card*> &vec){
				sort(vec.begin(), vec.end(), [](Card* c1, Card* c2){ return c1->get_cc() < c2->get_cc(); }); });
	MenuSelectFilter<vector<Card*>> CardsSortBirthDate("By Birth Date",
			[](vector<Card*> &vec){
				sort(vec.begin(), vec.end(), [](Card* c1, Card* c2){ return c1->get_birth_date() < c2->get_birth_date(); }); });

	MenuOptionsFilter<vector<Card*>> CardsSort("Sort currently selected cards", {&CardsSortName, &CardsSortCC, &CardsSortBirthDate},
			[](vector<Card*>) {}, [](){ return vector<Card*>(); }, true);


	/* Filter Cards by validity*/
	MenuSelectFilter<vector<Card*>> CardsValidity("By validity", flt::FilterCardByValidity);
	MenuSelectFilter<vector<Card*>> CardsInvalidity("By invalidity", flt::FilterCardByInvalidity);
	vector<MenuFilter<vector<Card*>>*> validityOpt = {&CardsValidity, &CardsInvalidity};


	/* Filter Cards */
	MenuSelectFilter<vector<Card*>> CardsName("By name", flt::FilterCardByName);
	MenuOptionsFilter<vector<Card*>> CardsValidityOptions("Filter by validity", validityOpt, [](vector<Card*>&){},
			[](){return(vector<Card*>());}, true);
	MenuSelectFilter<vector<Card*>> CardsSelect("List current selected cards",
			[this](vector<Card*>&vec) { this->museum_network.listCards(vec); });


	/* Sort Events */
	MenuSelectFilter<vector<Event>> EventsSortName("By name", flt::SortByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSortFee("By Fee",
			[](vector<Event> &vec){
				sort(vec.begin(), vec.end(), [](Event c1, Event c2){ return c1.get_fee() < c2.get_fee(); }); });
	MenuSelectFilter<vector<Event>> EventsSortCurrCapacity("By Current Capacity",
			[](vector<Event> &vec){
				sort(vec.begin(), vec.end(), [](Event c1, Event c2){ return c1.get_current_capacity() < c2.get_current_capacity(); }); });
	MenuOptionsFilter<vector<Event>> EventSort("Sort currently selected Events",
			{&EventsSortName, &EventsSortFee, &EventsSortCurrCapacity},
			[](vector<Event>) {}, [](){ return vector<Event>(); }, true);


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt,
			[](vector<Event>&){},
			[](){return(vector<Event>());}, true);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsLocationName("Filter by location name", flt::FilterEventByLocationName);
	MenuSelectFilter<vector<Event>> EventsId("Select by id", flt::FilterEventById);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeFrame);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });


	/* Sort Enterprises */
	MenuSelectFilter<vector<Enterprise>> EnterprisesSortName("By name", flt::SortByName<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterprisesSortNumEvents("By number of Events",
			[](vector<Enterprise> &vec){
				sort(vec.begin(), vec.end(), [](Enterprise c1, Enterprise c2){
					return c1.get_events().size() < c2.get_events().size();
				});
			});
	MenuOptionsFilter<vector<Enterprise>> EnterpriseSort("Sort currently selected Enterprises",
			{&EnterprisesSortName, &EnterprisesSortNumEvents},
			[](vector<Enterprise>) {}, [](){ return vector<Enterprise>(); }, true);


	/* Filter Enterprises */
	MenuSelectFilter<vector<Enterprise>> EnterpriseLocation("Filter by location", flt::FilterByLocationCin<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseName("Filter by name", flt::FilterByName<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseEvent("Filter by event ID", flt::FilterByEventID<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseSelected("List currently selected enterprises",
			[this](vector<Enterprise>&vec) { this->museum_network.listEnterprises(vec); });


	/* Sort RepairEnterprises */
	MenuSelectFilter<vector<RepairEnterprise>> RepEnterprisesSortName("By name", flt::SortByName<RepairEnterprise>);
	MenuSelectFilter<vector<RepairEnterprise>> RepEnterprisesSortNumJobs("By number of jobs done",
			[](vector<RepairEnterprise> &vec){
				sort(vec.begin(), vec.end(), [](RepairEnterprise c1, RepairEnterprise c2){
					return c1.get_numjobs() < c2.get_numjobs();
				});
			});
	MenuOptionsFilter<vector<RepairEnterprise>> RepEnterpriseSort("Sort currently selected RepairEnterprises",
			{&RepEnterprisesSortName, &RepEnterprisesSortNumJobs},
			[](vector<RepairEnterprise>) {}, [](){ return vector<RepairEnterprise>(); }, true);


	/* Filter RepairEnterprises */
	MenuSelectFilter<vector<RepairEnterprise>> RepEnterpriseLocation("Filter by location", flt::FilterByLocationCin<RepairEnterprise>);
	MenuSelectFilter<vector<RepairEnterprise>> RepEnterpriseName("Filter by name", flt::FilterByName<RepairEnterprise>);
	MenuSelectFilter<vector<RepairEnterprise>> RepEnterpriseSelected("List currently selected repair-enterprises",
			[this](vector<RepairEnterprise>&vec) { this->museum_network.listRepairEnterprises(vec); });


	/* Sort Workers */
	MenuSelectFilter<vector<StateWorker>> WorkersSortName("By name", flt::SortByName<StateWorker>);
	MenuSelectFilter<vector<StateWorker>> WorkersSortCC("By CC",
			[](vector<StateWorker> &vec){
				sort(vec.begin(), vec.end(), [](StateWorker c1, StateWorker c2){
					return c1.get_cc() < c2.get_cc();
				});
			});
	MenuOptionsFilter<vector<StateWorker>> WorkerSort("Sort currently selected Workers",
			{&WorkersSortName, &WorkersSortCC},
			[](vector<StateWorker>) {}, [](){ return vector<StateWorker>(); }, true);


	/* Filter Workers by employment*/
	MenuSelectFilter<vector<StateWorker>> WorkersEmployed("Select currently employed workers", flt::FilterWorkersByEmployment);
	MenuSelectFilter<vector<StateWorker>> WorkersNotEmployed("Select workers which aren't currently being employed by the network",
			flt::FilterWorkersByNonEmployment);
	vector<MenuFilter<vector<StateWorker>>*> employmentOpt = {&WorkersEmployed, &WorkersNotEmployed};

	/* Filter Workers */
	MenuSelectFilter<vector<StateWorker>> WorkerName("Filter by name", flt::FilterByName<StateWorker>);
	MenuOptionsFilter<vector<StateWorker>> WorkerHired("Filter by employment status", employmentOpt, [](vector<StateWorker>&){},
			[](){ return(vector<StateWorker>()); }, true);
	MenuSelectFilter<vector<StateWorker>> WorkerSelected("List currently selected workers",
			[this](const vector<StateWorker>&vec) { this->museum_network.listWorkers(vec); });


	/* List Cards */
	vector<MenuFilter<vector<Card*>>*> listCardsOpt = {&CardsSelect, &CardsSort, &CardsName, &CardsValidityOptions};
	MenuOptionsFilter<vector<Card*>> listCards("List Cards", listCardsOpt,
			[this](vector<Card*>&vec){ return vector<Card*>(); },
			[this](){ return(this->museum_network.getCards());}, // Initialize vector with all cards of the network
			false, {0, 1});


	/* List Enterprises */
	vector<MenuFilter<vector<Enterprise>>*> listEnterprisesOpt =
	{&EnterpriseSelected, &EnterpriseSort, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName};

	MenuOptionsFilter<vector<Enterprise>> listEnterprises("List Enterprises", listEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return vector<Enterprise>(); },
			[this](){ return(this->museum_network.getEnterprises());}, // Initialize vector with all enterprises of the network
			false, {0, 1});

	/* List Repair Enterprises */
	vector<MenuFilter<vector<RepairEnterprise>>*> listRepairEnterprisesOpt =
		{&RepEnterpriseSelected, &RepEnterpriseSort, &RepEnterpriseLocation, &RepEnterpriseName};
	MenuOptionsFilter<vector<RepairEnterprise>> listRepairEnterprises("List Repair Enterprises", listRepairEnterprisesOpt,
			[this](vector<RepairEnterprise>&vec){ return vector<RepairEnterprise>(); },
			[this](){ return(this->museum_network.getRepairEnterprisesvec());}, // Initialize vector with all enterprises of the network
			false, {0, 1});

	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt=
		{&EventsSelected, &EventSort, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsTimeframe, &EventsId};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());}, // Initialize vector with all events of the network
			false, {0, 1});


	/* List Museums */
	MenuSelect listMuseums("List Museums", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitMuseum("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listMuseums("List Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuOptions listMenu("List Museums", {&listMuseums, &commitMuseum, &FilterName, &FilterAddress});
		listMenu.show();
	});


	/* List Workers */
	vector<MenuFilter<vector<StateWorker>>*> listWorkersOpt = {&WorkerSelected, &WorkerSort, &WorkerName, &WorkerHired};
	MenuOptionsFilter<vector<StateWorker>> listWorkers("List Workers", listWorkersOpt,
			[this](vector<StateWorker>&vec){ return vector<StateWorker>(); },
			[this](){ return(this->museum_network.getWorkers());}, // Initialize vector with all museums of the network
			false, {0, 1});

	/* List Network Options */
	MenuOptions list_network("List Network Options",
			std::vector<Menu*>{&listEvents, &listMuseums, &listEnterprises, &listRepairEnterprises, &listCards, &listWorkers});


	/* Remove Events */
	MenuSelectFilter<vector<Event>> removeEventsSelected("Remove selected events",
		[this](vector<Event> &vec){
			if(vec.size() == this->museum_network.getEvents().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeEvents(vec);
				cout <<	"Event(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Event>>*> removeEventsOpt = listEventsOpt;
	removeEventsOpt.push_back(&removeEventsSelected);
	MenuOptionsFilter<vector<Event>> removeEvents("Remove Events", removeEventsOpt,
			[this](vector<Event>&vec){ return; },
			[this](){ return(this->museum_network.getEvents());}, // Initialize vector with all events of the network
			false, {0, 1});


	/* Remove Museum */
	MenuSelect removeMuseums("Remove Museums", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitMuseum("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listMuseum("List Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuSelect removeMuseum("Remove selected museums", [this, &mus] {
				if (mus.size() == this->museum_network.getMuseums().size())
					cout << "Warning! You will remove all of them!!\n";

				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.removeMuseums(mus);
					cout <<	"Museum(s) removed!"; utl::pauseConsole();
					mus.erase(mus.begin(), mus.end());
				}
				else
					cout << "Operation aborted" << endl;

		});

		MenuOptions listMenu("List Museums", {&listMuseum, &commitMuseum, &FilterName, &FilterAddress, &removeMuseum});
		listMenu.show();
	});


	/* Remove Enterprises */
	MenuSelectFilter<vector<Enterprise>> removeEnterprisesSelected("Remove selected enterprises",
		[this](vector<Enterprise> &vec){
			if(vec.size() == this->museum_network.getEnterprises().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeEnterprises(vec);
				cout <<	"Enterprise(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Enterprise>>*> removeEnterprisesOpt =
		{&EnterpriseSelected, &EnterpriseSort, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName, &removeEnterprisesSelected};
	MenuOptionsFilter<vector<Enterprise>> removeEnterprises("Remove Enterprises", removeEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return; },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0, 1});


	/* Remove Repair Enterprises */
	MenuSelectFilter<vector<RepairEnterprise>> removeRepEnterprisesSelected("Remove selected repair-enterprises",
		[this](vector<RepairEnterprise> &vec){
			if(vec.size() == this->museum_network.getRepairEnterprisesvec().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeRepairEnterprises(vec);
				cout <<	"Enterprise(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<RepairEnterprise>>*> removeRepairEnterprisesOpt =
		{&RepEnterpriseSelected, &RepEnterpriseSort, &RepEnterpriseLocation, &RepEnterpriseName, &removeRepEnterprisesSelected};
	MenuOptionsFilter<vector<RepairEnterprise>> removeRepairEnterprises("Remove Repair-Enterprises", removeRepairEnterprisesOpt,
			[this](vector<RepairEnterprise>&vec){ return; },
			[this](){ return(this->museum_network.getRepairEnterprisesvec());},
			false, {0, 1});


	/* Remove Cards */
	MenuSelectFilter<vector<Card*>> removeCardsSelected("Remove all selected cards",
		[this](vector<Card*> &vec){
			if(vec.size() == this->museum_network.getCards().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeCards(vec);
				cout <<	"Card(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Card*>>*> removeCardsOpt =
		{&CardsSelect, &CardsSort, &CardsName, &CardsValidity, &removeCardsSelected};
	MenuOptionsFilter<vector<Card*>> removeCards("Remove Cards", removeCardsOpt,
			[this](vector<Card*>&vec){ return; },
			[this](){ return(this->museum_network.getCards());},
			false, {0, 1});


	/* Remove Workers */
	MenuSelectFilter<vector<StateWorker>> removeWorkersSelected("Remove selected workers",
		[this](vector<StateWorker> &vec){
			if(vec.size() == this->museum_network.getWorkers().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeWorkers(vec);
				cout <<	"Worker(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<StateWorker>>*> removeWorkersOpt =
		{&WorkerSelected, &WorkerSort, &WorkerName, &WorkerHired, &removeWorkersSelected};
	MenuOptionsFilter<vector<StateWorker>> removeWorkers("Remove Workers", removeWorkersOpt,
			[this](vector<StateWorker>&vec){ return; },
			[this](){ return(this->museum_network.getWorkers());},
			false, {0, 1});


	/* Remove Network Options */
	MenuOptions remove_network("Network Remove Options",
			std::vector<Menu*>{&removeEvents, &removeMuseums, &removeEnterprises, &removeRepairEnterprises, &removeCards, &removeWorkers});


	/* Add User */
	MenuSelect addUser("Add a new account", [this](){
				Card *card;
				Card::cin_read_card(card);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid card formatting\n"));
				}
				cout << "This operation will have a cost of " << fixed << setprecision(2) << this->museum_network.getCost(card->get_type()) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addCard(card);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Museum */
	MenuSelect addMuseum("Add a new museum", [this](){
				Museum museum;
				Museum::cin_read_museum(museum);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid museum formatting\n"));
				}
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addMuseum(museum);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Enterprise */
	MenuSelect addEnterpirse("Add a new enterprise", [this](){
				Enterprise enterprise;
				Enterprise::cin_read_enterprise(enterprise);
				if (cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid enterprise formatting\n"));
				}

				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));

				if (a=='y' || a=='Y')
					this->museum_network.addEnterprise(enterprise);
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Repair Enterprise */
	MenuSelect addRepairEnterpirse("Add a new repair-enterprise", [this](){
				RepairEnterprise rep_enter;
				RepairEnterprise::cin_read_repairenterprise(rep_enter);
				if (cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid repair enterprise formatting\n"));
				}

				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));

				if (a=='y' || a=='Y') {
					this->museum_network.addRepairEnterprise(rep_enter);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Event */
	MenuSelectFilter<vector<Enterprise>> addEventToNetwork("Add an event to the selected enterprise",
			[this](vector<Enterprise>&vec) {
				if (vec.size() != 1)
					throw(UserInputReadingFailure("Multiple enterprises selected"));

				Event event;
				Event::cin_read_event(event);

				if (cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid event formatting\n"));
				}

				this->museum_network.addEvent(vec.at(0), event);
			});
	vector<MenuFilter<vector<Enterprise>>*> listAddOpt = listEnterprisesOpt;
	listAddOpt.insert(listAddOpt.begin(), &addEventToNetwork);

	MenuOptionsFilter<vector<Enterprise>> addEvent("Add a new event", listAddOpt,
			[this](vector<Enterprise> &vec){ return;  },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0, 1});


	/* Add State Worker */
	MenuSelect addStateWorker("Add a new state worker", [this](){
				StateWorker sw;
				StateWorker::cin_read_worker(sw);
				if (cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid state worker formatting\n"));
				}

				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));

				if (a=='y' || a=='Y') {
					this->museum_network.addWorker(sw);
				}
				else
					cout << "Operation aborted" << endl;
			});

	/* Add Options */
	MenuOptions add_network("Add Network Options",
			std::vector<Menu*>{&addEnterpirse, &addRepairEnterpirse, &addEvent, &addMuseum, &addUser, &addStateWorker});


	/* Modify Museums*/

	MenuSelect modifyMuseums("Modify Museums", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitFilters("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listSelectedMuseums("List Selected Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuSelect modifyMuseum("Modify the selected Museum", [this, &mus]() {
			/* Opens menu that changes the current musprise */
			if(mus.size() != 1)
				throw(UserInputReadingFailure("Multiple Museums selected"));
			Museum old_museum = *mus.begin(); // Store selected museum as backup for later modifying
			Museum new_museum = *mus.begin();

			MenuSelectFilter<Museum> modifyMuseumClosingTime("Modify closing time",
					[](Museum &mus){
						cout << "Closing time? (hour:min)" << endl;
						Time close_time; cin >> close_time;
						if(cin.fail())
							throw(UserInputReadingFailure("Invalid closing time"));
						mus.set_close(close_time);
					});

			MenuSelectFilter<Museum> modifyMuseumOpeningTime("Modify opening time",
					[](Museum &mus){
						cout << "Opening time? (hour:min)" << endl;
						Time open_time; cin >> open_time;
						if(cin.fail())
							throw(UserInputReadingFailure("Invalid opening time"));
						mus.set_open(open_time);
					});

			MenuSelectFilter<Museum> modifyMuseumNumVisits("Modify number of visits",
					[](Museum &mus){
						cout << "Number of visits?" << endl;
						unsigned int nvisits; cin >> nvisits;
						if(cin.fail())
							throw(UserInputReadingFailure("Invalid number of visits"));
						mus.set_numvisits(nvisits);
					});

			MenuSelectFilter<Museum> modifyMuseumFee("Modify fee",
					[](Museum &mus){
						cout << "Fee?" << endl;
						float fee; cin >> fee;
						if(cin.fail())
							throw(UserInputReadingFailure("Invalid fee"));
						mus.set_fee(fee);
					});

			MenuSelectFilter<Museum> modifyMuseumCommit("Commit changes",
					[this, &old_museum, &mus](Museum &museum){
						cout << "Previous Museum: " << endl; cout << old_museum << endl; utl::pauseConsole();
						cout << "Updated Museum: " << endl;	cout << museum << endl << endl;


						cout << "Are you sure that you want to update? (y/n)\n"; int a = getchar(); utl::ignore(cin);
						if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
						if (a=='y' || a=='Y') {
							this->museum_network.modifyMuseum(old_museum, museum);
							/* Update menu's museum set with the newly updated museum */
							mus.erase(old_museum);
							mus.insert(museum);
						}
						else
							cout << "Operation aborted" << endl;
					});

			MenuOptionsFilter<Museum> modifyMuseum("Modify the selected Museum",
					{&modifyMuseumOpeningTime, &modifyMuseumClosingTime, &modifyMuseumFee,
					&modifyMuseumNumVisits,&modifyMuseumCommit});

			modifyMuseum.show(new_museum); // Initialize the menu with the selected museum
		});

		MenuOptions listMenu("Modify Museums", {&listSelectedMuseums, &commitFilters, &FilterName, &FilterAddress, &modifyMuseum});
		listMenu.show();
	});

	MenuSelectFilter<vector<Enterprise>> modifyEnterpriseMenu("Modify the selected Enterprise",
			[this](vector<Enterprise>&vec){
				/* Opens menu that changes the current enterprise */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Enterprises selected"));
				Enterprise old_enterprise = vec.at(0); // Store selected enterprise as backup for later modifying

				MenuSelectFilter<Enterprise> modifyEnterpriseName("Modify Name",
						[](Enterprise &enter){
							cout << "Name?\n";
							string name; getline(cin, name);
							enter.set_name(name);
						});

				MenuSelectFilter<Enterprise> modifyEnterpriseContact("Modify Contact",
						[](Enterprise &enter){
							cout << "Contact?\n";
							string contact; getline(cin, contact);
							enter.set_contact(contact);
						});

				MenuSelectFilter<Enterprise> modifyEnterpriseAddress("Modify Address",
						[](Enterprise &enter){
							cout << "Address (street name/XXXX-XXX/region name  or	region)?\n";
							Address address; cin >> address;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid Address"));
							enter.set_address(address);
						});

				MenuSelectFilter<Enterprise> modifyEnterpriseCommit("Commit changes",
						[this, &old_enterprise](Enterprise &enter){
							cout << "Previous Enterprise: " << endl; cout << old_enterprise << endl; utl::pauseConsole();
							cout << "Updated Enterprise: " << endl;	cout << enter << endl << endl;


							cout << "Are you sure that you want to update? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if (a=='y' || a=='Y')
								this->museum_network.modifyEnterprise(old_enterprise, enter);
							else
								cout << "Operation aborted";
						});

				MenuOptionsFilter<Enterprise> modifyEnterprise("Modify the selected Enterprise",
						{&modifyEnterpriseAddress, &modifyEnterpriseContact, &modifyEnterpriseName, &modifyEnterpriseCommit});

				modifyEnterprise.show(vec.at(0)); // Initialize the menu with the selected enterprise
			});

	vector<MenuFilter<vector<Enterprise>>*> modifyEnterpriseOpt = listEnterprisesOpt;
	modifyEnterpriseOpt.push_back(&modifyEnterpriseMenu);
	MenuOptionsFilter<vector<Enterprise>> modifyEnterpriseSelection("Modify Enterprises", modifyEnterpriseOpt,
			[](vector<Enterprise>&vec){},[this](){ return(this->museum_network.getEnterprises());}, false, {0, 1});


	/* Modify Enterprises */

	MenuSelectFilter<vector<RepairEnterprise>> modifyRepairEnterpriseMenu("Modify the selected Repair-Enterprise",
			[this](vector<RepairEnterprise>&vec){
				/* Opens menu that changes the current enterprise */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple RepairEnterprises selected"));
				RepairEnterprise old_rep_enter = vec.at(0);

				MenuSelectFilter<RepairEnterprise> modifyRepairEnterpriseName("Modify Name",
						[](RepairEnterprise &enter){
							cout << "Name?\n";
							string name; getline(cin, name);
							enter.set_name(name);
						});


				MenuSelectFilter<RepairEnterprise> modifyRepairEnterpriseCoordinates("Modify coordinates",
						[](RepairEnterprise &rep_enter){
							tuple<float, float> coord;
							cout << "GPS coordinates:\n"
								 << "  X: ";
							cin >> get<0>(coord);
							utl::ignore(cin);
							cout << "  Y: ";
							cin >> get<1>(coord);
							utl::ignore(cin);

							if (cin.fail())
							  throw UserInputReadingFailure("given coordinates are not numbers");
							rep_enter.set_coords(coord);
						});

				MenuSelectFilter<RepairEnterprise> modifyRepairEnterpriseContact("Modify Contact",
						[](RepairEnterprise &enter){
							cout << "Contact?\n";
							string contact; getline(cin, contact);
							enter.set_contact(contact);
						});

				MenuSelectFilter<RepairEnterprise> modifyRepairEnterpriseAddress("Modify Address",
						[](RepairEnterprise &enter){
							cout << "Address (street name/XXXX-XXX/region name  or	region)?\n";
							Address address; cin >> address;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid Address"));
							enter.set_address(address);
						});

				MenuSelectFilter<RepairEnterprise> modifyRepairEnterpriseNumVisits("Modify number of jobs done",
						[](RepairEnterprise &rep_enter){
							cout << "Number of jobs?" << endl;
							unsigned int njobs; cin >> njobs;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid number of jobs"));
							rep_enter.set_numjobs(njobs);
						});

				MenuSelectFilter<RepairEnterprise> modifyRepairEnterpriseCommit("Commit changes",
						[this, &old_rep_enter](RepairEnterprise &enter) {
							cout << "Previous repair-enterprise: " << endl; cout << old_rep_enter << endl; utl::pauseConsole();
							cout << "Updated repair-enterprise: " << endl;	cout << enter << endl << endl;


							cout << "Are you sure that you want to update? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if (a=='y' || a=='Y')
								this->museum_network.modifyRepairEnterprise(old_rep_enter, enter);
							else
								cout << "Operation aborted";
						});

				MenuOptionsFilter<RepairEnterprise> modifyRepairEnterprise("Modify the selected Repair-Enterprise",
						{&modifyRepairEnterpriseAddress, &modifyRepairEnterpriseContact, &modifyRepairEnterpriseName,
						&modifyRepairEnterpriseNumVisits, &modifyRepairEnterpriseCoordinates, &modifyRepairEnterpriseCommit});

				modifyRepairEnterprise.show(vec.at(0)); // Initialize the menu with the selected enterprise
			});

	vector<MenuFilter<vector<RepairEnterprise>>*> modifyRepairEnterpriseOpt = listRepairEnterprisesOpt;
	modifyRepairEnterpriseOpt.push_back(&modifyRepairEnterpriseMenu);
	MenuOptionsFilter<vector<RepairEnterprise>> modifyRepairEnterpriseSelection("Modify Repair-Enterprises", modifyRepairEnterpriseOpt,
			[](vector<RepairEnterprise>&vec){},[this](){ return(this->museum_network.getRepairEnterprisesvec());}, false, {0, 1});


	/* Modify Events */

	MenuSelectFilter<vector<Event>> modifyEventMenu("Modify the selected Event",
			[this](vector<Event>&vec){
				/* Opens menu that changes the current event */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Events selected"));
				Event old_event = vec.at(0); // Store selected event as backup for later modifying

				MenuSelectFilter<Event> modifyEventName("Modify Name",
						[](Event &event){
							cout << "Name?\n";
							string name; getline(cin, name);
							event.set_name(name);
						});

				MenuSelectFilter<Event> modifyEventContact("Modify Location Name",
						[](Event &event){
							cout << "Location Name?\n";
							string location_name; getline(cin, location_name);
							event.set_location_name(location_name);
						});

				MenuSelectFilter<Event> modifyEventAddress("Modify Address",
						[](Event &event){
							cout << "Address (street name/XXXX-XXX/region name  or	region)?\n";
							Address address; cin >> address;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid Address"));
							event.set_address(address);
						});

				MenuSelectFilter<Event> modifyEventTime("Modify starting time",
						[](Event &event){
							cout << "Starting time? (hour:min)" << endl;
							Time time; cin >> time;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid starting time"));
							event.set_time(time);
						});

				MenuSelectFilter<Event> modifyEventDate("Modify starting date",
						[](Event &event){
							cout << "Date (year/month/day)?" << endl;
							Date date; cin >> date;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid starting date"));
							event.set_date(date);
						});


				MenuSelectFilter<Event> modifyEventMaxCapacity("Modify maximux capacity",
						[](Event &event){
							cout << "Max capacity?" << endl;
							unsigned capacity; cin >> capacity;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid maximum capacity"));
							event.set_max_capacity(capacity);
						});

				MenuSelectFilter<Event> modifyEventFee("Modify fee",
						[](Event &event){
							cout << "Fee?" << endl;
							float fee; cin >> fee;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid fee"));
							event.set_ticket_fee(fee);
						});

				MenuSelectFilter<Event> setEventInvalidity("Make the event invalid",
						[](Event &event){
							cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if(a == 'y' || a == 'Y')
								event.set_validity(false);
						});

				MenuSelectFilter<Event> setEventValidity("Make the event valid",
						[](Event &event){
							cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if(a == 'y' || a == 'Y')
								event.set_validity(true);
						});

				MenuSelectFilter<Event> modifyEventCommit("Commit changes",
						[this, &old_event](Event &event){
							cout << "Previous event: " << endl; cout << old_event << endl; utl::pauseConsole();
							cout << "Updated event: " << endl; cout << event << endl << endl;


							cout << "Are you sure that you want to update? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if (a=='y' || a=='Y')
								this->museum_network.modifyEvent(old_event, event);
							else
								cout << "Operation aborted";
						});


				vector<MenuFilter<Event>*> modifyCurrEventOptions =
					{ &modifyEventCommit, &setEventValidity, &setEventInvalidity, &modifyEventFee,
						&modifyEventDate, &modifyEventTime, &modifyEventAddress, &modifyEventContact,
						&modifyEventName, &modifyEventMaxCapacity};

				vector<int> repeatable_menus = {0, 1, 2};  // commit and set validity are more than one use
				MenuOptionsFilter<Event> modifyEvent("Modify the selected Event", modifyCurrEventOptions,
						[](Event &ev){}, [](){return(Event());}, false, repeatable_menus);

				modifyEvent.show(vec.at(0)); // Initialize the menu with the selected event
			});

	vector<MenuFilter<vector<Event>>*> modifyEventOpt = listEventsOpt;
	modifyEventOpt.push_back(&modifyEventMenu);
	MenuOptionsFilter<vector<Event>> modifyEventSelection("Modify Events", modifyEventOpt,
			[](vector<Event>&vec){},[this](){ return(this->museum_network.getEvents());}, false, {0, 1});


	/* Modify Workers */
	MenuSelectFilter<vector<StateWorker>> modifyWorkerMenu("Modify the selected Workers",
			[this](vector<StateWorker>&vec){
				/* Opens menu that changes the current state worker */
				if(vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Workers selected"));
				StateWorker old_worker = vec.at(0); // Store selected state worker as backup for later modifying

				MenuSelectFilter<StateWorker> modifyWorkerName("Modify Name",
						[](StateWorker &worker){
							cout << "Name?\n";
							string name; getline(cin, name);
							worker.set_name(name);
						});

				MenuSelectFilter<StateWorker> modifyWorkerContact("Modify Contact",
						[](StateWorker &worker){
							cout << "Contact?\n";
							string contact; getline(cin, contact);
							worker.set_contact(contact);
						});

				MenuSelectFilter<StateWorker> modifyWorkerAddress("Modify Address",
						[](StateWorker &worker){
							cout << "Address (street name/XXXX-XXX/region name  or	region)?\n";
							Address address; cin >> address;
							if(cin.fail())
								throw(UserInputReadingFailure("Invalid Address"));
							worker.set_address(address);
						});

				MenuSelectFilter<StateWorker> modifyWorkerMuseum("Modify Employment",
						[](StateWorker &worker){
							cout << "Set status to unemployed? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if (a=='y' || a=='Y') {
								if (worker.ishired())
									worker.fire();
							}
							else
							{
								string m_name; tuple<float, float> m_coords;
								cout << "Museum name?\n"; cin >> m_name;

								cout << "GPS coordinates:\n"
									 << "  X: ";
								cin >> get<0>(m_coords);
								utl::ignore(cin);
								cout << "  Y: ";
								cin >> get<1>(m_coords);
								utl::ignore(cin);

								if(cin.fail())
									throw(UserInputReadingFailure("Invalid Coordinates"));

								if (worker.ishired())
									worker.fire();
								worker.hire(m_name, m_coords);
							}
						});

				MenuSelectFilter<StateWorker> modifyWorkerCommit("Commit changes",
						[this, &old_worker](StateWorker &new_worker){
							cout << "Previous Worker: " << endl; cout << old_worker << endl; utl::pauseConsole();
							cout << "Updated Worker: " << endl;	cout << new_worker << endl << endl;


							cout << "Are you sure that you want to update? (y/n)\n"; int a = getchar(); utl::ignore(cin);
							if (!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
							if (a=='y' || a=='Y')
								this->museum_network.modifyWorker(old_worker, new_worker);
							else
								cout << "Operation aborted";
						});

				MenuOptionsFilter<StateWorker> modifyStateWorker("Modify the selected StateWorker",
						{&modifyWorkerAddress, &modifyWorkerContact, &modifyWorkerName, &modifyWorkerMuseum, &modifyWorkerCommit});

				modifyStateWorker.show(vec.at(0)); // Initialize the menu with the selected enterprise
			});

	vector<MenuFilter<vector<StateWorker>>*> modifyWorkerOpt = listWorkersOpt;
	modifyWorkerOpt.push_back(&modifyWorkerMenu);
	MenuOptionsFilter<vector<StateWorker>> modifyWorkerSelection("Modify StateWorkers", modifyWorkerOpt,
			[](vector<StateWorker>&vec){},[this](){ return(this->museum_network.getWorkers());}, false, {0, 1});


	/* Modify Network Options */
	MenuOptions modify_network("Modify Network Options", {&modifyEnterpriseSelection, &modifyRepairEnterpriseSelection,
			&modifyEventSelection, &modifyMuseums, &modifyWorkerSelection});

	/* Repair Museum */
	MenuSelect repairMuseums("Repair Museum", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitMuseum("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listMuseum("List Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuSelect repairSelectedMuseum("Send a repair enteprise to repair the selected museum",
				[this, &mus](){
					if (mus.size() != 1)
						throw UserInputReadingFailure("Select only one museum!");

					float distance;
					cout << "Maximum distance to the building\n";
					cin >> distance;
					utl::ignore(cin);
					if (cin.fail())
					  throw UserInputReadingFailure("given distance is not number");
					utl::clearConsole();


          RepairEnterprise r = this->museum_network.getBestRepairEnterprise(mus.begin()->get_coords(), distance);
					if (r == RepairEnterprise())
						throw(MenuForceExit("No repair-enteprise matches the given criteria"));

					cout << "The following repair-enteprise is the enterprise with most experience which follows the given criteria:\n";
					cout << r << endl;


					cout << "Are you that you want to contact this repair-enterprise? (y/n)\n"; int a = getchar(); utl::ignore(cin);
					if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
					if(a == 'y' || a == 'Y')
						this->museum_network.contactRepairEnterprise(r);

				});


		MenuOptions listMenu("Repair Museums", {&listMuseum, &commitMuseum, &FilterName, &FilterAddress, &repairSelectedMuseum});
		listMenu.show();
	});

	MenuSelectFilter<vector<StateWorker>> hireSelectedWorker("Hire Selected Worker",
		[this](vector<StateWorker> &vec) {
			if (vec.size() != 1)
				throw UserInputReadingFailure("Multiple workers selected");

			StateWorker to_hire = vec.at(0);
			MenuSelect selectMuseum("Select Museum", [this, &to_hire](){
				set<Museum> mus = this->museum_network.getMuseums();

				function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
				function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

				string name;
				Address addr;

				MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
							cout << "Name?\n"; getline(cin, name);
							name_filter = [](Museum m, string n) { return m.get_name() != n; };
						});

				MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
					cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
					if (cin.fail()) {
						utl::stream_clear(cin);
						throw(UserInputReadingFailure("Invalid name formatting\n"));
					}
					local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
				});

				MenuSelect commitMuseum("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
					for(auto it=mus.begin(); it != mus.end();)
						if (local_filter(*it, addr) || name_filter(*it, name))
							mus.erase(it++);
						else
							++it;
				});

				MenuSelect listMuseums("List Museums", [this, &mus] {
					this->museum_network.listMuseums(mus);
				});

				MenuSelect hireWorker("Hire worker to the selected museum", [this, &mus, &to_hire] {
					if (mus.size() != 1)
						throw UserInputReadingFailure("Multiple museums selected");

					this->museum_network.hireWorker(to_hire, *mus.begin());

					throw MenuForceExit(": Operation Completed with success");
				});

				MenuOptions listMenu("Select Museum", {&listMuseums, &commitMuseum, &FilterName, &FilterAddress, &hireWorker});
				listMenu.show();
			});
			selectMuseum.show();

	});

	vector<MenuFilter<vector<StateWorker>>*> hireWorkersOpt = {&WorkerSelected, &WorkerSort, &WorkerName, &hireSelectedWorker};
	MenuOptionsFilter<vector<StateWorker>> hireWorkers("Hire Workers", hireWorkersOpt,
			[this](vector<StateWorker>&vec){ return vector<StateWorker>(); },
			[this](){ // Initialize vector with all museums of the network filtered by non employment
			  vector<StateWorker> vec = this->museum_network.getWorkers();
			  flt::FilterWorkersByNonEmployment(vec);
			  return vec;
			},
			false, {0, 1});


	/* Main Menu */
	MenuOptions main_menu("Logged in as ADMIN",
			vector<Menu*>{&list_network, &remove_network, &add_network, &modify_network, &repairMuseums, &hireWorkers});

	main_menu.show();
}


/*
 * MEMBER INTERFACE
 */
MemberInterface::MemberInterface(MuseumNetwork &rnm, unsigned int cc) : museum_network(rnm) {
	vector<Card*> cards = rnm.getCards();
	vector<Card*>::iterator iter = find_if(cards.begin(), cards.end(), [&cc](Card *c1){ return(c1->get_cc() == cc); });
	if(iter == cards.end())
		throw(NoSuchObject(to_string(cc), "Card"));

	this->member_card = *(iter);
	//this->museum_network = rnm;
	cout << "Login Success!" << endl;
	utl::pauseConsole();
}

void MemberInterface::show() {
	utl::clearConsole();
	cout << "Logged in as cc with number " << this->member_card->get_cc() << " at " << Time() << endl;

	/* Send notify event prompt if intended */
	if(this->member_card->get_type() == SILVERCARD_TYPE) {
		vector<Event> events_filtered = this->museum_network.getEvents();
		flt::FilterByLocation<Event>(events_filtered, this->member_card->get_address()); // Select all events within a location
		flt::FilterEventByCapacity(events_filtered, 50); // Select all events with less than 50% capacity
		flt::FilterEventByGivenTimeFrame(events_filtered, 8, 0); // Select all events within 8 hours
		if(events_filtered.size() != 0) {
			cout << "Notification: In the next 8 hours " << events_filtered.size() <<
				" event(s) will take place in your area of residence, " << this->member_card->get_address().getRegion() << '.' << endl <<
				"All of them are, at most, 50\% full and the entry is free for you!" << endl;

			cout << "Do you want to list them? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a == 'y' || a == 'Y') {
				this->museum_network.listEvents(events_filtered);
				utl::pauseConsole();
			}
		}
	}


	/* Sort Events */
	MenuSelectFilter<vector<Event>> EventsSortName("By name", flt::SortByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSortFee("By Fee",
			[](vector<Event> &vec){
				sort(vec.begin(), vec.end(), [](Event c1, Event c2){ return c1.get_fee() < c2.get_fee(); }); });
	MenuSelectFilter<vector<Event>> EventsSortCurrCapacity("By Current Capacity",
			[](vector<Event> &vec){
				sort(vec.begin(), vec.end(), [](Event c1, Event c2){ return c1.get_current_capacity() < c2.get_current_capacity(); }); });
	MenuOptionsFilter<vector<Event>> EventSort("Sort currently selected Events",
			{&EventsSortName, &EventsSortFee, &EventsSortCurrCapacity},
			[](vector<Event>) {}, [](){ return vector<Event>(); }, true);


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt,
			[](vector<Event>&){},
			[](){return(vector<Event>());}, true);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsLocationName("Filter by location name", flt::FilterEventByLocationName);
	MenuSelectFilter<vector<Event>> EventsId("Select by id", flt::FilterEventById);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeFrame);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });


	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt=
		{&EventsSelected, &EventSort, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsTimeframe, &EventsId};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());}, // Initialize vector with all events of the network
			false, {0, 1});


	/* List Museums */
	MenuSelect listMuseums("List Museums", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitMuseum("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listMuseums("List Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuOptions listMenu("List Museums", {&listMuseums, &commitMuseum, &FilterName, &FilterAddress});
		listMenu.show();
	});

	/* List Member and Network */
	MenuSelect listUser("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	MenuOptions list_network("Network List Options", std::vector<Menu*>{&listEvents, &listMuseums});



	/* Renew Membership */
	MenuSelect renewCard ("Renew your membership", [this](){
				cout << "Renewing your membership has a cost of " << fixed << setprecision(2) << this->museum_network.getCost(this->member_card->get_type()) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->member_card->renew();
					cout <<	"Membership renewed\n";
					}
				else
					cout << "Operation aborted" << endl;
			});



	/* Purchase Event */
	MenuSelectFilter<vector<Event>> purchaseEvent("Purchase selected event",
			[this](vector<Event>&vec) {
				if (!this->member_card->isvalid())
					throw(CardExpired(this->member_card->get_cc()));
				if (vec.size() != 1)
					throw(UserInputReadingFailure("Multiple Events selected"));

				bool is_event_free = false;
				if (this->member_card->get_type() == SILVERCARD_TYPE) {
					vector<Event> silver_event = vec;
					flt::FilterEventByCapacity(silver_event, 50);  // max capacity 50%
					flt::FilterByLocation(silver_event,  this->member_card->get_address());
					flt::FilterEventByGivenTimeFrame(silver_event, 8, 0);  // events happening in the next 8 hours;

					if (!silver_event.empty()) {
						is_event_free = true;
						cout << "This event is free for you!" << endl;
					}
				}

				if (!is_event_free){
					cout << "This action will have a price of " << fixed << setprecision(2) <<
						vec.at(0).get_fee() * (1 - this->museum_network.getDiscount(member_card->get_type())) << endl;
				}

				cout << "Are you sure? (y/n)" << endl;
				int a = getchar(); utl::ignore(cin);

				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.purchaseEvent(this->member_card->get_cc(), vec.at(0));
					vec = this->museum_network.getEvents();  // Reset all events after purchase
					cout <<	"Event purchased successfully" << endl;
				}
				else
					cout << "Operation aborted" << endl;

			});
	vector<MenuFilter<vector<Event>>*> purchaseEventOpt =
		{&purchaseEvent, &EventsSelected, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsId};
	MenuOptionsFilter<vector<Event>> purchaseEventMenu("Purchase Event", purchaseEventOpt,
			[this](vector<Event>&vec){},
			[this](){ return(this->museum_network.getEvents()); }, false, {1});

	/* Visit Museum */
	MenuSelect visitMuseum("Visit Museum", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitMuseums("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listMuseums("List Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuSelect visitSelectedMuseum("Visit selected museum",
			[this, &mus](){
				if (mus.size() != 1)
					throw(UserInputReadingFailure("Multiple museums selected"));

				Museum m = *mus.begin();
				m.set_numvisits(m.get_numvisits() + 1);
				this->museum_network.modifyMuseum(*mus.begin(), m);

				/* Update the set inside the menu */
				mus.erase(mus.begin()); mus.insert(m);
			});

		MenuOptions listMenu("Visit Museum", {&listMuseums, &visitSelectedMuseum, &commitMuseums,
				&FilterName, &FilterAddress});
		listMenu.show();
	});

	/* Change current Member */
	MenuSelect changeContact("Change your contact",
			[this](){
				cout << "Contact?" << endl;
				string contact;
				getline(cin, contact);
				this->member_card->set_contact(contact);
			});
	MenuSelect changeName("Change your name",
			[this](){
				cout << "Name?" << endl;
				string name;
				getline(cin, name);
				this->member_card->set_name(name);
			});
	MenuSelect changeBirthDate("Change your birth date",
			[this](){
					Date date;
					cout << "Date (year/month/day)?" << endl;
					cin >> date;
					if(cin.fail()) {
						utl::stream_clear(cin);
						throw(UserInputReadingFailure("Invalid Date"));
					}
					this->member_card->set_birth_date(date);
			});
	MenuSelect changeAddress("Change your address",
			[this](){
				Address addr;
				cout << "Address (street name/XXXX-XXX/region name  or	region)?" << endl;
				cin >> addr;
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid Address"));
				}
				this->member_card->set_address(addr);
			});
	MenuOptions changeMember("Change your information",
			vector<Menu*>{&changeContact, &changeName, &changeBirthDate, &changeAddress});



	/* Account deletion */
	MenuSelect removeMember("Delete your account", [this](){
				cout << "Are you sure? (y/n)" << endl; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.removeCard(this->member_card);
					throw(MenuForceExit("Member menu"));
				}
				else
					cout << "Operation aborted" << endl;
			;});


	/* Main Menu */
	MenuOptions main_menu("Logged in as " + to_string(this->member_card->get_cc()),
			vector<Menu*>{&list_network, &renewCard, &listUser, &purchaseEventMenu, &visitMuseum, &changeMember, &removeMember});

	main_menu.show();
}


/*
 * USER INTERFACE
 */
UserInterface::UserInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	return;
}

void UserInterface::show(){
	/* Sort Events */
	MenuSelectFilter<vector<Event>> EventsSortName("By name", flt::SortByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSortFee("By Fee",
			[](vector<Event> &vec){
				sort(vec.begin(), vec.end(), [](Event c1, Event c2){ return c1.get_fee() < c2.get_fee(); }); });
	MenuSelectFilter<vector<Event>> EventsSortCurrCapacity("By Current Capacity",
			[](vector<Event> &vec){
				sort(vec.begin(), vec.end(), [](Event c1, Event c2){ return c1.get_current_capacity() < c2.get_current_capacity(); }); });
	MenuOptionsFilter<vector<Event>> EventSort("Sort currently selected Events",
			{&EventsSortName, &EventsSortFee, &EventsSortCurrCapacity},
			[](vector<Event>) {}, [](){ return vector<Event>(); }, true);


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt,
			[](vector<Event>&){},
			[](){return(vector<Event>());}, true);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsLocationName("Filter by location name", flt::FilterEventByLocationName);
	MenuSelectFilter<vector<Event>> EventsId("Select by id", flt::FilterEventById);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeFrame);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelectFilter<set<Museum>> MuseumsSelected("List current selected museums",
			[this](set<Museum>&mus) { this->museum_network.listMuseums(mus); });


	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt=
		{&EventsSelected, &EventSort, &EventsLocation, &EventsLocationName, &EventsName, &EventsDate, &EventsTimeframe, &EventsId};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());}, // Initialize vector with all events of the network
			false, {0, 1});

	/* List Museums */
	MenuSelect listMuseums("List Museums", [this](){
		set<Museum> mus = this->museum_network.getMuseums();

		function<bool(Museum, string)> name_filter = [](Museum m, string name) { return false; };
		function<bool(Museum, Address)> local_filter = [](Museum m, Address addr) { return false; };

		string name;
		Address addr;

		MenuSelect FilterName("Filter by Name", [&name_filter, &name]() {
					cout << "Name?\n"; getline(cin, name);
					name_filter = [](Museum m, string n) { return m.get_name() != n; };
				});

		MenuSelect FilterAddress("Filter by Address", [&local_filter, &addr]() {
			cout << "Address (street name/XXXX-XXX/region name  or	region)?\n"; cin >> addr;
			if (cin.fail()) {
				utl::stream_clear(cin);
				throw(UserInputReadingFailure("Invalid name formatting\n"));
			}
			local_filter = [](Museum m, Address add) { return !(m.get_address() == add); };
		});

		MenuSelect commitMuseum("Commit Filters", [&mus, &local_filter, &name_filter, &name, &addr]() {
			for(auto it=mus.begin(); it != mus.end();)
				if (local_filter(*it, addr) || name_filter(*it, name))
					mus.erase(it++);
				else
					++it;
		});

		MenuSelect listMuseums("List Museums", [this, &mus] {
			this->museum_network.listMuseums(mus);
		});

		MenuOptions listMenu("List Museums", {&listMuseums, &commitMuseum, &FilterName, &FilterAddress});
		listMenu.show();
	});


	/* List Network */
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});

	/* Register */
	MenuSelect registerUser("Purchase a new account\n", [this](){
				Card *card;
				Card::cin_read_card(card);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid card formatting\n"));
				}
				cout << "This operation will have a cost of " << fixed << setprecision(2) << this->museum_network.getCost(card->get_type()) << endl;
				cout << "Are you sure? (y/n)" << endl; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addCard(card);
					throw(MenuForceExit("Please login with your new account"));
				}
				else
					cout << "Operation aborted" << endl;
			});

	MenuOptions main_menu("Logged in as an NON-REGISTERED user",
			vector<Menu*>{&list_network, &registerUser});

	main_menu.show();
}


/*
 * GUI
 */
void GUI::show() {
	utl::clearConsole();
	MenuSelect adminMenu("Admin menu", [this](){ AdminInterface admin_interface(museum_network); admin_interface.show(); });

	MenuSelect userMenu("Non-registered User menu", [this](){ UserInterface user_interface(museum_network); user_interface.show(); });;

	MenuSelect memberMenu("Member menu", [this](){
			unsigned cc;
			cout << "Please type your CC" << endl; cin >> cc; utl::ignore(cin);
			MemberInterface member_interface(museum_network, cc);
			member_interface.show();
		});;

	MenuSelect importMenu("Import from a file", [this](){
			cout << "Insert the config file name (path relative to executable directory)" << endl;
			string config_file;
			cin >> config_file; utl::ignore(cin);
			this->museum_network.importFiles(config_file);
			cout << "File read successfully!" << endl;
		});

	MenuSelect exportMenu("Export to a file", [this](){
			string config_file, cards_file, museum_file, enterprise_file, repair_ent_file, worker_file;

			cout << "Insert the config file name (path relative to executable directory)" << endl; cin >> config_file;
			cout << "Insert the cards file name (path relative to executable directory)" << endl; cin >> cards_file;
			cout << "Insert the enteprise file name (path relative to executable directory)" << endl; cin >> enterprise_file;
			cout << "Insert the museum file name (path relative to executable directory)" << endl; cin >> museum_file;
			cout << "Insert the repair enterprises file name (path relative to executable directory)" << endl; cin >> repair_ent_file;
			cout << "Insert the workers file name (path relative to executable directory)" << endl; cin >> worker_file; utl::ignore(cin);

			this->museum_network.exportFiles(cards_file, museum_file, enterprise_file, repair_ent_file, worker_file, config_file);
			cout << "Files were exported with success" << endl;});

	MenuOptions main_menu("Welcome to RNM\n", vector<Menu*> {&adminMenu, &memberMenu, &userMenu, &importMenu, &exportMenu});
	main_menu.show();
}
