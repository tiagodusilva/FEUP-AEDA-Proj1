<<<<<<< HEAD
#include <gtest/gtest.h>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    // Specify test name by setting filter to TESTNAME*
    testing::GTEST_FLAG(filter) = "menu*";
    return RUN_ALL_TESTS();
}
=======
#include <iostream>
#include "include/date.h"
#include "include/cards.h"
#include "include/time.h"

using namespace std;

int
main()
{
	//IndividualCard a("abc", "123", 123, Date(), Address());
	//Date a;
	//Time a(11, 12);
	//cout << a << '\n';

	//ofstream myfile;
	//myfile.open("output_test.txt");
	//myfile << a;
	//myfile.close();

	Time b;

	ifstream myfile2;
	myfile2.open("output_test.txt");
	myfile2 >> b;
	myfile2.close();

	cout << b << '\n';
	return 0;
}

>>>>>>> ce594b381feb2b4a1091b73eebd1dddaf6a66700
