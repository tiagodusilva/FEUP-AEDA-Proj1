#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

class Date
{
private:
	time_t date_int;
	tm date_tm;

	/* sync time_tm info to time_t */
	bool syncmembers();

public:
	/* defaults Date to current date */
	Date();

	/*
	* WARNING: Does not check if created Date is valid
	* (a check needs to be made before calling the constructor)
	*/
	Date(short year, short month, short day);

	Date(short year, short month, short day, short hour);

	Date(short year, short month, short day, short hour, short minute);

	// GETTERS

	int getDay() const;
	int getMonth() const;
	int getYear() const;
	int getWeekday() const;  // 1 is Sunday ([1, 7])

	// OTHER PUBLIC METHODS

	/* returns true if it's a leap year */
	bool isLeapYear() const;

	/* fast forwards x years */
	void ffyear(short years=1);

	/* fast forwards x months */
	void ffmonth(short months=1);

	/* fast forwards x days */
	void ffday(short days=1);

	bool operator==(const Date &d) const;
	bool operator!=(const Date &d) const;
	bool operator< (const Date &d) const;
	bool operator<=(const Date &d) const;
	bool operator> (const Date &d) const;
	bool operator>=(const Date &d) const;
};

std::ostream& operator<<(std::ostream& stream, const Date &d);

#endif  // DATE_H
