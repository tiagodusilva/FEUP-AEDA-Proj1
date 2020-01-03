/** @file exceptions.h */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

/** @defgroup exc_grp Custom exceptions */

/** @addtogroup	exc_grp
  *
  * @brief	Exception objects defined for use in out project workflow (runtime_error inheritance)
  *
  * @{
  */

/* MISCELLANEOUS EXCEPTIONS */

/** @brief	Thrown when there was a user input (usually through std::cin) failure */
class UserInputReadingFailure: public std::runtime_error {
public:
	UserInputReadingFailure(const std::string & fail_elem) :
	    std::runtime_error("There was a problem reading the input from the user: " + fail_elem) {};
};


/* MENU RELATED EXCEPTIONS */

/** @brief	Thrown when the called menu has no function to call */
class MenuExitWithNoFunctionCall : public std::runtime_error{
public:
	MenuExitWithNoFunctionCall(const std::string & title) :
	    std::runtime_error("Exited from menu " + title) {};
};

/** @brief	Thrown by a menu to forcefully kill itself */
class MenuForceExit : public std::runtime_error{
public:
	MenuForceExit(const std::string & title) :
	    std::runtime_error("Exited from menu " + title) {};
};


/* FILE RELATED EXCEPTIONS */

/** @brief	Thrown when a file was not found */
class FileNotFound : public std::runtime_error {
public:
	FileNotFound(const std::string & file_name) :
	    std::runtime_error("File with name " + file_name + " not found") {};
};

/** @brief	Thrown when there was a reading failure from a file */
class FileReadingFailed: public std::runtime_error {
public:
	FileReadingFailed(std::string fail_elem) :
	    std::runtime_error("There was a problem reading the files: " + fail_elem) {};
};


/* CARD RELATED EXCEPTIONS */

/** @brief	Thrown when a user attemps to renew a card too early */
class TooEarlyToRenewCard: public std::runtime_error {
public:
	TooEarlyToRenewCard(const std::string & fail_elem) :
	    std::runtime_error("It's too early to renew this card: " + fail_elem) {};
};

/** @brief	Thrown when a user attempts to use the benefits of his Card while it is expired */
class CardExpired : public std::runtime_error {
public:
	CardExpired(unsigned cc) :
		std::runtime_error("The current accout with cc " + std::to_string(cc) + " and as such can't buy events") {};
};


/* NETWORK RELATED EXCEPTIONS */

/** @brief	Thrown when the instance of an Object is malformed */
class InvalidObject: public std::runtime_error {
public:
    InvalidObject(const std::string &object, const std::string &reason) :
	std::runtime_error(object + "Object is invalid: " + reason) {};
};

/** @brief	Thrown when attempting to instantiate a duplicate of an Object that can't have duplicates */
class ObjectAlreadyExists : public std::runtime_error {
public:
	ObjectAlreadyExists(const std::string &unique_id, const std::string &object) :
	    std::runtime_error("There already is a(n) " + object + " with unique identifier " + unique_id + " in the network") {};
};

/** @brief	Thrown when the Object we're attempting to find can't be found anywhere */
class NoSuchObject : public std::runtime_error {
public:
    NoSuchObject(const std::string &unique_id, const std::string &object) :
	std::runtime_error("There isn't any " + object + " Object with unique identifier(s) " + unique_id) {};
};

/** @} */

#endif	// EXCEPTION_H
