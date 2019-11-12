#include "../include/interfaces.h"

#include "../include/utilities.h"

using namespace std;
/* Admin interface */
AdminInterface::AdminInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	cout << "Login Success!" << endl;
	utl::pauseConsole();
}


void AdminInterface::show() {

	/* Filter Cards */
	MenuSelelectFilter<vector<Card*>> CardsName("By name", flt::FilterByCardName);
	MenuSelelectFilter<vector<Card*>> CardsValidity("By validity", flt::FilterByValidity);
	MenuSelelectFilter<vector<Card*>> CardsSelect("List current selected cards",
			[this](vector<Card*>&vec) { this->museum_network.listCards(vec); });

	/* Filter Events between Dates*/
	MenuSelelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt, [](vector<Event> &a){},
			[](){return(vector<Event>());}, true);
	MenuSelelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocation<Event>);
	MenuSelelectFilter<vector<Event>> EventsTimeframe("Filter in a timeframe", flt::FilterEventByTimeCin);
	MenuSelelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocation<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsSelected("List current selected museums",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });

	/* Filter Enterprises */
	MenuSelelectFilter<vector<Enterprise>> EnterpriseLocation("Filter by location", flt::FilterByLocation<Enterprise>);
	MenuSelelectFilter<vector<Enterprise>> EnterpriseName("Filter by name", flt::FilterByName<Enterprise>);
	MenuSelelectFilter<vector<Enterprise>> EnterpriseEvent("Filter by event", flt::FilterByEvent<Enterprise>);
	MenuSelelectFilter<vector<Enterprise>> EnterpriseSelected("List current selected enterprises",
			[this](vector<Enterprise>&vec) { this->museum_network.listEnterprises(vec); });

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

	/* List Enterprises */
	vector<MenuFilter<vector<Enterprise>>*> listEnterprisesOpt = {&EnterpriseSelected, &EnterpriseLocation, &EnterpriseEvent, &EnterpriseName};
	MenuOptionsFilter<vector<Enterprise>> listEnterprises("List Enterprises", listEnterprisesOpt,
			[this](vector<Enterprise>&vec){ return vector<Enterprise>(); },
			[this](){ return(this->museum_network.getEnterprises());},
			false, {0});
	/* List Cards */
	vector<MenuFilter<vector<Card*>>*> listCardsOpt = {&CardsSelect, &CardsName, &CardsValidity};
	MenuOptionsFilter<vector<Card*>> listCards("List Cards", listCardsOpt,
			[this](vector<Card*>&vec){ return vector<Card*>(); },
			[this](){ return(this->museum_network.getCards());},
			false, {0});



	/* List Network */
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums, &listEnterprises, &listCards});


	/* Remove Museums */
	MenuSelelectFilter<vector<Museum>> removeMuseumsSelected("Remove selected museums",
		[this](vector<Museum> &vec){
			if(vec.size() == this->museum_network.getMuseums().size()) { // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.removeMuseums(vec);
					cout <<	"Museums removed!"; utl::pauseConsole();
					}
				else
					cout << "Operation aborted" << endl;
			}
		});

	vector<MenuFilter<vector<Museum>>*> removeMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName, &removeMuseumsSelected};
	MenuOptionsFilter<vector<Museum>> removeMuseums("Remove Museums", removeMuseumsOpt,
			[this](vector<Museum>&vec){ return; },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});

	/* Remove Enterprises */
	MenuSelelectFilter<vector<Enterprise>> removeEnterprisesSelected("Remove selected enterprises",
		[this](vector<Enterprise> &vec){
			if(vec.size() == this->museum_network.getEnterprises().size()) // If user has all of them selected
			cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeEnterprises(vec);
				cout <<	"Enterprises removed!"; utl::pauseConsole();
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
	MenuSelelectFilter<vector<Card*>> removeCardsSelected("Remove all selected cards",
		[this](vector<Card*> &vec){
			if(vec.size() == this->museum_network.getCards().size()) // If user has all of them selected
				cout << "Warning! You will remove all of them!!\n";
			cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a=='y' || a=='Y') {
				this->museum_network.removeCards(vec);
				cout <<	"Cards removed!"; utl::pauseConsole();
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
	MenuOptions remove_network("Remove Network Options", std::vector<Menu*>{&removeMuseums, &removeEnterprises, &removeCards});

	/* Add User */
	MenuSelelect registerUser("Add a new account\n", [this](){
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

	MenuOptions main_menu("Logged in as an non-registered user",
			vector<Menu*>{&list_network, &remove_network, &registerUser});

	main_menu.show();
}

/* Member interface */

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

	if(this->member_card->get_type() == 2) {
		vector<Event> events_filtered = this->museum_network.getEvents();
		flt::FilterByLocation<Event>(events_filtered);
		flt::FilterEventByCapacity(events_filtered, 50);
		flt::FilterEventByTime(events_filtered, Time(8, 0));
		if(events_filtered.size() != 0) {
			cout << "Notification: In the next 8 hours " << events_filtered.size() <<
				" events will take place in your area of residence, " << this->member_card->get_address().getRegion() <<
				".\nAll of them don't exceed a 50\% capacity";

			cout << "Do you want to list them? (y/n)\n"; int a = getchar(); utl::ignore(cin);
			if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
			if(a == 'y' || a == 'Y') {
				this->museum_network.listEvents(events_filtered);
			}
		}
	}

	/* Filter Events between Dates*/
	MenuSelelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);
	MenuSelelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocation<Event>);
	MenuSelelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec, this->member_card->get_type()); });

	/* List Events */
	vector<MenuFilter<vector<Event>>*> listEventsOpt = {&EventsSelected, &EventsLocation, &EventsName, &EventsDate};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>){return;},
			[this](){ return(this->museum_network.getEvents());},
			false, {0});


	/* Filter Museums */
	MenuSelelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocation<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });


	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsSelected, &MuseumsLocation, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ return vector<Museum>(); },
			[this](){ return(this->museum_network.getMuseums());},
			false, {0});


	/* List Member and Network */
	MenuSelelect listUser("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});


	/* Renew Membership */
	MenuSelelect renewCard ("Renew your membership", [this](){
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
				if(!this->member_card->isvalid()) throw(CardExpired(this->member_card->get_cc()));
				if(vec.size()!=1) throw(MultipleEventsSelected(to_string(vec.size())));
				cout << "This action will have a price of " <<
					vec.at(0).get_fee() * (1 - this->museum_network.getDiscount(member_card->get_type())) << endl;
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
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
	MenuSelelect changeContact("Change your contact",
			[this](){ string contact; getline(cin, contact); this->member_card->set_contact(contact);});
	MenuSelelect changeName("Change your name",
			[this](){ string name; getline(cin, name); this->member_card->set_name(name); });
	MenuSelelect changeBirthDate("Change your information",	[this](){
				Date date; cin >> date;
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid Date"));
				}
				this->member_card->set_birth_date(date);});
	MenuSelelect changeAddress("Change your information", [this](){;
				Address addr; cin >> addr;
				if(cin.fail()) {
					utl::stream_clear(cin);
					throw(UserInputReadingFailure("Invalid Address"));
				}
				this->member_card->set_address(addr);});

	MenuOptions changeMember("Change your information",
			vector<Menu*>{&changeContact, &changeName, &changeBirthDate, &changeAddress});


	MenuSelelect removeMember("Delete your account", [this](){
				cout << "Are you sure? (y/n)\n"; int a = getchar(); utl::ignore(cin);
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y') {
					this->museum_network.removeCard(this->member_card);
					throw(MenuForceExit("Member menu"));
				}
				else
					cout << "Operation aborted" << endl;
			;});

	MenuOptions main_menu("Logged in as " + to_string(this->member_card->get_cc()),
			vector<Menu*>{&list_network, &renewCard, &listUser, &purchaseEvent, &changeMember, &removeMember});

	main_menu.show();
}


