#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>


class FileReadingFailed: public std::runtime_error {
public:
	FileReadingFailed(std::string fail_elem) :
	    std::runtime_error("There was a problem reading the files: " + fail_elem) {};
};

class UserInputReadingFailure: public std::runtime_error {
public:
	UserInputReadingFailure(const std::string & fail_elem) :
	    std::runtime_error("There was a problem reading the input from the user: " + fail_elem) {};
};

class TooEarlyToRenewCard: public std::runtime_error {
public:
	TooEarlyToRenewCard(const std::string & fail_elem) :
	    std::runtime_error("It's too early to renew this card: " + fail_elem) {};
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

class EventFull: public std::runtime_error {
public:
    EventFull(unsigned event_id) :
        std::runtime_error("Event with ID " + std::to_string(event_id) + " is full, it cannot be booked any more") {};
};

class EventNotFound: public std::runtime_error {
public:
    EventNotFound(unsigned event_id) :
		std::runtime_error("Event with ID " + std::to_string(event_id) + " was not found") {};
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

class FileDoesntExist : public std::runtime_error {
public:
	FileDoesntExist(const std::string & file_name) :
	    std::runtime_error("File with name " + file_name + "does not exist") {};
};

class FileAlreadyExists : public std::runtime_error {
public:
	FileAlreadyExists(const std::string & file_name) :
	    std::runtime_error("File with name " + file_name + "already exists") {};
};

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

class CardAlreadyExists : public std::runtime_error {
public:
	CardAlreadyExists(unsigned cc) :
	    std::runtime_error("There already is an user with cc number " + std::to_string(cc) + " in the network") {};
};

class CardExpired : public std::runtime_error {
public:
	CardExpired(unsigned cc) :
		std::runtime_error("The current accout with cc " + std::to_string(cc) + " and as such can't buy events") {};
};

class NoSuchCard : public std::runtime_error {
public:
	NoSuchCard(unsigned cc) :
	    std::runtime_error("There isn't any user with cc number " + std::to_string(cc) + " in the network") {};
};

class EnterpriseAlreadyExists : public std::runtime_error {
public:
	EnterpriseAlreadyExists(const std::string & name) :
	    std::runtime_error("There already is an enterprise with the name " + name + " in the network") {};
};

class NoSuchEnterprise : public std::runtime_error {
public:
    NoSuchEnterprise(const std::string &name) :
        std::runtime_error("There isn't any enterprise with the name " + name + "in the network") {};
};

class MuseumAlreadyExists : public std::runtime_error {
public:
	MuseumAlreadyExists(const std::string & name) :
	    std::runtime_error("There already is a museum with the name " + name + "in the network") {};
};

class NoSuchMuseum : public std::runtime_error {
public:
	NoSuchMuseum(const std::string & name) :
	    std::runtime_error("There isn't any museum with name " + name + " in the network") {};
};

class FileNotFound : public std::runtime_error {
public:
	FileNotFound(const std::string & file_name) :
	    std::runtime_error("File with name " + file_name + " not found") {};
};

class FileIncorrectFormatting : public std::runtime_error {
public:
	FileIncorrectFormatting(const std::string & file_name) :
	    std::runtime_error("File with name " + file_name + " is formatted incorrectly") {};
};

class MultipleEventsSelected : public std::runtime_error {
public:
	MultipleEventsSelected(const std::string &num_events) :
		std::runtime_error(num_events + " events selected instead of 1") {};
};

#endif  // EXCEPTION_H
