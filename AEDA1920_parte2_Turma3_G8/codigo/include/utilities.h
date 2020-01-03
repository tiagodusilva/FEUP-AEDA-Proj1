/** @file utilities.h */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <sys/stat.h>
#include <tuple>

/** @brief	General utility functions */
namespace utl {
/** @brief	Number of new line characters, '\\n', when trying to clear the
 * screen */
#define CLEAR_CONSOLE_NEW_LINES 80

/**
 * @brief	Checks if a given string is a valid number
 *
 * @param s	String to check
 *
 * @returns	true, if all characters of the given string, 's', are digits\n
 *		false, otherwise
 */
bool isNum(const std::string& s);

/**
 * @brief	Trim given string of empty/transparent characters from the left
 * end
 *
 * @param str	Reference to the string to be trimmed
 * @param chars	String containing the characters to match for trimming (default:
 * "\\t\\n\\v\\f\\r ")
 *
 * @returns	The given string with all empty characters from the left end
 * trimmed
 */
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

/**
 * @brief	Trim given string of empty/transparent characters from the right
 * end
 *
 * @param str	Reference to the string to be trimmed
 * @param chars	String containing the characters to match for trimming (default:
 * "\\t\\n\\v\\f\\r ")
 *
 * @returns	The given string with all empty characters from the right end
 * trimmed
 */
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

/**
 * @brief	Trim given string of empty/transparent characters from both ends
 *
 * @param str	Reference to the string to be trimmed
 * @param chars	String containing the characters to match for trimming (default:
 * "\\t\\n\\v\\f\\r ")
 *
 * @returns	The given string with all empty characters from both ends
 * trimmed
 */
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

/**
 * @brief	Check if a given string can be considered an empty string
 *
 * @param str	Copy of the string to test
 *
 * @return	true, if the string only contains empty/invisible characters
 *("\\t\\n\\v\\f\\r")\n false, otherwise
 */
bool isStrEmpty(std::string str);

/**
 * @brief	Check if a given filestream is empty
 *
 * @note	Meant to be used right after opening an ifstream
 *
 * @param fin	File instream to check
 *
 * @returns	true, if the given ifstream is empty\n
 *		false, otherwise
 */
bool isFileEmpty(std::ifstream& fin);

/**
 * @brief	Read a confirmation from user input
 *
 * @note	Expects y/n answer (lowercase). If the return is true, 'c' will
 *contain either 'y' or 'n' (lowercase)
 *
 * @details	Presents msg + " (y/n) ? "
 *
 * @param c	Char read from the user input
 * @param msg	Message to present to the user
 *
 * @returns	false, if user interrupts with Ctrl+Z\n
 *		true, otherwise
 */
bool readConfirmation(char& c, std::string msg);

/**
 * @brief	Pauses the program's execution and waits for any user input
 * @note	Actual method for that may change in the future
 */
void pauseConsole();

/**
 * @brief	Clear the console by printing new line characters, '\\n'
 * @note	Method may change in the future
 */
void clearConsole();

/**
 * @brief	Checks stream.eof() and stream.fail()
 * @note	When it returns false, a more detailed message is given in the
 *error string
 *
 * @param stream	Reference to the stream to check
 * @param error		Reference to the error string to print (in case of EOF
 *or fail)
 *
 * @returns	false, when stream reached EOF or the failbit is set\n
 *		true, otherwise
 */
bool checkStream(std::istream& stream, std::string& error);

/**
 * @brief	Forces the user to write an integer.
 *
 * @details	If a minimum or maximum number are given it forces the user to
 *write an integer\n between the given range [min, max] (inclusive)
 *
 * @param stream	'istream' to read the user input from
 * @param min		Optional minimum value the user has to input (default:
 *INT32_MIN)
 * @param max		Optional maximum value the user has to input (default:
 *INT32_MAX)
 * @param message	Optional message to write before waiting for the user
 *input (default: "")
 */
int getInt(std::istream& stream,
           int min                    = INT32_MIN,
           int max                    = INT32_MAX,
           const std::string& message = "");

/**
 * @brief	Call the ignore method on a given 'istream' 1000 chars or until
 * '\n'
 * @param i	Stream to call the ignore method on
 */
inline void
ignore(std::istream& i)
{
  i.ignore(1000, '\n');
};

/**
 * @brief	Clear the failbit and ignore all characters from a given
 * 'istream'
 * @param i	Stream to clear
 */
inline void
stream_clear(std::istream& i)
{
  i.clear();
  i.ignore();
};

/**
 * @brief	Checks if a given file exists
 * @note	Source: https://stackoverflow.com/a/12774387
 *
 * @param name	String speciffing the path to the file to check
 *
 * @returns	true, in case the file exists
 *		false, otherwise
 */
bool file_exists(const std::string& name);

/**
 * @brief Calculates the distance between 2 points.
 *
 * @param c1  Tuple representing the first point coordinates.
 * @param c2  Tuple representing the second point coordinates.
 *
 * @return  The distance between the 2 points.
 */
float coord_dist(const std::tuple<float, float>& c1,
                 const std::tuple<float, float>& c2);

} // namespace utl

#endif // UTILITIES_H
