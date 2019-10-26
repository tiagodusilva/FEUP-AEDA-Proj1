#include <iostream>
#include "include/date.h"

using namespace std;

int
main()
{
	Date a;
	cout << a << '\n';

	Date b(2019, 10, 26);
	cout << b << '\n';

	if (a == b)
		cout << "a == b";
	else
		cout << "a != b";
	return 0;
}

