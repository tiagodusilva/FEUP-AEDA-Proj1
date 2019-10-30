#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

class Time
{
private:
	short hour, min;

public:
	/* defaults current time */
	Time();

	Time(short hour, short min);

	short getMin() const;
	short getHour() const;

	bool operator==(const Time& t) const;
	bool operator!=(const Time& t) const;
	bool operator< (const Time& t) const;
	bool operator<=(const Time& t) const;
	bool operator> (const Time& t) const;
	bool operator>=(const Time& t) const;

	friend std::ostream& operator<<(std::ostream& outstream, const Time &t);
	friend std::ofstream& operator<<(std::ofstream& outstream, const Time &t);
};

//std::ostream& operator<<(std::ostream& outstream, const Time &t);
//std::ofstream& operator<<(std::ofstream& outstream, const Time &t);

#endif  // TIME_H
