#include "../include/interfaces.h"

using namespace std;

MemberInterface::MemberInterface(MuseumNetwork &rnm, unsigned int cc) {
	vector<Card*> cards = rnm.getCards();
	vector<Card*>::iterator iter = find_if(cards.begin(), cards.end(), [&cc](Card *c1){ return(c1->get_cc() == cc); });
	if(iter == cards.end())
		throw(NoSuchCard(cc));

	this->member_card = *(iter);
	this->museum_network = rnm;
	cout << "Login Success!" << endl;
	cout << "Logged in as " << this->member_card->get_name() << " at " << Time() << endl;

	listEvents = MenuSelelect("List all events.", [this](){ museum_network.listEvents(); });
	listMuseums = MenuSelelect("List all museums.", [this](){ museum_network.listMuseums(); });
	listUser = MenuSelelect("List your information", [this](){ this->museum_network.listCards(vector<Card*> { this->member_card }); });
	list_network = MenuOptions("List Network Options", std::vector<Menu*>{&listEvents, &listMuseums});
	renewCard = MenuSelelect("Renew your membership", [this](){ member_card->renew(); });
	main_menu = MenuOptions("Logged in as " + member_card->get_name(), vector<Menu*> {&list_network, &renewCard, &listUser});
}
