#pragma once
#include <iostream>
#include<vector>
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <sstream>
#include<stdlib.h>
#include<fstream>
#include<algorithm>

using namespace std;
class Evidence
{
private:
	std::string id;
	std::string measurement;
	float imageClarityLevel;
	int quantity;
	std::string photograph;

public:
	Evidence();
	Evidence(const std::string& id, const std::string& measurement, const float& imageClarityLevel, const int& quantity, const std::string& photograph);
	std::string get_Id() const;
	std::string get_Measurement() const;
	float get_imageClarityLevel() const;
	int get_Quantity() const;
	std::string get_Photograph() const;
	bool operator==(const Evidence& evidence);
	void set_Id(const std::string newId);
	void set_Measurement(const std::string newMeasurement);
	void set_imageClarityLevel(const float newImageClarityLevel);
	void set_quantity(const int newQuantity);
	void set_photograph(const std::string newPhotograph);

	std::string toString();
	friend std::ostream& operator<<(std::ostream& outStream, Evidence& evidence);
	friend std::istream& operator>>(std::istream& inStream, Evidence& evidence);
};

class CaseFile {
private:
	std::string caseReference;
	std::vector<std::string> evidenceId{};

public:
	CaseFile() {}
	CaseFile(const std::string& caseReference, const std::vector<string> evidenceId);
	
	

	std::string get_caseReference() const;
	std::vector<std::string> getEvidencesId() const;
	
	friend std::ostream& operator<<(std::ostream& outStream, CaseFile& user);
	friend std::istream& operator>>(std::istream& inStream, CaseFile& user);
	bool operator==(const CaseFile& user);
	std::string toString();
	void set_caseReference(const std::string& caseReference) { this->caseReference = caseReference; };
	void set_evidenceId(const std::vector<std::string> evidenceId) { this->evidenceId = evidenceId; };


};