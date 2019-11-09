#include <gtest/gtest.h>
#include "include/event.h"
#include "include/cards.h"
#include "include/utilities.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	//Specify test name by setting filter to TESTNAME*
	testing::GTEST_FLAG(filter) = "menu*";
	//testing::GTEST_FLAG(filter) = "card*";
	return RUN_ALL_TESTS();

//	const vector<int> a = {1, 2, 3, 4, 5, 6};
//	vector<int> b;
//	int i=0;
//	copy_if(a.begin(), a.end(),back_inserter(b), [](int a){ return a>3; });
//	for (i = 0; i < b.size(); ++i) {
//		cout << b.at(i) << endl;
//	}

//    Event e("Workshop de Introducao a Python 3", 0, 2, 20, Address("Aquela rua da FEUP sabes", "2222-666", "Porto"), Time(15, 0), Date(2019, 11, 13));
//    cout << e << endl;
//    cout << string(2*EVENT_OUPUT_DELIM, '-') << endl;
//    cout << e << endl;

//    IndividualCard c;
//    cout << c << endl;

    //return 0;

}
