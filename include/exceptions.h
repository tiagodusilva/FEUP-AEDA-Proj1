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

class FileDoesntExist : public std::exception {
private:
	std::string file_name;
public:
	FileDoesntExist(std::string file) : file_name(file) {};

	virtual const char* what() noexcept {
		std::string what = "File with name " + file_name +
			"does not exist";
		return what.c_str();
	}
};

class FileAlreadyExists : public std::exception {
private:
	std::string file_name;
public:
	FileAlreadyExists(std::string file) : file_name(file) {};

	virtual const char* what() noexcept {
		std::string what = "File with name " + file_name +
			"already exists";
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


class CardAlreadyExists : public std::exception {
private:
	unsigned cc;
public:
	CardAlreadyExists(unsigned cc) { this->cc = cc; };

	virtual const char* what() noexcept {
		std::string what = "There is already an user with cc number " + std::to_string(cc) +
			" in the network";
		return what.c_str();
	}
};

class NoSuchCard : public std::exception {
private:
	unsigned cc;
public:
	NoSuchCard(unsigned cc) { this->cc = cc; };

	virtual const char* what() noexcept {
		std::string what = "There isn't any user with cc number " + std::to_string(cc) +
			" in the network";
		return what.c_str();
	}
};

class EnterpriseAlreadyExists : public std::exception {
private:
	std::string name;
public:
	EnterpriseAlreadyExists(std::string name) { this->name = name; };

	virtual const char* what() noexcept {
		std::string what = "There is already an enterprise with name " + name +
			" in the network";
		return what.c_str();
	}
};

class NoSuchEnterprise : public std::exception {
private:
	std::string name;
public:
	NoSuchEnterprise(std::string name) { this->name = name; };

	virtual const char* what() noexcept {
		std::string what = "There isn't any enterprise with name " + name +
			" in the network";
		return what.c_str();
	}
};

class MuseumAlreadyExists : public std::exception {
private:
	std::string name;
public:
	MuseumAlreadyExists(std::string name) { this->name = name; };

	virtual const char* what() noexcept {
		std::string what = "There is already a museum with name " + name +
			" in the network";
		return what.c_str();
	}
};

class NoSuchMuseum : public std::exception {
private:
	std::string name;
public:
	NoSuchMuseum(std::string name) { this->name = name; };

	virtual const char* what() noexcept {
		std::string what = "There isn't any museum with name " + name +
			" in the network";
		return what.c_str();
	}
};
//TODO Do this exception but for museums and enterprises

#endif  // EXCEPTION_H
