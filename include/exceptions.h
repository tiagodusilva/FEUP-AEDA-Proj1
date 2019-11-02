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


class DuplicatedEvent: public std::exception
{
	std::string fail_elem;
public:
	DuplicatedEvent(std::string fail_elem) { this->fail_elem = fail_elem; }

	virtual const char* what() const noexcept
	{
		std::string what = "This event has already been registered/bought: " + fail_elem;
		return what.c_str();
	}
};

#endif  // EXCEPTION_H
