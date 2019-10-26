#include "../include/time.h"

using namespace std;

/* WARNING: current date is compiler dependent */
Time::Time()
{
	/* current localTime for gcc/gcc based compiler */
	time_t time_now;
	time(&time_now);

	/* we need to "normalize" the information about hours, minutes and seconds */
	tm *temp_tm = localtime(&time_now);

	/* save info */
	hour = temp_tm->tm_hour;
	min = temp_tm->tm_min;
}

Time::Time(short hour, short min)
{
	this->hour = hour;
	this->min = min;
}

#pragma region GETTERS

short
Time::getMin() const
{
	return min;
}

short
Time::getHour() const
{
	return hour;
}

#pragma endregion

ostream&
operator<<(ostream& outstream, const Time &t)
{
	outstream << setfill('0') <<
	    setw(2) << t.getHour() << ":" <<
	    setw(2) << t.getMin() <<
	    setfill(' ');

	return outstream;
}

/* compare */

bool
Time::operator==(const Time &t) const
{
	return (this->hour == t.hour) && (this->min == t.min);
}

bool
Time::operator!=(const Time &t) const
{
	return !(*this == t);
}

bool
Time::operator< (const Time &t) const
{
	if (this->hour < t.hour)
		return true;
	else if (this->min < t.min)
		return true;

	return false;
}

bool
Time::operator> (const Time &t) const
{
	if (this->hour > t.hour)
		return true;
	else if (this->min > t.min)
		return true;

	return false;
}

bool
Time::operator<=(const Time &t) const
{
	return !(*this > t);
}

bool
Time::operator>=(const Time &t) const
{
	return !(*this < t);
}
