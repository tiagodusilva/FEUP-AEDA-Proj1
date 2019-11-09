#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "../include/museum_network.h"

#include <sstream>

using namespace std;

TEST(network, add_and_list_cards){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
			   s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
			   s3("Leonel", "DAqules que e fixe", 12345, Date(2015, 12, 1), Address("Barcelos"));
	rnm.addCard(&u1);
	rnm.addCard(&i1);
	rnm.addCard(&s1);
	rnm.addCard(&s3);
	ASSERT_THROW(rnm.addCard(&s2), CardAlreadyExists);

	ASSERT_EQ(rnm.getCards().size(), 4);
	//rnm.listCards(rnm.getCards());
}

TEST(network, remcards){
	MuseumNetwork rnm;
	string delim ="\n_---------------------_\n";
	IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
			   s2("Leonel", "DAqules que e fixe", 12345, Date(2015, 12, 1), Address("Barcelos"));

	rnm.addCard(&u1);
	rnm.addCard(&i1);
	rnm.addCard(&s1);
	rnm.addCard(&s2);
	ASSERT_EQ(rnm.getCards().size(), 4);

	IndividualCard d1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
	UniCard d2("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
	std::vector<Card*> vec {&d1, &d2};

	rnm.removeCards(vec);
	ASSERT_EQ(rnm.getCards().size(), 2);
	rnm.listCards(rnm.getCards());
}

using namespace std;
