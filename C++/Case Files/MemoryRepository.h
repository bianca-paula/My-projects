#pragma once
#include "Repository.h"
#include "Domain.h"
#include <string>
#include <vector>
#include "FilesRepository.h"
#include "Mylist.h"
using namespace std;

class MemoryRepository : public Repository
{
private:
	std::vector<Evidence> evidences;
	std::vector<CaseFile> users;
	int position_of_the_current;
public:
	MemoryRepository();
	bool add_evidence(const Evidence& new_evidence);
	bool update_evidence(const Evidence& new_evidence);
	std::vector<Evidence> getEvidences() { return evidences; };
	int next_evidence_iterator();
	bool delete_evidence(const Evidence& evidence);
	std::vector<CaseFile> getUsers() {
		return users;
	};
	string getFileName() override { return ""; };
	friend class FilesRepository;
};

