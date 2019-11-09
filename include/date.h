#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <fstream>
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
	Date(time_t date_int);

	/*
	* WARNING: Does not check if created Date is valid
	* (tries to automaticaly fixes mistakes in date inputs)
	*/
	Date(short year, short month, short day);

	// GETTERS

	int getDay() const;
	int getMonth() const;
	int getYear() const;
	int getWeekday() const;  // 1 is Sunday ([1, 7])
	time_t getRaw() const;

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


	unsigned int operator-(const Date &b);
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator< (const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& outstream, const Date &d);
std::ofstream& operator<<(std::ofstream& outstream, const Date &d);
std::ifstream& operator>>(std::ifstream &instream, Date &d);

#endif  // DATE_H
