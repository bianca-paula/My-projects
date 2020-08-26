#include "Validation.h"
#include <algorithm>
#include <cctype>
#include <string>

bool Validator::String_is_empty(const std::string& string_parameter)
{
	return string_parameter.size() == 0;
}


std::string Validator::Validate_string(const std::string& string_parameter)
{
	if (!Validator::String_is_empty(string_parameter))
		return string_parameter;
	throw ValidationException("String cannot be empty");
}

void Validator::isEvidenceValid(Evidence& evidence)
{
	std::string exceptions = "";
	if (evidence.get_Id() == "")
		exceptions += "Id is not valid! ";
	if (evidence.get_Measurement() == "")
		exceptions += "Measurement is not valid! ";
	if (evidence.get_Quantity() < 0)
		exceptions += "Quantity is not valid! ";
	if (evidence.get_Photograph() == "")
		exceptions += "Photograph is not valid! ";
	if (exceptions != "")
		throw ValidationException(exceptions);
}
