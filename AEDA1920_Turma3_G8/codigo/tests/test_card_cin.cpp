#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../include/cards.h"
#include "../include/exceptions.h"
#include "../include/time.h"

using namespace std;

TEST(cards_cin, files) {
	Card *cp;
	Card::cin_read_card(cp);

	if (cin.fail())
		cout << "Nha Nha mean, you seg fault\n";
	else
		cout << *cp;
}
