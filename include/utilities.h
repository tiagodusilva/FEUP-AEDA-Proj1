#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <sys/stat.h>

// TODO: GET EVERYTHING TO USE EXCEPTIONS

namespace utl
{
    #define CLEAR_CONSOLE_NEW_LINES 150

	/**
	Returns true if all characters from string s are digits
	*/
	bool isNum(const std::string& s);

	/**
	Return a string with all whitespace from the right and left trimmed
	*/
    std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

    /**
    Return a string with all whitespace from the right and left trimmed
    */
    std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

    /**
    Return a string with all whitespace from the right and left trimmed
    */
    std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

	/**
	 * Check if a given string can be considered an empty string
	*/
	bool isStrEmpty(std::string str);
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
	int getInt(std::istream &stream, int min=INT32_MIN, int max=INT32_MAX, const std::string &message="");

	/*
	 * ignore istream or ifstream 1000 chars or until '\n'
	 */
	inline void ignore(std::istream &i) { i.ignore(1000, '\n'); };

	/*
	 * Checks if a given file exists;
	 * Takes a string specifing the path to the file to check as an argument;
	 * Returns true in case the file exists and false in case the files doesn't exist;
	 * Source: https://stackoverflow.com/a/12774387
	*/
	bool file_exists(const std::string& name);
}

#endif //UTILITIES_H
