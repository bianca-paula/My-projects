#pragma once
#include "Repository.h"
#include "Domain.h"
#include <string>
#include <vector>
using namespace std;

class FileRepository: public Repository{
private:
	std::vector<Evidence>evidences;
	void write_to_file(std::vector<Evidence>evidences);
	std::vector <Evidence> read_from_file();
	int position_of_the_current;
	std::vector<CaseFile> users{};
	std::vector<CaseFile> read_users_from_file();
public:
	string name_of_file;
public:
	FileRepository(const string& name_of_file);

	bool add_evidence(const Evidence& new_evidence);
	bool update_evidence(const Evidence& new_evidence);

	/*
	Returns all the evidences from the repository
	Parameters: -
	Output: a vector containing the evidences
*/
	std::vector<Evidence> getEvidences() { return read_from_file(); };
	int next_evidence_iterator();
	string getFileName() { return this->name_of_file; };
	bool delete_evidence(const Evidence& evidence);
	void setPath(const std::string& path);

	/*
	Returns all the case files in the repository
	Parameters: -
	Output: a vector containing the case files
*/
	std::vector<CaseFile> getUsers() { return read_users_from_file(); };
};