/** @file date.h */
#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <fstream>
#include <iostream>


/** @addtogroup	datetime_grp
  *
  * @{
  */


/** @brief	the number of seconds in a day (60 secs * 60 mins * 24 hours) */
#define SECONDS_IN_DAY 86400

/** @brief	the number of seconds in a min (60 seconds) */
#define SECS_IN_MIN 60

/** @brief	the number of minutes in an hour (60 minutes) */
#define MIN_IN_HOUR 60

/**
 * @brief	Class that saves and handles date information in our project
 *
 * @details	This class is a wrapper for 'ctime'. It tries to fix any mistake given to the constructor instead of throwing exceptions\n
 *		(e.g.: 32nd of January, 2010 is corrected to 1st of February, 2010)\n
 *		This class only saves and handles information relative to: day, month, year, leap-years and weekday
 */
class Date
{
private:
	/** @brief	integer type that stores the number of seconds since the Epoch */
	time_t date_int;
	/** @brief	struct that stores the translated date info (year, month, day, etc...) */
	tm date_tm;

	/** @brief	syncs information in the 'date_tm' data member to the 'date_int' data member */
	bool syncmembers();

public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor of the class Date
	 *
	 * @details	Creates a Date object that contains information about the current system date
	 */
	Date();
	/**
	 * @brief	Constructor for the class Date that that takes a 'ctime' time_t
	 *
	 * @details	This constructor is mainly used to read date information from files since it also sets\n
	 *		information relating to time of the day to some default values for Date class comparisons
	 *
	 * @param date_int	'ctime' time_t that represents all the information in a Date object
	 */
	Date(time_t date_int);
	/**
	 * @brief	Normal constructor for the class Date
	 *
	 * @details	Creates a Date object with the give year, month and day information.\n
	 *		Does not warn user if the created Date is valid (tries to automatically fix inputed mistakes)
	 *
	 * @param year	representing the date's year
	 * @param month	representing the date's month
	 * @param day	representing the date's day
	 */
	Date(short year, short month, short day);

	/* GETTERS */
	/**
	 * @brief	Getter for the saved day information
	 *
	 * @return	date's day information currently saved in the class object
	 */
	int get_day() const;
	/**
	 * @brief	Getter for the saved month information
	 *
	 * @return	date's month information currently saved in the class object
	 */
	int get_month() const;
	/**
	 * @brief	Getter for the saved year information
	 *
	 * @return	date's year information currently saved in the class object
	 */
	int get_year() const;
	/**
	 * @brief	Getter for the weekday information
	 *
	 * @return	date's weekday given the information currently saved in the class object\n
	 *		[1, 7] <=> [Sunday, Saturday]
	 */
	int get_weekday() const;
	/**
	 * @brief	Getter for the 'ctime' time_t saved in the class
	 *
	 * @return	'ctime' time_t that represents all the information currently saved in the class object
	 */
	time_t get_raw() const;

	/* OTHER MEMBER FUNCTIONS */
	/**
	 * @brief	Checks if the current Date object represents a leap year
	 *
	 * @return	true, if the current year represented by the Date object is a leap year\n
	 *		false, otherwise
	 */
	bool isLeapYear() const;

	/**
	 * @brief	Get the number of days between 2 Date objects
	 *
	 * @param b	The Date object that will be used for calculations with the current Date object
	 *
	 * @return	The number of days between 2 Date objects. Always a positive number (or 0)
	 */
	unsigned int diffdays(const Date &b) const;

	/**
	 * @brief	Fast-forwards the current Date object an x amount of years
	 *
	 * @details	Takes care of error correction (e.g.: for the default parameter, 29th of February, 2004 becomes 01st of March, 2005)
	 *
	 * @param years	The number of years to fast-forward (default = 1)
	 */
	void ffyear(short years=1);

	/**
	 * @brief	Fast-forwards the current Date object an x amount of months
	 *
	 * @details	Takes care of error correction (e.g.: for the default parameter, 31st of March, 2004 becomes 01st of May, 2004)
	 *
	 * @param months	The number of months to fast-forward (default = 1)
	 */
	void ffmonth(short months=1);

	/**
	 * @brief	Fast-forwards the current Date object an x amount of days
	 *
	 * @details	Takes care of error correction (e.g.: for the default parameter, 31st of January, 2004 becomes 01st of February, 2004)
	 *
	 * @param days	The number of days to fast-forward (default = 1)
	 */
	void ffday(short days=1);

