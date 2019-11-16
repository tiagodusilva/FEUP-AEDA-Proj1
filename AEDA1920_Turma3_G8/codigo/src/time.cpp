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
			throw InvalidObject("Time", "when minutes is 0, hour must be between 0 and 24");
	}
	else if (min < 0 || min > 59 || hour < 0 || hour > 23)
		throw InvalidObject("Time", "hour must be between 0 and 23 and minutes between 0 and 59");

	this->hour = hour;
	this->min = min;
}

#pragma region GETTERS

short
Time::get_min() const {
	return min;
}

short
Time::get_hour() const {
	return hour;
}

#pragma endregion

/* compare */

bool
operator==(const Time& lhs, const Time& rhs)
{
	return ((lhs.get_hour() == rhs.get_hour()) && (lhs.get_min() == rhs.get_min()));
}

bool
operator!=(const Time& lhs, const Time& rhs)
{
	return !(lhs == rhs);
}

bool
operator< (const Time& lhs, const Time& rhs)
{
	if (lhs.get_hour() > rhs.get_hour())
		return false;

	if (lhs.get_hour() < rhs.get_hour())
		return true;

	return lhs.get_min() < rhs.get_min();
}

bool
operator<=(const Time& lhs, const Time& rhs)
{
	if (lhs.get_hour() > rhs.get_hour())
		return false;

	if (lhs.get_hour() < rhs.get_hour())
		return true;

	return lhs.get_min() <= rhs.get_min();
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
	outstream << "" << t.hour << ':' << t.min;

	return outstream;
}

istream&
operator>>(std::istream &instream, Time &t)
{
	try {
		//cout << "Time (hour:min)? ";
		string temp_time;
		getline(instream, temp_time);

		int div = temp_time.find(':');
		if (div == string::npos)
			throw UserInputReadingFailure("Time: " + temp_time);

		else {
			t.hour = (short) stoi(temp_time.substr(0, div));
			t.min = (short) stoi(temp_time.substr(div + 1));

			if (t.min == 0) {
				if (t.hour < 0 || t.hour > 24)
					throw UserInputReadingFailure("Time: when minutes is 0, hour must be between 0 and 24: " + temp_time);
			}
			else if (t.min < 0 || t.min > 59 || t.hour < 0 || t.hour > 23)
				throw UserInputReadingFailure("Time: hour must be between 0 and 23 and minutes between 0 and 59" + temp_time);
		}

	}catch(const std::exception& e) {
		instream.setstate(ios::failbit);
		t.hour = t.min = 0;

		cerr << e.what() << endl;
	}

	return instream;
}

ifstream&
operator>>(std::ifstream &instream, Time &t)
{
	try {
		string temp_time;
		getline(instream, temp_time);

		int div = temp_time.find(':');
		if (div == string::npos)
			throw FileReadingFailed("Time: " + temp_time);

		else {
			t.hour = (short) stoi(temp_time.substr(0, div));
			t.min = (short) stoi(temp_time.substr(div + 1));

			if (t.min == 0) {
				if (t.hour < 0 || t.hour > 24)
					throw FileReadingFailed("Time: when minutes is 0, hour must be between 0 and 24" + temp_time);
			}
			else if (t.min < 0 || t.min > 59 || t.hour < 0 || t.hour > 23)
				throw FileReadingFailed("Time: hour must be between 0 and 23 and minutes between 0 and 59" + temp_time);

		}

	}catch(const std::exception& e) {
		instream.setstate(ios::failbit);
		t.hour = t.min = 0;

		cerr << e.what() << endl;
	}

	return instream;
}


long
timespan_size(const Date &d_lhs, const Time &t_lhs, const Date &d_rhs, const Time &t_rhs)
{
	/* get time struct at the end of the interval */
	time_t start_raw = d_lhs.get_raw();
	tm start_tm = *(gmtime(&start_raw));
	start_tm.tm_sec  = 0;
	start_tm.tm_min  = t_lhs.get_min();
	start_tm.tm_hour = t_lhs.get_hour();


	/* get time struct at the beggining of the interval */
	time_t end_raw = d_rhs.get_raw();
	tm end_tm = *(gmtime(&end_raw));
	end_tm.tm_sec = 0;
	end_tm.tm_min = t_rhs.get_min();
	end_tm.tm_hour = t_rhs.get_hour();

	return (mktime(&end_tm) - mktime(&start_tm)) / SECS_IN_MIN;
}
