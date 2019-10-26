#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>

class Date
{
private:
	time_t time_int;
	tm time_tm;

public:
	/* Defaults Date to current date */
	Date();

	/*
	* WARNING: Does not check if created Date is valid
	* (a check needs to be made before calling the constructor)
	*/
	Date(short year, short month, short day);

	Date(short year, short month, short day, short hour);

	Date(short year, short month, short day, short hour, short minute);

	// GETTERS

	int getMinute() const;
	int getHour() const;
	int getDay() const;
	int getMonth() const;
	int getYear() const;

	// OTHER PUBLIC METHODS

	bool readFromFile(std::ifstream& file, unsigned int& lineTracker, std::string & error);

	/* sync time_tm info to time_t */
	bool syncmembers();

	/* Returns true if it's a leap year */
	bool isLeapYear() const;

	/* 1 year forward */
	void fforwardyear();

	bool operator== (const Date& d) const;
	bool operator!= (const Date& d) const;
	bool operator< (const Date& d) const;
	bool operator<= (const Date& d) const;
	bool operator> (const Date& d) const;
	bool operator>= (const Date& d) const;
	//Date operator+ (const Date& d);
	//Date operator- (const Date& d);
};

std::ostream& operator<< (std::ostream& stream, const Date& date);

#endif  // DATE_H
