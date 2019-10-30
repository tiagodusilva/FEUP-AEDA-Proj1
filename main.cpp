#include <iostream>
#include "include/date.h"
#include "include/cards.h"

using namespace std;

int
main()
{
	//IndividualCard a("abc", "123", 123, Date(), Address());
	Date a;

	ifstream myfile;
	myfile.open("output_test.txt");
	myfile >> a;
	myfile.close();

	cout << a << '\n';
	return 0;
}

