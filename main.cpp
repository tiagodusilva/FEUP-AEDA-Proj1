#include <gtest/gtest.h>
#include "include/event.h"
#include "include/cards.h"
#include "include/utilities.h"

using namespace std;

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	// Specify test name by setting filter to TESTNAME*
	testing::GTEST_FLAG(filter) = "card*";
    testing::GTEST_FLAG(filter) = "utilities*";
	// testing::GTEST_FLAG(filter) += "menu*";
	return RUN_ALL_TESTS();

//    Event e("Workshop de Introducao a Python 3", 0, 2, 20, Address("Aquela rua da FEUP sabes", "2222-666", "Porto"), Time(15, 0), Date(2019, 11, 13));
//    cout << e << endl;
//    cout << string(2*EVENT_OUPUT_DELIM, '-') << endl;
//    cout << e << endl;

//    IndividualCard c;
//    cout << c << endl;

//    return 0;

}
