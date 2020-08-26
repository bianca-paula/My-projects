#include "FilesRepository.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
FileRepository::FileRepository(const std::string& name_of_file) {
	this->name_of_file = name_of_file;
	this->position_of_the_current = 0;
}
std::vector <Evidence> FileRepository::read_from_file()
{
	std::vector<Evidence>evidences{};
	Evidence evidence;
	std::ifstream fin(this->name_of_file);
	while (fin >> evidence)
	{
		evidences.push_back(evidence);
	}
	fin.close();
	return evidences;
}

std::vector<CaseFile> FileRepository::read_users_from_file()
{
	std::vector<CaseFile>users{};
	CaseFile user;
	std::ifstream fin("users.txt");
	while (fin >> user)
	{
		users.push_back(user);
	}
	fin.close();
	return users;
}

void FileRepository::write_to_file(std::vector<Evidence>evidences)
{
	std::ofstream out;
	out.open(name_of_file, std::ofstream::out | std::ofstream::trunc);
	out.close();
	std::ofstream fout(name_of_file);
	for (auto& evidence : evidences)
		fout << evidence << endl;
	fout.close();
}

/*
	Adds a new evidence to the repository
	Parameters: new_evidence - the evidence to be added
	Output: false - if the evidence already exists and it cannot be added, true otherwise
*/
bool FileRepository::add_evidence(const Evidence& new_evidence)
{
	std::vector<Evidence> evidences = this->read_from_file();
	std::vector<Evidence>::iterator iterate = find(evidences.begin(), evidences.end(), new_evidence);
	if (iterate == evidences.end())
	{
		evidences.push_back(new_evidence);
		this->write_to_file(evidences);
		return true;
	}
	return false;
}

/*
	Returns an iterator for the next evidence in the evidence repository
	Parameters: -
	Output: the position on which the next evidence is
*/
int FileRepository::next_evidence_iterator()
{
	std::vector<Evidence> evidences = this->read_from_file();
	if (this->position_of_the_current == evidences.size())
		this->position_of_the_current = 0;
	return this->position_of_the_current++;
}


/*
	Updates an already existing evidence from the repository
	Parameters: new_evidence - the new details of the evidence
	Output: false - if the evidence does not exist and it cannot be updated, true otherwise
*/
bool FileRepository::update_evidence(const Evidence& new_evidence)
{
	int ok = 0;
	std::vector<Evidence> evidences = this->read_from_file();
	if (evidences.empty())
	{
		return false;
	}
	std::vector<Evidence>::iterator iterate = find(evidences.begin(), evidences.end(), new_evidence);
	if (iterate != evidences.end())
	{
		*iterate = new_evidence;
		ok = 1;
	}
	this->write_to_file(evidences);
	if (ok == 1)
		return true;
	return false;
}

/*
	Deletes an already existing evidence from the repository
	Parameters: evidence -the evidence to be deleted
	Output: false - if the evidence does not exist and it cannot be deleted, true otherwise
*/
bool  FileRepository::delete_evidence(const Evidence& evidence)
{
	std::vector<Evidence> evidences = this->read_from_file();
	if (evidences.empty())
	{
		return false;
	}
	auto iterate = std::find(evidences.begin(), evidences.end(), evidence);
	if (iterate != evidences.end())
	{
		evidences.erase(iterate);
		this->write_to_file(evidences);
		return true;
	}
	return false;
}

void FileRepository::setPath(const std::string& path)
{
	this->name_of_file = path;
}