/* User Interface */

UserInterface::UserInterface(MuseumNetwork &rnm) : museum_network(rnm) {
	cout << "Login Success!" << endl;
	utl::pauseConsole();
}

void UserInterface::show(){
	/* Filter Events between Dates */
	MenuSelelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};

	/* Filter Events */
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);
	MenuSelelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocation<Event>);
	MenuSelelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	/* Filter Museums */
	MenuSelelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocation<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
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
	MenuSelelect registerUser("Purchase a new account\n", [this](){
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

	MenuOptions main_menu("Logged in as an non-registered user",
			vector<Menu*>{&list_network, &registerUser});

	main_menu.show();
}


/* GUI */

void GUI::show() {
	utl::clearConsole();
	MenuSelelect adminMenu("Admin menu", [this](){ AdminInterface admin_interface(museum_network); admin_interface.show(); });

	MenuSelelect userMenu("User menu", [this](){ UserInterface user_interface(museum_network); user_interface.show(); });;

	MenuSelelect memberMenu("Member menu", [this](){
			unsigned cc;
			cout << "Please type your CC\n"; cin >> cc; utl::ignore(cin);
			MemberInterface member_interface(museum_network, cc);
			member_interface.show(); });;

	MenuSelelect importMenu("Import from a file", [this](){
			string config_file;
			cout << "Insert the config file name\n";
			cin >> config_file;
			this->museum_network.importFiles(config_file); });

	MenuSelelect listCards("List cards", [this](){ museum_network.listCards(); });

	MenuSelelect exportMenu("Export to a file", [this](){
			string config_file, cards_file, museum_file, enterprise_file;
			cout << "Insert the config file name\n"; cin >> config_file;
			cout << "Insert the cards file name\n"; cin >> cards_file;
			cout << "Insert the museum file name\n"; cin >> museum_file;
			cout << "Insert the enterprise file name\n"; cin >> enterprise_file;
			this->museum_network.exportFiles(config_file, cards_file, museum_file, enterprise_file); });

	MenuOptions main_menu("Welcome to RNM\n", vector<Menu*> {&adminMenu, &memberMenu, &userMenu, &importMenu, &exportMenu, &listCards});
	main_menu.show();
}
