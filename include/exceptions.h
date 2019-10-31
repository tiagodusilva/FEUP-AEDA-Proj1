#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class FileReadingFailed: public std::exception
{
	std::string failed_file;
public:
	FileReadingFailed(std::string failed_file) { this->failed_file = failed_file; }

	virtual const char* what() const throw()
	{
		return "There was a problem reading the files";
	}

	std::string show() const { return this->failed_file; }
};

#endif  // EXCEPTION_H