	/**
	 * @brief	Subtraction operator overload
	 *
	 * @details	This is a wrapper for the 'diffdays' member-function
	 *
	 * @param b	The Date object that will be used for calculations with the current Date object
	 *
	 * @return	The number of days between 2 Date objects. Always a positive number (or 0)
	 */
	unsigned int operator-(const Date &b);

	/* EXTRACTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded istream extraction operator
	 *
	 * @details	Mainly used with std::cin to get information from the user
	 *
	 * @param instream	Reference to the istream object to extract info from
	 * @param d		Reference to the Date object where the read information is saved
	 *
	 * @return	Reference to the istream object, 'instream', passed in the parameters
	 */
	friend std::istream& operator>>(std::istream &instream, Date &d);
};

/* COMPARISON OPERATOR OVERLOAD */
/** @relatesalso Date
 * @brief	Overloaded equality test operator
 *
 * @param lhs	Reference to one of the Date objects to be tested
 * @param rhs	Reference to one of the Date objects to be tested
 *
 * @return	true,  if the 2 Date objects have equal values for their 'ctime' time_t varible\n
 *		false, otherwise
 */
bool operator==(const Date& lhs, const Date& rhs);
/** @relatesalso Date
 * @brief	Overloaded inequality test operator
 *
 * @param lhs	Reference to one of the Date objects to be tested
 * @param rhs	Reference to one of the Date objects to be tested
 *
 * @return	true,  if the 2 Date objects have different values for their 'ctime' time_t varible\n
 *		false, otherwise
 */
bool operator!=(const Date& lhs, const Date& rhs);

/** @relatesalso Date
 * @brief	Overloaded less than test operator
 *
 * @param lhs	Reference to the Date object to be tested as the smaller one
 * @param rhs	Reference to the Date object to be tested as the greater
 *
 * @return	true, if lhs' 'ctime' time_t varible evaluates as less than rhs' one\n
 *		false, otherwise
 */
bool operator< (const Date& lhs, const Date& rhs);
/** @relatesalso Date
 * @brief	Overloaded less than or equal test operator
 *
 * @param lhs	Reference to the Date object to be tested as the smaller one
 * @param rhs	Reference to the Date object to be tested as the greater
 *
 * @return	true, if lhs' 'ctime' time_t varible evaluates as less than or equal to rhs' one\n
 *		false, otherwise
 */
bool operator<=(const Date& lhs, const Date& rhs);

/** @relatesalso Date
 * @brief	Overloaded greater than test operator
 *
 * @param lhs	Reference to the Date object to be tested as the greater one
 * @param rhs	Reference to the Date object to be tested as the smaller one
 *
 * @return	true, if lhs' 'ctime' time_t varible evaluates as greater than rhs' one\n
 *		false, otherwise
 */
bool operator> (const Date& lhs, const Date& rhs);
/** @relatesalso Date
 * @brief	Overloaded greater than or equal test operator
 *
 * @param lhs	Reference to the Date object to be tested as the greater one
 * @param rhs	Reference to the Date object to be tested as the smaller one
 *
 * @return	true, if lhs' 'ctime' time_t varible evaluates as greater than or equal to rhs' one\n
 *		false, otherwise
 */
bool operator>=(const Date& lhs, const Date& rhs);

/* INSERTION OPERATOR OVERLOAD */
/** @relatesalso Date
 * @brief	Overloaded ostream insertion operator
 *
 * @details	Mainly used with std::cout to show formated information on screen
 *
 * @param outstream	Reference to the ostream object to insert info to
 * @param d		Reference to the Date object whose info will be inserted in the ostream
 *
 * @return	Reference to the ostream object, 'outstream', passed in the parameters
 */
std::ostream& operator<<(std::ostream& outstream, const Date &d);
/** @relatesalso Date
 * @brief	Overloaded ofstream insertion operator
 *
 * @details	Used to save information on a file so it can be read again at a later date
 *
 * @param outstream	Reference to the ofstream object to insert info to
 * @param d		Reference to the Date object whose info will be inserted in the ofstream
 *
 * @return	Reference to the ofstream object, 'outstream', passed in the parameters
 */
std::ofstream& operator<<(std::ofstream& outstream, const Date &d);

/* EXTRACTION OPERATOR OVERLOAD */
/** @relatesalso Date
 * @brief	Overloaded ifstream extraction operator
 *
 * @details	Used to read information that has been saved to a file previously
 *
 * @param instream	Reference to the ifstream object to extract info from
 * @param d		Reference to the Date object where the read information is saved
 *
 * @return	Reference to the ifstream object, 'instream', passed in the parameters
 */
std::ifstream& operator>>(std::ifstream &instream, Date &d);

/** @} */

#endif  // DATE_H
