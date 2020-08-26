#include "Domain.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <sstream>
#include<stdlib.h>
#include<fstream>
#include<algorithm>



CaseFile::CaseFile(const std::string& caseReference, const std::vector<string> evidenceId)
{
	this->caseReference = caseReference;
	this->evidenceId = evidenceId;
}

std::string CaseFile::get_caseReference() const
{
	return this->caseReference;
}

std::vector<std::string> CaseFile::getEvidencesId() const
{
	return this->evidenceId;
}





std::string CaseFile::toString()
{
	std::string c;
	c += this->get_caseReference();
	for (auto e : this->evidenceId)
		c += ","+e;
	return c;


}

bool CaseFile::operator==(const CaseFile& user)
{
	return this->caseReference == user.get_caseReference();
}



Evidence::Evidence() :id(""), measurement(""), imageClarityLevel(), quantity(), photograph("") {}
Evidence::Evidence(const std::string& id, const std::string& measurement, const float& imageClarityLevel, const int& quantity, const std::string& photograph)
{
	this->id = id;
	this->measurement = measurement;
	this->imageClarityLevel = imageClarityLevel;
	this->quantity = quantity;
	this->photograph = photograph;
}
std::string Evidence::get_Id() const
{
	return this->id;
}

std::string Evidence::get_Measurement() const
{
	return this->measurement;
}

float Evidence::get_imageClarityLevel() const
{
	return this->imageClarityLevel;
}

int Evidence::get_Quantity() const
{
	return this->quantity;
}

std::string Evidence::get_Photograph() const
{
	return this->photograph;
}
void Evidence::set_Id(const std::string newId) {
	this->id = newId;
}
void Evidence::set_Measurement(const std::string newMeasurement)
{
	this->measurement = newMeasurement;
}
void Evidence::set_imageClarityLevel(const float newImageClarityLevel) {
	this->imageClarityLevel = newImageClarityLevel;
}
void Evidence::set_quantity(const int newQuantity) {
	this->quantity = newQuantity;
}
void Evidence::set_photograph(const std::string newPhotograph) {
	this->photograph = newPhotograph;
}
bool Evidence::operator==(const  Evidence& evidence)
{
	return this->id== evidence.get_Id(); 
}

std::string Evidence::toString()
{
	return this->get_Id() + "," + this->get_Measurement() + "," + std::to_string(this->get_imageClarityLevel()) + "," + std::to_string(this->get_Quantity()) + "," + this->get_Photograph();
}
std::vector<std::string> Split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	bool ok = false;
	while (std::getline(tokenStream, token, delimiter))
	{
		ok = true;
		tokens.push_back(token);
	}
	return tokens;
}

std::ostream& operator<<(std::ostream& outStream, Evidence& evidence) {
	outStream << evidence.get_Id() << "," << evidence.get_Measurement() << "," << evidence.get_imageClarityLevel() << ","
		<< evidence.get_Quantity() << "," << evidence.get_Photograph();
	return outStream;
}

std::istream& operator>>(std::istream& inStream, Evidence& evidence) {
	std::string id; std::string measurement; float imageClarityLevel; int quantity; std::string photograph; std::string line;

	//n >> line;

	getline(inStream, line);


	line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
	size_t position = line.find(",");
	id = line.substr(0, position);
	line.erase(0, position + 1);

	position = line.find(",");

	measurement = line.substr(0, position).c_str();
	line.erase(0, position + 1);

	position = line.find(",");

	imageClarityLevel = atof(line.substr(0, position).c_str());
	line.erase(0, position + 1);

	position = line.find(",");
	quantity = atoi(line.substr(0, position).c_str());
	line.erase(0, position + 1);

	photograph = line;

	evidence.set_Id(id); evidence.set_Measurement(measurement); evidence.set_imageClarityLevel(imageClarityLevel); evidence.set_quantity(quantity); evidence.set_photograph(photograph);

	

	return inStream;
}

std::ostream& operator<<(std::ostream& outStream, CaseFile& user)
{

	outStream << user.get_caseReference() << "," << user.toString();
	return outStream;
}

std::istream& operator>>(std::istream& inStream, CaseFile& user)
{
	std::vector<std::string> tokens;
	std::string line;
	std::vector<std::string> sad;

	getline(inStream, line);
	
	if (!line.empty()) {
		tokens = Split(line, ',');
		user.caseReference = tokens[0];
		for (int i = 1; i < tokens.size(); i++)
			sad.push_back(tokens[i]);
			//user.evidenceId.push_back(tokens[i]);
		user.set_evidenceId(sad);
	}


	return inStream;
}
