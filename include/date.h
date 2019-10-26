#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>

class Date
{
private:
	time_t time_int;

public:
	/* Defaults Date to current date */
	Date();

	/*
	* WARNING: Does not check if created Date is valid
	* (a check needs to be made before calling the constructor)
	*/
	Date(short year, short month, short day);
	Date(short year, short month, short day, short hour);

	// GETTERS

	int getHour() const;
	int getDay() const;
	int getMonth() const;
	int getYear() const;

	// OTHER PUBLIC METHODS

	/*
	* Reads a Date from user input
	* Guarentees a valid Date (returns true)
	* Ctrl + Z to abort input (returns false)
	*/
	bool readUserInput();

	/**
	Reads a Date from file
	Returns false if the Date is invalid
	Also reeturns false if ifstrean.eof() or ifstream.fail() are detected
	*/
	bool readFromFile(std::ifstream& file, unsigned int& lineTracker, std::string & error);

	/* Returns true if it's a leap year */
	bool isLeapYear() const;

	bool operator== (const Date& d) const;
	bool operator!= (const Date& d) const;
	bool operator< (const Date& d) const;
	bool operator<= (const Date& d) const;
	bool operator> (const Date& d) const;
	bool operator>= (const Date& d) const;
};

std::ostream& operator<< (std::ostream& stream, const Date& date);

#endif  // DATE_H
