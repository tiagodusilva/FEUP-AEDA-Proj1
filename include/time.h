#ifndef TIME_H
#define TIME_H

#include <fstream>
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

	friend std::ifstream& operator>>(std::ifstream &instream, Time &t);
};

#endif  // TIME_H
