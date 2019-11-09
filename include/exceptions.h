#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>


class FileReadingFailed: public std::exception
{
	std::string fail_elem;
public:
	FileReadingFailed(std::string fail_elem) { this->fail_elem = fail_elem; }

	virtual const char* what() const noexcept
	{
		std::string what = "There was a problem reading the files: " + fail_elem;
		return what.c_str();
	}
};

class UserInputReadingFailure: public std::exception
{
	std::string fail_elem;
public:
	UserInputReadingFailure(std::string fail_elem) { this->fail_elem = fail_elem; }

	virtual const char* what() const noexcept
	{
		std::string what = "There was a problem reading the input from the user: " + fail_elem;
		return what.c_str();
	}
};


class TooEarlyToRenewCard: public std::exception
{
	std::string fail_elem;
public:
	TooEarlyToRenewCard(std::string fail_elem) { this->fail_elem = fail_elem; }

	virtual const char* what() const noexcept
	{
		std::string what = "It's too early to renew this card: " + fail_elem;
		return what.c_str();
	}
};


class InvalidTime: public std::exception
{
public:
	InvalidTime() = default;
	virtual const char* what() const noexcept
	{
		return "Time is out-of-bounds";
	}
};


class DuplicateEvent: public std::exception {
    std::string fail_elem;
public:
    DuplicateEvent(std::string fail_elem) { this->fail_elem = fail_elem; }

    virtual const char *what() const noexcept {
        std::string what = "This event has already been registered/bought: " + fail_elem;
        return what.c_str();
    }
};


class EventFull: public std::exception {
private:
    unsigned event_id;
public:
    EventFull(unsigned event_id) { this->event_id = event_id; };

    virtual const char* what() noexcept {
        std::string what = "Event with ID " + std::to_string(event_id) + " is full, it cannot be booked any more";
        return what.c_str();
    }
};

class EventNotFound: public std::exception {
private:
    unsigned event_id;
public:
    EventNotFound(unsigned event_id) { this->event_id = event_id; };

    virtual const char* what() noexcept {
        std::string what = "Event with ID " + std::to_string(event_id) + " was not found";
        return what.c_str();
    }
};

class EventAlreadyBought: public std::exception {
private:
    unsigned event_id, cc;
public:
    EventAlreadyBought(unsigned event_id, unsigned cc) { this->event_id = event_id; this->cc = cc; };

    virtual const char* what() noexcept {
        std::string what = "Event " + std::to_string(event_id) +
                " has already been bought by user with cc " + std::to_string(cc);
        return what.c_str();
    }
};

class MenuExitWithNoFunctionCall : public std::exception{
private:
	std::string title;
public:
	MenuExitWithNoFunctionCall(std::string t) : title(t) {};
    virtual const char* what() noexcept {
        std::string what = "Exited from menu " + title;
        return what.c_str();
    }
};

#endif  // EXCEPTION_H
