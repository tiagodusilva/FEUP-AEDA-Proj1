#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#define SECONDS_IN_DAY 86400  // 60 * 60 * 24

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

	// GETTERS

	int getDay() const;
	int getMonth() const;
	int getYear() const;
	int getWeekday() const;  // 1 is Sunday ([1, 7])

	// OTHER PUBLIC METHODS

	/* returns true if it's a leap year */
	bool isLeapYear() const;
	unsigned int diffdays(const Date &b) const;  // get the number of days between 2 Dates

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

	unsigned int operator-(const Date &b);
};

std::ostream& operator<<(std::ostream& stream, const Date &d);

#endif  // DATE_H
