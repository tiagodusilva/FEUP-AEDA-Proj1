#include "../include/interfaces.h"

#include "../include/utilities.h"

using namespace std;


MemberInterface::MemberInterface(MuseumNetwork &rnm, unsigned int cc) : museum_network(rnm) {
	vector<Card*> cards = rnm.getCards();
	vector<Card*>::iterator iter = find_if(cards.begin(), cards.end(), [&cc](Card *c1){ return(c1->get_cc() == cc); });
	if(iter == cards.end())
		throw(NoSuchCard(cc));

	this->member_card = *(iter);
	//this->museum_network = rnm;
	cout << "Login Success!" << endl;
	getchar();
}

void MemberInterface::show() {
	utl::clearConsole();
	cout << "Logged in as cc with number " << this->member_card->get_cc() << " at " << Time() << endl;


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
	vector<MenuFilter<vector<Event>>*> listEventsOpt = {&EventsLocation, &EventsSelected, &EventsName, &EventsDate};
	MenuOptionsFilter<vector<Event>> listEvents("List Events", listEventsOpt,
			[this](vector<Event>&vec){ this->museum_network.listEvents(vec, this->member_card->get_type()); },
			[this](){ return(this->museum_network.getEvents()); });


	/* Filter Museums */
	MenuSelelectFilter<vector<Museum>> MuseumsLocation("Filter by location", flt::FilterByLocation<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsName("Filter by name", flt::FilterByName<Museum>);
	MenuSelelectFilter<vector<Museum>> MuseumsSelected("List current selected events",
			[this](vector<Museum>&vec) { this->museum_network.listMuseums(vec); });


	/* List Museums */
	vector<MenuFilter<vector<Museum>>*> listMuseumsOpt = {&MuseumsLocation, &MuseumsSelected, &MuseumsName};
	MenuOptionsFilter<vector<Museum>> listMuseums("List Museums", listMuseumsOpt,
			[this](vector<Museum>&vec){ this->museum_network.listMuseums(vec); },
			[this](){ return(this->museum_network.getMuseums());});


	/* List Member and Network */
	MenuSelelect listUser("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});


	/* Renew Membership */
	MenuSelelect renewCard ("Renew your membership", [this](){ member_card->renew(); });


	/* Purchase Event */
	MenuOptionsFilter<vector<Event>> purchaseEvent("Purchase Event", listEventsOpt,
			[this](vector<Event>&vec){
				if(!this->member_card->isvalid()) throw(CardExpired(this->member_card->get_cc()));
				if(vec.size()!=1) throw(MultipleEventsSelected(to_string(vec.size())));
				this->museum_network.purchaseEvent(this->member_card->get_cc(), vec.at(0));
				cout <<	"Event purchased successfully\n"; getchar();},
				[this](){ return(this->museum_network.getEvents()); });


	/* Change current Member */
	MenuSelelect changeContact("Change your contact",
			[this](){ string contact; getline(cin, contact); this->member_card->set_contact(contact);});
	MenuSelelect changeName("Change your name",
			[this](){ string name; getline(cin, name); this->member_card->set_name(name); });
	MenuSelelect changeBirthDate("Change your information",	[this](){
				Date date; cin >> date;
				if(cin.fail()) throw(UserInputReadingFailure("Invalid Date"));
				this->member_card->set_birth_date(date);});
	MenuSelelect changeAddress("Change your information", [this](){;
				Address addr; cin >> addr;
				if(cin.fail()) throw(UserInputReadingFailure("Invalid Address"));
				this->member_card->set_address(addr);});

	MenuOptions changeMember("Change your information",
			vector<Menu*>{&changeContact, &changeName, &changeBirthDate, &changeAddress});


	MenuSelelect removeMember("Delete your account", [this](){
				cout << "Are you sure? (y/n)\n"; int a = getchar();
				if(!(a == 'y' || a == 'Y' || a == 'n' || a == 'N')) throw(UserInputReadingFailure("Type y or n"));
				if(a=='y' || a=='Y'){cout << "NICE\n"; this->museum_network.removeCard(this->member_card);};});

	MenuOptions main_menu("Logged in as " + member_card->get_name(),
			vector<Menu*>{&list_network, &renewCard, &listUser, &purchaseEvent, &changeMember, &removeMember});

	main_menu.show();
}

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
			cout << "Insert the cards file name\n"; cin >> config_file;
			cout << "Insert the museum file name\n"; cin >> config_file;
			cout << "Insert the enterprise file name\n"; cin >> config_file;
			this->museum_network.exportFiles(config_file, cards_file, museum_file, enterprise_file); });

	MenuOptions main_menu("Welcome to RNM\n", vector<Menu*> {&adminMenu, &memberMenu, &userMenu, &importMenu, &exportMenu, &listCards});
	main_menu.show();
}
