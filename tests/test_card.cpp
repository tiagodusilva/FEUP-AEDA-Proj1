#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../include/cards.h"

using namespace std;

TEST(cards, files) {
	vector<unsigned int> vec;
	vec.push_back(1472); vec.push_back(2327);

	UniCard c("nome", "contact", 123, Date(1999, 1, 21), Address("estrada", "1234-567", "regiao"), vec);

	ofstream tofile("output.txt");
	tofile << c;
	tofile.close();

	Card *cp;
	ifstream fromfile("output.txt");
	fromfile >> cp;
	fromfile.close();

	ASSERT_EQ(c.get_name(), cp->get_name());
	ASSERT_EQ(c.get_contact(), cp->get_contact());
	ASSERT_EQ(c.get_cc(), cp->get_cc());
	ASSERT_EQ(c.get_birth_date(), cp->get_birth_date());
	ASSERT_EQ(c.get_creation_date(), cp->get_creation_date());
	ASSERT_EQ(c.get_expiration_date(), cp->get_expiration_date());
	ASSERT_EQ(c.get_address(), cp->get_address());
	ASSERT_EQ(c.get_bought_events(), cp->get_bought_events());
}
