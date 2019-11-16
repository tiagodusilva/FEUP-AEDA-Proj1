/** @file exceptions.h */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

/** @defgroup exc_grp Custom exception module */

/** @addtogroup	exc_grp
  *
  * @brief	Exception objects defined for use in out project workflow (runtime_error inheritance)
  *
  * @{
  */

/* Miscellaneous Exceptions */

class UserInputReadingFailure: public std::runtime_error {
public:
	UserInputReadingFailure(const std::string & fail_elem) :
	    std::runtime_error("There was a problem reading the input from the user: " + fail_elem) {};
};


class InvalidTime: public std::runtime_error {
public:
	InvalidTime() :
	    std::runtime_error("Time is out-of-bounds") {};
};

class InvalidAddress: public std::runtime_error {
public:
	InvalidAddress() :
	    std::runtime_error("Zip code is invalid") {};
};



/* Menu related exceptions */

class MenuExitWithNoFunctionCall : public std::runtime_error{
public:
	MenuExitWithNoFunctionCall(const std::string & title) :
	    std::runtime_error("Exited from menu " + title) {};
};

class MenuForceExit : public std::runtime_error{
public:
	MenuForceExit(const std::string & title) :
	    std::runtime_error("Exited from menu " + title) {};
};



/* File related Exceptions */

class FileNotFound : public std::runtime_error {
public:
	FileNotFound(const std::string & file_name) :
	    std::runtime_error("File with name " + file_name + " not found") {};
};

class FileReadingFailed: public std::runtime_error {
public:
	FileReadingFailed(std::string fail_elem) :
	    std::runtime_error("There was a problem reading the files: " + fail_elem) {};
};



/* Event related exceptions */

class EventFull: public std::runtime_error {
public:
    EventFull(unsigned event_id) :
        std::runtime_error("Event with ID " + std::to_string(event_id) + " is full, it cannot be booked any more") {};
};

class EventInvalid: public std::runtime_error {
public:
    EventInvalid(unsigned event_id) :
		std::runtime_error("Event with ID " + std::to_string(event_id) + " is in an invalid state") {};
};

class EventAlreadyBought: public std::runtime_error {
public:
    EventAlreadyBought(unsigned event_id, unsigned cc):
        std::runtime_error( "Event " + std::to_string(event_id) + " has already been bought by user with cc " + std::to_string(cc)) {};
};



/* Card related Exceptions */

class TooEarlyToRenewCard: public std::runtime_error {
public:
	TooEarlyToRenewCard(const std::string & fail_elem) :
	    std::runtime_error("It's too early to renew this card: " + fail_elem) {};
};

class CardExpired : public std::runtime_error {
public:
	CardExpired(unsigned cc) :
		std::runtime_error("The current accout with cc " + std::to_string(cc) + " and as such can't buy events") {};
};



/* Network related Exceptions */

class ObjectAlreadyExists : public std::runtime_error {
public:
	ObjectAlreadyExists(const std::string &unique_id, const std::string &object) :
	    std::runtime_error("There already is a(n) " + object + " with unique identifier " + unique_id + " in the network") {};
};

class NoSuchObject : public std::runtime_error {
public:
    NoSuchObject(const std::string &unique_id, const std::string &object) :
        std::runtime_error("There isn't any " + object + " with unique identifier " + unique_id) {};
};

/** @} */

#endif  // EXCEPTION_H
