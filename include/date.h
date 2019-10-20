#ifndef __DATE_H__
#define __DATE_H__

#include <ctime>
#include <iostream>
#include <fstream>

class Date
{
public:
    /**
        Defaults Date to Epoch (1970/01/01)
    */
    Date();

    /**
    WARNING: Does not check if created Date is valid!
    */
    Date(short aYear, short aMonth, short aDay);

    /**
        If the string is in a wrong format, it will set Date to an invalid state
        (y = 0, m = 0, d = 0)
        isValid will be false if the string was poorly constructed or if the Date read was invalid
    */
    Date(const std::string& s, bool & isValid);

    // GETTERS

    short getDay() const;
    short getMonth() const;
    short getYear() const;

    // OTHER PUBLIC METHODS

    /**
        Returns a Date object with the current system date
        May only work in visual studio, requires additional testing
    */
    Date now();

    /**
        Reads a Date from user input
        Guarentees a valid Date (returns true)
        Ctrl + Z to abort input (returns false)
    */
    bool readUserInput();

    /**
        Reads a Date from file
        Returns false if the Date is invalid
        Also reeturns false if ifstrean.eof() or ifstream.fail() are detected
    */
    bool readFromFile(std::ifstream& file, unsigned int& lineTracker, std::string & error);

    /**
        Returns true if it's a leap year
    */
    bool isLeapYear() const;

    /**
        Returns true if the Date object is valid
        Checks days in months, month belonging [1, 12] and leap years
    */
    bool isValid() const;

    bool operator< (const Date& d) const;
    bool operator>= (const Date& d) const;
    bool operator> (const Date& d) const;
    bool operator<= (const Date& d) const;
    bool operator== (const Date& d) const;
    bool operator!= (const Date& d) const;

private:
    short day, month, year;
};

std::ostream& operator<< (std::ostream& stream, const Date& date);

#endif  // __DATE_H__
