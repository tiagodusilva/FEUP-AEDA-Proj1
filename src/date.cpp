#include "../include/date.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool
Date::syncmembers()
{
	/* sync information in tm struct to the time_t member */
	time_t temp_time_int = mktime(&time_tm);

	if (temp_time_int == -1)
		return 1;
	else {
		time_int = temp_time_int;
		return 0;
	}
}

/* WARNING: current date is compiler dependent */
Date::Date()
{
	/* current localTime for gcc/gcc based compiler */
	time(&time_int);

	/* we need to "normalize" the information about hours, minutes and seconds */
	tm *temp_tm = localtime(&time_int);
	temp_tm->tm_sec = temp_tm->tm_min = temp_tm->tm_hour = 0;

	/* save info */
	time_tm = *temp_tm;
	syncmembers();
}

Date::Date(short year, short month, short day)
{
	/* mktime will adjust out-of-range / unitialized members automaticaly */
	time_tm	= {
			.tm_mday=day,
			.tm_mon=month - 1,
			.tm_year=year - 1900
		  };

	syncmembers();
}

Date::Date(short year, short month, short day, short hour)
{
	/* mktime will adjust out-of-range / unitialized members automaticaly */
	time_tm = {
			.tm_hour=hour,
			.tm_mday=day,
			.tm_mon=month - 1,
			.tm_year=year - 1900
		  };

	syncmembers();
}

Date::Date(short year, short month, short day, short hour, short minute)
{
	/* mktime will adjust out-of-range / unitialized members automaticaly */
	time_tm = {
			.tm_min=minute,
			.tm_hour=hour,
			.tm_mday=day,
			.tm_mon=month - 1,
			.tm_year=year - 1900
		  };

	syncmembers();
}

#pragma region GETTERS

int
Date::getMinute() const
{
	return time_tm.tm_min;
}

int
Date::getHour() const
{
	return time_tm.tm_hour;
}

int
Date::getDay() const
{
	return time_tm.tm_mday;
}

int
Date::getMonth() const
{
	return time_tm.tm_mon + 1;
}

int
Date::getYear() const
{
	return time_tm.tm_year + 1900;
}

#pragma endregion

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
Date::readFromFile(std::ifstream& file, unsigned int& lineTracker, std::string & error)
{
	return true;
}

ostream&
operator<< (ostream& outstream, const Date& d)
{
	outstream << setfill('0') <<
	    setw(4) << d.getYear() << "/" <<
	    setw(2) << d.getMonth() << "/" <<
	    setw(2) << d.getDay() << " " <<
	    setw(2) << d.getHour() << ":" <<
	    setw(2) << d.getMinute() <<
	    setfill(' ');

	return outstream;
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

void
Date::fforwardyear()
{
	this->time_tm.tm_year++;
	syncmembers();
}

/*
Date
Date::operator+ (const Date& d)
{
	this->time_tm.tm_min  += d.time_tm.tm_min;
	this->time_tm.tm_hour += d.time_tm.tm_hour;
	this->time_tm.tm_mday += d.time_tm.tm_mday;
	this->time_tm.tm_mon  += d.time_tm.tm_mon;
	this->time_tm.tm_year += d.time_tm.tm_year + 1900;

	this->syncmembers();
	return *this;
}

Date
Date::operator- (const Date& d)
{
	this->time_tm.tm_min  -= d.time_tm.tm_min;
	this->time_tm.tm_hour -= d.time_tm.tm_hour;
	this->time_tm.tm_mday -= d.time_tm.tm_mday;
	this->time_tm.tm_mon  -= d.time_tm.tm_mon;
	this->time_tm.tm_year -= d.time_tm.tm_year;

	this->syncmembers();
	return *this;
}
*/
