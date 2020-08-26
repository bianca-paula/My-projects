#pragma once
#include <exception>
#include <string>
#include "Domain.h"
class Validator {
public:
	/*
		Checks if a string is empty or not
		Parameters: s - string
		Output: bool - True if it is empty, false otherwise
	*/
	static bool String_is_empty(const std::string& string_parameter);
	static std::string Validate_string(const std::string& string_parameter);
	static void isEvidenceValid(Evidence& evidence);
};


class ValidationException : public std::exception {
private:
	std::string message;
public:
	ValidationException(std::string message) : message(message) {}

	const char* what()
	{
		return message.c_str();
	}
};