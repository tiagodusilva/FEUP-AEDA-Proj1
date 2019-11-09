#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "../include/museum_network.h"

#include <sstream>

using namespace std;


TEST(network, DISABLED_add_and_list_cards){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
			   s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
			   s3("Leonel", "DAqules que e fixe", 12345, Date(2015, 12, 1), Address("Barcelos"));
	rnm.addCard(&i1);
	rnm.addCard(&u1);
	rnm.addCard(&s1);
	rnm.addCard(&s3);

	SilverCard s5("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga"));
	ASSERT_THROW(rnm.addCard(&s5), CardAlreadyExists);
	ASSERT_EQ(rnm.getCards().size(), 4);

	vector<Card*> vec = {&i1, &u1};
	rnm.listCards(vec);
	//rnm.listCards(rnm.getCards());
}


TEST(network, DISABLED_remcards){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
			   s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
			   s3("Leonel", "DAqules que e fixe", 12345, Date(2015, 12, 1), Address("Barcelos"));
	rnm.addCard(&i1);
	rnm.addCard(&u1);
	rnm.addCard(&s1);
	rnm.addCard(&s3);

	ASSERT_EQ(rnm.getCards().size(), 4);

	IndividualCard d1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard d2("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	std::vector<Card*> vec {&d1, &d2};

	rnm.removeCards(vec);
	ASSERT_EQ(rnm.getCards().size(), 2);
	ASSERT_THROW(rnm.removeCard(&d1), NoSuchCard);
	// rnm.listCards(rnm.getCards());
}


TEST(network, DISABLED_modcard){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
			   s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
			   s3("Leonel", "DAqules que e fixe", 12345, Date(2015, 12, 1), Address("Barcelos"));
	rnm.addCard(&i1);
	rnm.addCard(&u1);
	rnm.addCard(&s1);
	rnm.addCard(&s3);

	IndividualCard d1("Rosetta Stone changed", "Nice", 123, Date(), Address("AVANTE"));
	rnm.modifyCard(&d1); // Change card with 123
	ASSERT_EQ(rnm.getCards().at(0)->get_name(), d1.get_name());


	// ASSERT_THROW(rnm.removeCard(&i1), NoSuchCard); TODO This throws nothing, is it supposed to?
	rnm.removeCard(&d1);
	ASSERT_THROW(rnm.modifyCard(&i1), NoSuchCard);
	rnm.listCards(rnm.getCards());
}

TEST(network, DISABLED_enterprises){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	set<Event> e;

	Enterprise e1("Moreira", "912", Address("Porto")),
			   e2("Noice", "123", Address("Porto")),
			   e3("Lul", "132", Address("noice"));

	vector<Enterprise> vec = {e3};

	rnm.addEnterprise(e1);
	rnm.addEnterprise(e2);

	EXPECT_EQ(rnm.getEnterprises().size(), 2);
	EXPECT_THROW(rnm.addEnterprise(e1), EnterpriseAlreadyExists);
	// EXPECT_THROW(rnm.listEnterprises(vec), NoSuchEnterprise); This throws nothing becaus when coming from menu all of the enterprises provided are valid

	rnm.listEnterprises();
}

TEST(network, DISABLED_museums){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	set<Event> e;

	Museum  m1("M1", Time(9, 30), Time(19, 00), 2, Address("Evora")),
			m2("M2", Time(10, 30), Time(20, 00), 2, Address("Porto")),
	        m3("M3", Time(11, 20), Time(21, 30), 2, Address("Lisboa"));

	vector<Museum> vec = {m3};

	rnm.addMuseum(m1);
	rnm.addMuseum(m2);

	EXPECT_EQ(rnm.getMuseums().size(), 2);
	EXPECT_THROW(rnm.addMuseum(m1), MuseumAlreadyExists);
	// EXPECT_THROW(rnm.listEnterprises(vec), NoSuchEnterprise); This throws nothing becaus when coming from menu all of the enterprises provided are valid

	//rnm.listMuseums();
	//rnm.listMuseums(vec);
}

TEST(network, getEvents) {
	MuseumNetwork rnm;

	Event e1("1", 23, 5, Address("Porto"), Time(9, 0), Date(2002, 9, 11)),
		  e2("2", 23, 2, Address("Asd"), Time(11, 0), Date(2011, 9, 21)),
		  e3("3", 10, 3, Address("Opa"), Time(15, 0), Date(2019, 4, 4)),
		  e4("4", 10, 6, Address("Nice"), Time(20, 0), Date(2020, 1, 11)),
		  e5("5", 15, 8, Address("Evora"), Time(9, 50), Date(2030, 7, 15)),
		  e6("6", 30, 9, Address("Aveirso"), Time(11, 10), Date(2001, 10, 5)),
		  e7("7", 30, 8, Address("Faro"), Time(20, 30), Date(2001, 11, 3));

	set<Event> set1 = {e1, e2, e3};
	set<Event> set2 = {e4, e5, e6};
	set<Event> set3 = {e7};

	Enterprise ent1("Moreira", "912", Address("Porto"), set1),
			   ent2("Noice", "123", Address("Porto"), set2),
			   ent3("Lul", "132", Address("noice"), set3);

	rnm.addEnterprise(ent1);
	rnm.addEnterprise(ent2);
	rnm.addEnterprise(ent3);

	ASSERT_EQ(rnm.getEvents().size(), 7);
	rnm.listEvents();
}
