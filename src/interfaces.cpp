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

	/* Filter Cards */
	MenuSelectFilter<vector<Card*>> CardsName("By name", flt::FilterByCardName);
	MenuSelectFilter<vector<Card*>> CardsValidity("By validity", flt::FilterByValidity);
	MenuSelectFilter<vector<Card*>> CardsSelect("List current selected cards",
			[this](vector<Card*>&vec) { this->museum_network.listCards(vec); });


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt, [](vector<Event> &a){},
			[](){return(vector<Event>());}, true);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeCin);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocationCin<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsSelected("List current selected museums",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });


	/* Filter Enterprises */
	MenuSelectFilter<vector<Enterprise>> EnterpriseLocation("Filter by location", flt::FilterByLocationCin<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseName("Filter by name", flt::FilterByName<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseEvent("Filter by event", flt::FilterByEvent<Enterprise>);
	MenuSelectFilter<vector<Enterprise>> EnterpriseSelected("List current selected enterprises",
			[this](vector<Enterprise>&vec) { this->museum_network.listEnterprises(vec); });


	/* List Cards */
	vector<MenuFilter<vector<Card*>>*> listCardsOpt = {&CardsSelect, &CardsName, &CardsValidity};
	MenuOptionsFilter<vector<Card*>> listCards("List Cards", listCardsOpt,
			[this](vector<Card*>&vec){ return vector<Card*>(); },
			[this](){ return(this->museum_network.getCards());},
			false, {0});


	/* List Enterprises */
	vector<MenuFilter<vector<Enterprise>>*> listEnterprisesOpt = {&EnterpriseSelected, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName};
	MenuOptionsFilter<vector<Enterprise>> listEnterprises("List Enterprises", listEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return vector<Enterprise>(); },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0});


	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt = {&EventsSelected, &EventsLocation, &EventsName, &EventsDate, &EventsTimeframe};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());},
			false, {0});


	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});


	/* List Network Options */
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums, &listEnterprises, &listCards});


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
	vector<MenuFilter<vector<Event>>*> removeEventsOpt =
		{&EventsSelected, &EventsTimeframe, &EventsDate, &EventsLocation, &EventsName, &removeEventsSelected};
	MenuOptionsFilter<vector<Event>> removeEvents("Remove Events", removeEventsOpt,
			[this](vector<Event>&vec){ return; },
			[this](){ return(this->museum_network.getEvents());},
			false, {0});


	/* Remove Museums */
	MenuSelectFilter<vector<Museum>> removeMuseumsSelected("Remove selected museums",
		[this](vector<Museum> &vec){
			if(vec.size() == this->museum_network.getMuseums().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeMuseums(vec);
				cout <<	"Museum(s) removed!"; utl::pauseConsole();
				vec.erase(vec.begin(), vec.end());
			}
			else
				cout << "Operation aborted" << endl;
		});
	vector<MenuFilter<vector<Museum>>*> removeMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName, &removeMuseumsSelected};
	MenuOptionsFilter<vector<Museum>> removeMuseums("Remove Museums", removeMuseumsOpt,
			[this](vector<Museum>&vec){ return; },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});


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
		{&EnterpriseSelected, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName, &removeEnterprisesSelected};
	MenuOptionsFilter<vector<Enterprise>> removeEnterprises("Remove Enterprises", removeEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return; },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0});


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
		{&CardsSelect, &CardsName, &CardsValidity, &removeCardsSelected};
	MenuOptionsFilter<vector<Card*>> removeCards("Remove Cards", removeCardsOpt,
			[this](vector<Card*>&vec){ return; },
			[this](){ return(this->museum_network.getCards());},
			false, {0});


	/* Remove Network Options */
	MenuOptions remove_network("Network Remove Options", std::vector<Menu*>{&removeEvents, &removeMuseums, &removeEnterprises, &removeCards});


	/* Add User */
	MenuSelect addUser("Add a new account", [this](){
				Card *card;
				Card::cin_read_card(card);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid card formatting\n"));
				}
				cout << "This operation will have a cost of " << this->museum_network.getCost(card->get_type()) << endl;
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
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid enterprise formatting\n"));
				}
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.addEnterprise(enterprise);
				}
				else
					cout << "Operation aborted" << endl;
			});


	/* Add Event */
	MenuSelectFilter<vector<Enterprise>> addEventToNetwork("Add an event to the selected enterprise",
			[this](vector<Enterprise>&vec) {
				if(vec.size() != 1) throw(UserInputReadingFailure("Multiple enterprises selected"));
				Event event; Event::cin_read_event(event);
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid museum formatting\n"));
				}

				this->museum_network.addEvent(vec.at(0), event);
			});
	vector<MenuFilter<vector<Enterprise>>*> listAddOpt = listEnterprisesOpt;
	listAddOpt.push_back(&addEventToNetwork);
	MenuOptionsFilter<vector<Enterprise>> addEvent("Add a new event", listAddOpt,
			[this](vector<Enterprise> &vec){ return;  },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0});


	/* Add Options */
	MenuOptions add_network("Add Network Options", std::vector<Menu*>{&addEnterpirse, &addEvent, &addMuseum, &addUser});


	/* Main Menu */
	MenuOptions main_menu("Logged in as ADMIN",
			vector<Menu*>{&list_network, &remove_network, &add_network});


	main_menu.show();
}


/*
 * MEMBER INTERFACE
 */
