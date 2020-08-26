#pragma once

#include "UndoRedo.h"
#include "MyList.h"
#include "Repository.h"
#include "FilesRepository.h"
#include "Validation.h"
#include"UndoRedo.h"
#include "Observer.h"

class Service:public Subject
{
private:
	Repository& repository;
    MyList& my_list;

	vector<std::shared_ptr<ActionUndoRedo>> Undo;
	vector<std::shared_ptr<ActionUndoRedo>> Redo;



public:
	Service(Repository& repository, MyList& save_list): repository{repository},my_list{save_list}{}
	Repository& get_repository() { return repository; }
	string getFile() { return this->repository.getFileName(); };
	MyList& get_my_list() { return my_list; }
	void addEvidence(const std::string& id, const std::string& measurement, const float& imageClarity, const int& quantity, const std::string& photograph);
	std::vector<Evidence> getAllEvidences() const;
	void updateEvidence(const std::string& id, const std::string& measurement, const float& imageClarity, const int& quantity, const std::string& photograph);
	void deleteEvidence(const std::string& id);
	void saveEvidence(const std::string& id);
	Evidence nextEvidence() const;
	std::vector<Evidence> mylist() const;
	void open();
	void setFileLocation(const std::string& fileLocation);


	bool check_if_there_are_undos_left();
	bool check_if_there_are_redos_left();
	void undo();
	void redo();

	
	std::vector<CaseFile> get_users() const;
	std::vector<Evidence> get_fileEvidences(CaseFile c) const;
};

class RepositoryException : public std::exception {
private:
	std::string message;
public:
	RepositoryException(std::string message) : message(message) {}

	const char* what()
	{
		return message.c_str();
	}
};

