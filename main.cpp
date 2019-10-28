#include <iostream>
#include "include/date.h"
#include <ctime>

using namespace std;

int
main()
{
	Date a;
	Date b(2019, 10, 29);
	cout << a << '\n' << b << '\n';

	if (a==b)
		cout << "==" << '\n';

	cout << a - b << '\n';

	return 0;
}