MemberInterface::MemberInterface(MuseumNetwork &rnm, unsigned int cc) : museum_network(rnm) {
	vector<Card*> cards = rnm.getCards();
	vector<Card*>::iterator iter = find_if(cards.begin(), cards.end(), [&cc](Card *c1){ return(c1->get_cc() == cc); });
	if(iter == cards.end())
		throw(NoSuchCard(cc));

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
		flt::FilterEventByTimeFrame(events_filtered, 8); // Select all events within 8 hours
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


	/* Filter Events between Dates*/
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec, this->member_card->get_type()); });

	/* Filter Museums */
	MenuSelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocationCin<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });



	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt = {&EventsSelected, &EventsLocation, &EventsName, &EventsDate};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());},
			false, {0});

	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});

	/* List Member and Network */
	MenuSelect listUser("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	MenuOptions list_network("Network List Options", std::vector<Menu*>{&listEvents, &listMuseums});



	/* Renew Membership */
	MenuSelect renewCard ("Renew your membership", [this](){
				cout << "Renewing your membership has a cost of " << this->museum_network.getCost(this->member_card->get_type()) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->member_card->renew();
					cout <<	"Membership renewed\n"; utl::pauseConsole();
					}
				else
					cout << "Operation aborted" << endl;
			member_card->renew(); });



	/* Purchase Event */
	MenuOptionsFilter<vector<Event>> purchaseEvent("Purchase Event", listEventsOpt,
			[this](vector<Event>&vec){
				if (!this->member_card->isvalid())
					throw(CardExpired(this->member_card->get_cc()));
				if (vec.size() != 1)
					throw(MultipleEventsSelected(to_string(vec.size())));

				bool is_event_free = false;
				if (this->member_card->get_type() == SILVERCARD_TYPE) {
					vector<Event> silver_event = vec;
					flt::FilterEventByCapacity(silver_event, 50);  // max capacity 50%
					flt::FilterByLocation(silver_event,  this->member_card->get_address());
					flt::FilterEventByTimeFrame(silver_event, 8);  // events happening in the next 8 hours;

					if (!silver_event.empty()) {
						is_event_free = true;
						cout << "This event is free for you!" << endl;
					}
				}

				if (!is_event_free){
					cout << "This action will have a price of " <<
						vec.at(0).get_fee() * (1 - this->museum_network.getDiscount(member_card->get_type())) << endl;
				}

				cout << "Are you sure? (y/n)\n";
				int a = getchar(); utl::ignore(cin);

				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.purchaseEvent(this->member_card->get_cc(), vec.at(0));
					cout <<	"Event purchased successfully\n"; utl::pauseConsole();
					}
				else
					cout << "Operation aborted" << endl;
				},
			[this](){ return(this->museum_network.getEvents()); });



	/* Change current Member */
	MenuSelect changeContact("Change your contact",
			[this](){ string contact; getline(cin, contact); this->member_card->set_contact(contact);});
	MenuSelect changeName("Change your name",
			[this](){ string name; getline(cin, name); this->member_card->set_name(name); });
	MenuSelect changeBirthDate("Change your information",	[this](){
				Date date; cin >> date;
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid Date"));
				}
				this->member_card->set_birth_date(date);});
	MenuSelect changeAddress("Change your information", [this](){;
				Address addr; cin >> addr;
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid Address"));
				}
				this->member_card->set_address(addr);});
	MenuOptions changeMember("Change your information",
			vector<Menu*>{&changeContact, &changeName, &changeBirthDate, &changeAddress});



	/* Account deletion */
	MenuSelect removeMember("Delete your account", [this](){
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
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
			vector<Menu*>{&list_network, &renewCard, &listUser, &purchaseEvent, &changeMember, &removeMember});

	main_menu.show();
}


/*
 * USER INTERFACE
 */
UserInterface::UserInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	return;
}

void UserInterface::show(){
	/* Filter Events between Dates */
	MenuSelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);
	MenuSelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocationCin<Event>);
	MenuSelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocationCin<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });


	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt = {&EventsSelected, &EventsLocation, &EventsName, &EventsDate};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());},
			false, {0});

	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});


	/* List Network */
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});

	/* Register */
	MenuSelect registerUser("Purchase a new account\n", [this](){
				Card *card;
				Card::cin_read_card(card);
				if(cin.fail()) {
					utl::ignore(cin);
					throw(UserInputReadingFailure("Invalid card formatting\n"));
				}
				cout << "This operation will have a cost of " << this->museum_network.getCost(card->get_type()) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
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

	MenuSelect userMenu("User menu", [this](){ UserInterface user_interface(museum_network); user_interface.show(); });;

	MenuSelect memberMenu("Member menu", [this](){
			unsigned cc;
			cout << "Please type your CC\n"; cin >> cc; utl::ignore(cin);
			MemberInterface member_interface(museum_network, cc);
			member_interface.show(); });;

	MenuSelect importMenu("Import from a file", [this](){
			string config_file;
			cout << "Insert the config file name\n";
			cin >> config_file; utl::ignore(cin);
			this->museum_network.importFiles(config_file);
			cout << "File read successfully!\n";});

	MenuSelect exportMenu("Export to a file", [this](){
			string config_file, cards_file, museum_file, enterprise_file;
			cout << "Insert the config file name\n"; cin >> config_file;
			cout << "Insert the cards file name\n"; cin >> cards_file;
			cout << "Insert the museum file name\n"; cin >> museum_file;
			cout << "Insert the enterprise file name\n"; cin >> enterprise_file; utl::ignore(cin);
			this->museum_network.exportFiles(config_file, cards_file, museum_file, enterprise_file);
			cout << "Files were exported with success\n";});

	MenuOptions main_menu("Welcome to RNM\n", vector<Menu*> {&adminMenu, &memberMenu, &userMenu, &importMenu, &exportMenu});
	main_menu.show();
}
