/** @file time.h */
#ifndef TIME_H
#define TIME_H

#include <fstream>
#include <iostream>

#include "date.h"

/** @defgroup datetime_grp Time and Date module */

/** @addtogroup	datetime_grp
  *
  * @brief	Code related to the handling, saving and comparisons of points in time
  *
  * @{
  */

/**
 * @brief	Class that saves and handles time information in our project
 */
class Time
{
private:
	/** @brief	integer type that represents hours [0, 23] */
	short hour;
	/** @brief	integer type that represents minutes [0, 59] */
	short min;

public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor of the class Time
	 *
	 * @details	Creates a Time object that contains information about the current system time
	 */
	Time();
	/**
	 * @brief	Constructor of the class Time
	 *
	 * @param hour	representing hours
	 * @param min	representing minutes
	 *
	 * @throws InvalidObject	when the given time is not representable in a 24-hour clock
	 */
	Time(short hour, short min);

	/* GETTERS */
	/**
	 * @brief	Getter for the saved hours information
	 *
	 * @return	hours information currently saved in the class
	 */
	short get_hour() const;
	/**
	 * @brief	Getter for the saved minutes information
	 *
	 * @return	minutes information currently saved in the class
	 */
	short get_min() const;

	/* INSERTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded ostream insertion operator
	 *
	 * @details	Mainly used with std::cout to show formated information on screen
	 *
	 * @param outstream	Reference to the ostream object to insert info to
	 * @param t		Reference to the Time object whose info will be inserted in the ostream
	 *
	 * @return	Reference to the ostream object, 'outstream', passed in the parameters
	 */
	friend std::ostream& operator<<(std::ostream& outstream, const Time &t);
	/**
	 * @brief	Overloaded ofstream insertion operator
	 *
	 * @details	Used to save information on a file so it can be read again at a later date
	 *
	 * @param outstream	Reference to the ofstream object to insert info to
	 * @param t		Reference to the Time object whose info will be inserted in the ofstream
	 *
	 * @return	Reference to the ofstream object, 'outstream', passed in the parameters
	 */
	friend std::ofstream& operator<<(std::ofstream& outstream, const Time &t);

	/* EXTRACTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded istream extraction operator
	 *
	 * @details	Mainly used with std::cin to get information from the user
	 *
	 * @param instream	Reference to the istream object to extract info from
	 * @param t		Reference to the Time object where the read information is saved
	 *
	 * @return	Reference to the istream object, 'instream', passed in the parameters
	 */
	friend std::istream& operator>>(std::istream &instream, Time &t);
	/**
	 * @brief	Overloaded ifstream extraction operator
	 *
	 * @details	Used to read information that has been saved to a file previously
	 *
	 * @param instream	Reference to the ifstream object to extract info from
	 * @param t		Reference to the Time object where the read information is saved
	 *
	 * @return	Reference to the ifstream object, 'instream', passed in the parameters
	 */
	friend std::ifstream& operator>>(std::ifstream &instream, Time &t);
};

/* COMPARISON OPERATOR OVERLOAD */
/** @relatesalso Time
 * @brief	Overloaded equality test operator
 *
 * @param lhs	Reference to one of the Time objects to be tested
 * @param rhs	Reference to one of the Time objects to be tested
 *
 * @return	true,  if the 2 Time objects have the same values for hours and minutes\n
 *		false, otherwise
 */
bool operator==(const Time& lhs, const Time& rhs);
/** @relatesalso Time
 * @brief	Overloaded inequality test operator
 *
 * @param lhs	Reference to one of the Time objects to be tested
 * @param rhs	Reference to one of the Time objects to be tested
 *
 * @return	false,  if the 2 Time objects have the same values for hours and minutes\n
 *		true, otherwise
 */
bool operator!=(const Time& lhs, const Time& rhs);

/** @relatesalso Time
 * @brief	Overloaded less than test operator
 *
 * @param lhs	Reference to the Time object to be tested as the smaller one
 * @param rhs	Reference to the Time object to be tested as the greater one
 *
 * @return	true,  if the time represent by the lhs Time object is a point earlier in the day, relative to the rhs Time object\n
 *		false, otherwise
 */
bool operator< (const Time& lhs, const Time& rhs);
/** @relatesalso Time
 * @brief	Overloaded less than or equal test operator
 *
 * @param lhs	Reference to the Time object to be tested as the smaller one
 * @param rhs	Reference to the Time object to be tested as the greater one
 *
 * @return	true,  if the time represent by the lhs Time object is a point earlier in the day, relative to the rhs Time object, or if they pass equality test\n
 *		false, otherwise
 */
bool operator<=(const Time& lhs, const Time& rhs);

/** @relatesalso Time
 * @brief	Overloaded less than test operator
 *
 * @param lhs	Reference to the Time object to be tested as the greater one
 * @param rhs	Reference to the Time object to be tested as the smaller one
 *
 * @return	true,  if the time represent by the lhs Time object is a point later in the day, relative to the rhs Time object\n
 *		false, otherwise
 */
bool operator> (const Time& lhs, const Time& rhs);
/** @relatesalso Time
 * @brief	Overloaded less than or equal test operator
 *
 * @param lhs	Reference to the Time object to be tested as the smaller one
 * @param rhs	Reference to the Time object to be tested as the greater one
 *
 * @return	true,  if the time represent by the lhs Time object is a point later in the day, relative to the rhs Time object, or if they pass equality test\n
 *		false, otherwise
 */
bool operator>=(const Time& lhs, const Time& rhs);

/* NON MEMBER FUNCTION */
/**
 * @brief	Calculate (and return) the difference (in minutes) between 2 points in time
 *
 * @param d_lhs	Reference to the Date object at left side of the interval
 * @param t_lhs	Reference to the Time object at left side of the interval
 * @param d_rhs	Reference to the Date object at right side of the interval
 * @param t_rhs	Reference to the Time object at right side of the interval
 *
 * @return	positive, if the second point in time given comes chronologically after the first one\n
		0, if the 2 points in time given are chronologically the same
		negative, if the first point in time given comes chronologically after the seconds one\n
 */
long timespan_size(const Date &d_lhs, const Time &t_lhs, const Date &d_rhs, const Time &t_rhs);

/** @} */

#endif  // TIME_H
