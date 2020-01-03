#include "../include/date.h"

#include <iomanip>
#include <sstream>

#include "../include/exceptions.h"
#include "../include/utilities.h"

using namespace std;

bool
Date::syncmembers()
{
	/* sync information in tm struct to the time_t member */
	time_t temp_date_int = mktime(&date_tm);

	if (temp_date_int == -1)
		return true;
	else {
		date_int = temp_date_int;
		return false;
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

Date::Date(time_t date_int)
{
	tm *temp_tm = gmtime(&date_int);
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
Date::get_day() const
{
	return date_tm.tm_mday;
}

int
Date::get_month() const
{
	return date_tm.tm_mon + 1;
}

int
Date::get_year() const {
	return date_tm.tm_year + 1900;
}

int
Date::get_weekday() const {
	return date_tm.tm_wday + 1;
}

time_t
Date::get_raw() const {
	return this->date_int;
}

#pragma endregion

bool
Date::isLeapYear() const
{
	/* check if this year is a leap year */
	int year = this->get_year();
	if (year % 4 != 0)
		return false;

	if (year % 100 != 0)
		return true;

	return year % 400 == 0;
}

unsigned int
Date::diffdays(const Date &b) const
{
	/* get the number of days between 2 Dates */
	return abs(this->date_int - b.date_int) / SECONDS_IN_DAY;
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

/* compare */

bool
operator==(const Date& lhs, const Date& rhs)
{
	return (lhs.get_raw() == rhs.get_raw());
}

bool
operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

bool
operator< (const Date& lhs, const Date& rhs)
{
	return (lhs.get_raw() < rhs.get_raw());
}

bool
operator<=(const Date& lhs, const Date& rhs)
{
	return (lhs.get_raw() <= rhs.get_raw());
}

bool
operator> (const Date& lhs, const Date& rhs)
{
	return !(lhs <= rhs);
}

bool
operator>=(const Date& lhs, const Date& rhs)
{
	return !(lhs < rhs);
}


unsigned int
Date::operator-(const Date &b)
{
	/* get the number of days between 2 Dates */
	return this->diffdays(b);
}


ostream&
operator<<(ostream& outstream, const Date &d)
{
	outstream << setfill('0') <<
	    setw(4) << d.get_year() << '/' <<
	    setw(2) << d.get_month() << '/' <<
	    setw(2) << d.get_day() <<
	    setfill(' ');

	return outstream;
}


ofstream&
operator<<(std::ofstream& outstream, const Date &d)
{
	outstream << to_string(d.get_raw());

	return outstream;
}


std::istream&
operator>>(std::istream &instream, Date &d)
{
	try {
		//cout << "Date (year/month/day)? ";

		/* check if date is well formed */
		string temp_date;
		getline(cin, temp_date);
		int div = temp_date.find("/");
		int div2 = temp_date.find("/", div + 1);
		if (div == string::npos || div2 == string::npos)
			throw UserInputReadingFailure("Date given by user is malformed: " + temp_date);

		/* read date from istringstream */
		istringstream date_istream(temp_date);
		short year, month, day;

		date_istream >> year; date_istream.ignore(1000, '/');
		date_istream >> month; date_istream.ignore(1000, '/');
		date_istream >> day;

		d = Date(year, month, day);

	}catch(const std::exception& e) {
		d = Date(0, 0, 0);
		instream.setstate(ios::failbit);

		cerr << e.what() << endl;
	}

	return instream;
}


ifstream&
operator>>(ifstream &instream, Date &d)
{
	try {
		time_t temp_time;
		instream >> temp_time; utl::ignore(instream);  // clear '\n' char from stream

		d = Date(temp_time);

	}catch(const std::exception& e) {
		d = Date(0, 0, 0);
		instream.setstate(ios::failbit);

		cerr << e.what() << endl;
	}

	return instream;
}
