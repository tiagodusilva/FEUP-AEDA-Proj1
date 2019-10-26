#include <iostream>
#include "include/date.h"

using namespace std;

int
main()
{
	Date a;
	cout << a << '\n';

	Date b(0, 1, 1);
	cout << b << '\n';

	if (a > b)
		cout << "a > b\n";
	else if (a < b)
		cout << "a < b\n";
	else
		cout << "a == b\n";
	return 0;
}

