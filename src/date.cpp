#include "../include/date.h"

using namespace std;

bool
Date::syncmembers()
{
	/* sync information in tm struct to the time_t member */
	time_t temp_date_int = mktime(&date_tm);

	if (temp_date_int == -1)
		return 1;
	else {
		date_int = temp_date_int;
		return 0;
	}
}

/* WARNING: current date is compiler dependent */
Date::Date()
{
	/* current localTime for gcc/gcc based compiler */
	time(&date_int);

	/* we need to "normalize" the information about hours, minutes and seconds */
	tm *temp_tm = gmtime(&date_int);
	temp_tm->tm_sec = temp_tm->tm_min = temp_tm->tm_hour = 0;

	/* save info */
	date_tm = *temp_tm;
	syncmembers();
}

Date::Date(short year, short month, short day)
{
	/* mktime will adjust out-of-range / unitialized members automaticaly */
	date_tm	= {
			.tm_mday=day,
			.tm_mon=month - 1,
			.tm_year=year - 1900
		  };

	syncmembers();
}

#pragma region GETTERS

int
Date::getDay() const
{
	return date_tm.tm_mday;
}

int
Date::getMonth() const
{
	return date_tm.tm_mon + 1;
}

int
Date::getYear() const
{
	return date_tm.tm_year + 1900;
}

int
Date::getWeekday() const
{
	return date_tm.tm_wday + 1;
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

ostream&
operator<<(ostream& outstream, const Date &d)
{
	outstream << setfill('0') <<
	    setw(4) << d.getYear() << "/" <<
	    setw(2) << d.getMonth() << "/" <<
	    setw(2) << d.getDay() <<
	    setfill(' ');

	return outstream;
}


/* compare */

bool
Date::operator==(const Date &d) const
{

	return (this->date_int == d.date_int);
}

bool
Date::operator!=(const Date &d) const
{
	return (this->date_int != d.date_int);
}

bool
Date::operator< (const Date &d) const
{
	return (this->date_int < d.date_int);
}

bool
Date::operator<=(const Date &d) const
{
	return (this->date_int <= d.date_int);
}

bool
Date::operator> (const Date &d) const
{
	return (this->date_int > d.date_int);
}

bool
Date::operator>=(const Date &d) const
{
	return (this->date_int >= d.date_int);
}

/* fast forward */

void
Date::ffyear(short years)
{
	this->date_tm.tm_year += years;
	syncmembers();
}

void
Date::ffmonth(short months)
{
	this->date_tm.tm_mon += months;
	syncmembers();
}

void
Date::ffday(short days)
{
	this->date_tm.tm_mday += days;
	syncmembers();

}
