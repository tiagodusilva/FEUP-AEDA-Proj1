#include "../include/time.h"

#include <ctime>
#include <iomanip>

#include "../include/exceptions.h"

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
	hour = (short) temp_tm->tm_hour;
	min = (short) temp_tm->tm_min;
}

Time::Time(short hour, short min)
{
	if (min == 0) {
		if (hour < 0 || hour > 24)
			throw InvalidTime();
	}
	else if (min < 0 || min > 59 || hour < 0 || hour > 23)
		throw InvalidTime();

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

/* compare */

bool
operator==(const Time& lhs, const Time& rhs)
{
	return ((lhs.getHour() == rhs.getHour()) && (lhs.getMin() == rhs.getMin()));
}

bool
operator!=(const Time& lhs, const Time& rhs)
{
	return !(lhs == rhs);
}

bool
operator< (const Time& lhs, const Time& rhs)
{
	if (lhs.getHour() < rhs.getHour())
		return true;
	else if (lhs.getMin() < rhs.getMin())
		return true;

	return false;
}

bool
operator<=(const Time& lhs, const Time& rhs)
{
	if (lhs.getHour() < rhs.getHour())
		return true;
	else if (lhs.getMin() < rhs.getMin())
		return true;

	return (lhs == rhs);
}

bool
operator> (const Time& lhs, const Time& rhs)
{
	return !(lhs <= rhs);
}


bool
operator>=(const Time& lhs, const Time& rhs)
{
	return !(lhs < rhs);
}

ostream&
operator<<(ostream& outstream, const Time &t)
{
	outstream << setfill('0') <<
	    setw(2) << t.hour << ':' <<
	    setw(2) << t.min <<
	    setfill(' ');

	return outstream;
}

ofstream&
operator<<(std::ofstream& outstream, const Time &t)
{
	outstream << t.hour << ':' << t.min;

	return outstream;
}

ifstream&
operator>>(std::ifstream &instream, Time &t)
{
	try {
		string temp_str;
		getline(instream, temp_str);

		int div = temp_str.find(':');
		if (div == string::npos)
			throw FileReadingFailed("time: " + temp_str);

		else {
			t.hour = (short) stoi(temp_str.substr(0, div));
			t.min = (short) stoi(temp_str.substr(div + 1));
		}

	}catch(const std::exception& e) {
		instream.setstate(ios::failbit);
		t.hour = t.min = 0;

		cerr << e.what() << endl;
	}

	return instream;
}
