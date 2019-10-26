#include "../include/date.h"
#include <iostream>
#include <iomanip>

using namespace std;

/* WARNING: current date is compiler dependent */
Date::Date()
{
	/* current localTime for gcc/gcc based compiler */
	time(&time_int);
}

Date::Date(short year, short month, short day)
{
	/* mktime will adjust out-of-range / unitialized members automaticaly */
	tm temp_tm = {.tm_mday=day, .tm_mon=month - 1, .tm_year=year - 1900};
	time_int = mktime(&temp_tm);
}

Date::Date(short year, short month, short day, short hour)
{
	/* mktime will adjust out-of-range / unitialized members automaticaly */
	tm temp_tm = {.tm_hour=hour, .tm_mday=day, .tm_mon=month - 1, .tm_year=year - 1900};
	time_int = mktime(&temp_tm);
}

#pragma region GETTERS

int
Date::getHour() const
{
	return localtime(&time_int)->tm_hour;
}

int
Date::getDay() const
{
	return localtime(&time_int)->tm_mday;
}

int
Date::getMonth() const
{
	return localtime(&time_int)->tm_mon + 1;
}

int
Date::getYear() const
{
	return localtime(&time_int)->tm_year + 1900;
}

#pragma endregion

bool
Date::readUserInput()
{
	return true;
}

bool
Date::readFromFile(std::ifstream& file, unsigned int& lineTracker, std::string & error)
{
	return true;
}

ostream&
operator<< (ostream& outstream, const Date& date)
{
	outstream << setfill('0') <<
	    setw(4) << date.getYear() << "/" <<
	    setw(2) << date.getMonth() << "/" <<
	    setw(2) << date.getDay() <<
	    setfill(' ');

	return outstream;
}

bool
Date::isLeapYear() const
{
	/* check if this year is a leap year */
	int year = getYear();
	if (year % 4 != 0)
		return false;

	if (year % 100 != 0)
		return true;

	return year % 400 == 0;
}

bool
Date::operator==(const Date & d) const
{

	return (this->time_int == d.time_int);
}

bool
Date::operator!=(const Date & d) const
{
	return (this->time_int != d.time_int);
}

bool
Date::operator<(const Date& d) const
{
	return (this->time_int < d.time_int);
}

bool
Date::operator<=(const Date & d) const
{
	return (this->time_int <= d.time_int);
}

bool
Date::operator>(const Date & d) const
{
	return (this->time_int > d.time_int);
}

bool
Date::operator>=(const Date & d) const
{
	return (this->time_int >= d.time_int);
}
