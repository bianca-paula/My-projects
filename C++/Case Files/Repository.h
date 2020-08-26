#pragma once
#include "Domain.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Repository {
private:
	std::vector<Evidence>evidences{};
	std::vector<CaseFile> users{};
public:
	Repository() {}
	/*
		Adds a new evidence to the repository
		Parameters: new_evidence - the evidence to be added
		Output: false - if the evidence already exists and it cannot be added, true otherwise
	*/
	virtual bool add_evidence(const Evidence& new_evidence)=0;

	/*
		Updates an already existing evidence from the repository
		Parameters: new_evidence - the new details of the evidence
		Output: false - if the evidence does not exist and it cannot be updated, true otherwise
	*/
	virtual bool update_evidence(const Evidence& new_evidence)=0;

	/*
		Returns all the evidences from the repository
		Parameters: -
		Output: a vector containing the evidences
	*/
	virtual std::vector<Evidence> getEvidences()=0;

	/*
		Returns all the case files in the repository
		Parameters: -
		Output: a vector containing the case files
	*/
	virtual std::vector<CaseFile> getUsers() = 0;

	virtual string getFileName() = 0;

	/*
		Returns an iterator for the next evidence in the evidence repository
		Parameters: -
		Output: the position on which the next evidence is 
	*/
	virtual int next_evidence_iterator()=0;

	/*
		Deletes an already existing evidence from the repository
		Parameters: evidence -the evidence to be deleted
		Output: false - if the evidence does not exist and it cannot be deleted, true otherwise
	*/
	virtual bool delete_evidence(const Evidence& evidence)=0;
};