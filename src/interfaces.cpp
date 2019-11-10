#include "../include/interfaces.h"

using namespace std;


/*void FilterBetweenDates(vector<Event> &vec) {
	Date date1;
	cin >> date1;
	if(cin.fail())
		throw(NoSuchCard(123)); // TODO add exceptions for this

	Date date2;
	cin >> date2;
	if(cin.fail())
		throw(NoSuchCard(123)); // TODO add exceptions for this

	vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
			[&date1, &date2](Event &ev) { return!(flt::is_between(ev, date1, date2)); });
	vec.erase(iter, vec.end());
}*/

MemberInterface::MemberInterface(MuseumNetwork &rnm, unsigned int cc) {
	vector<Card*> cards = rnm.getCards();
	vector<Card*>::iterator iter = find_if(cards.begin(), cards.end(), [&cc](Card *c1){ return(c1->get_cc() == cc); });
	if(iter == cards.end())
		throw(NoSuchCard(cc));

	this->member_card = *(iter);
	this->museum_network = rnm;
	cout << "Login Success!" << endl;
	getchar();
}

void MemberInterface::show() {
	cout << "Logged in as " << this->member_card->get_name() << " at " << Time() << endl;


	//listEventsDate = MenuSelelectFilter<vector<Event>>
	MenuSelelectFilter<vector<Event>> EventsBetweenDates("Between dates", flt::FilterBetweenDates<Event>);
	MenuSelelectFilter<vector<Event>> EventsInADate("In a date", flt::FilterInDate<Event>);
	vector<MenuFilter<vector<Event>>*> dateOpt = {&EventsBetweenDates, &EventsInADate};
	MenuOptionsFilter<vector<Event>> EventsDate("Filter by dates", dateOpt);

	MenuSelelectFilter<vector<Event>> EventsLocation("Filter by location", flt::FilterByLocation<Event>);
	MenuSelelectFilter<vector<Event>> EventsName("Filter by name", flt::FilterByName<Event>);
	MenuSelelectFilter<vector<Event>> EventsSelected("List current selected events",
			[this](vector<Event>&vec) { this->museum_network.listEvents(vec); });

	vector<MenuFilter<vector<Event>>*> listEventsOpt = {&EventsLocation, &EventsSelected, &EventsName, &EventsDate};
	MenuOptionsFilter<vector<Event>> listEvents("List Events.", listEventsOpt,
			[this](vector<Event>&vec){ cout<< 3;this->museum_network.listEvents(vec); }, this->museum_network.getEvents());


	MenuSelelect listMuseums("List all museums.", [this](){ museum_network.listMuseums(); });
	MenuSelelect listUser("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	MenuOptions list_network("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});
	MenuSelelect renewCard ("Renew your membership", [this](){ member_card->renew(); });
	MenuOptions main_menu("Logged in as " + member_card->get_name(), vector<Menu*> {&list_network, &renewCard, &listUser});

	main_menu.show();
}
