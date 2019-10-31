#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>
#include <fstream>
#include <istream>

// TODO: GET EVERYTHING TO USE EXCEPTIONS

namespace utl
{
	/**
	Returns true if all characters from string s are digits
	*/
	bool isNum(const std::string& s);

	/**
	Trims all whitespace from the right and left of string s
	*/
	void strTrim(std::string & s);

	/**
	Returns trrue if a given filestream is empty
	Meant to be used right after opening an ifstream
	*/
	bool isFileEmpty(std::ifstream & fin);

	/**
	Read a confirmation from user input (expects y/n answer)
	Presents msg + " (y/n) ? "
	If it return true, c will always "y" or "n" (lowercase)
	Return false if user interrupts with Ctrl+Z
	*/
	bool readConfirmation(char& c, std::string msg);

	/**
	Pauses the program's execution and waits for any user input
	Actual method for that may change in the future
	*/
	void pauseConsole();

	/**
	Clear the console... or somthing similar in effect
	Method may change in the future
	*/
	void clearConsole();

	/**
	Checks stream.eof() and stream.fail()
	When it returns false, a more detailed message is given in the error string
	*/
	bool checkStream(std::istream & stream, std::string & error);

	/**
	* Forces user to write an integer.
	* If a minimun or maximum number are given it forces the user to write an integer
	* between the given range [min, max] (inclusive).
	*/
	int getInt(std::istream &stream, int min=INT32_MIN, int max=INT32_MAX);

	/*
	 * ignore istream or ifstream 1000 chars or until '\n'
	 */
	inline void ignore(std::istream &i) { i.ignore(1000, '\n'); };
}

#endif //UTILITIES_H
