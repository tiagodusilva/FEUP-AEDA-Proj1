#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../include/cards.h"
#include "../include/exceptions.h"
#include "../include/date.h"
#include "../include/time.h"

using namespace std;

TEST(cards, files) {
	cout << "Time span" << endl;
	Date a(2019, 11, 12);
	Time t(10, 5);
	cout << timespan_size(a, t, Date(2019, 11, 13), Time(10, 5)) << endl;


	UniCard c("nome", "contact", 123, Date(1999, 1, 21), Address("estrada", "1234-567", "regiao"));

	ofstream tofile("output.txt");
	tofile << c << endl;
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


	EXPECT_THROW(Time(24, 1), InvalidObject);

}

TEST(cards, time_bet) {
	Time a(11, 00), b(15, 00);
	Date now;
	cout << timespan_size(now, a, now, b);
}
