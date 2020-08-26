#include <vector>
#include <algorithm>
#include "Service.h"


std::vector<Evidence> Service::getAllEvidences()const
{
	return repository.getEvidences();
}
void Service::open()
{
	my_list.open();
}

void Service::addEvidence(const std::string& id, const std::string& measurement, const float& imageClarity, const int& quantity, const std::string& photograph)
{
	Evidence evidence_to_add{ id, measurement, imageClarity,quantity,photograph };
	bool check_success =repository.add_evidence(evidence_to_add);
	if(check_success==false)
		throw RepositoryException("Cannot add evidence!");
	else
	{
		Undo.push_back(std::make_shared<UndoRedo_Add>(repository, evidence_to_add));
		Redo.clear();
	}
	this->notify();
}

void Service::updateEvidence(const std::string& id, const std::string& measurement, const float& imageClarity, const int& quantity, const std::string& photograph)
{
	vector<Evidence> all_evidences = repository.getEvidences();
	Evidence evidence_to_update{ id, measurement, imageClarity,quantity,photograph };
	Evidence evidence_before_update;
	for (Evidence& evidence : all_evidences)
	{
		if (evidence == evidence_to_update)
		{
			evidence_before_update = evidence;
			break;
		}
	}

	bool check_success = repository.update_evidence(evidence_to_update);
	if (check_success == false)
		throw RepositoryException("Cannot update evidence!");

	else {
		Undo.push_back(std::make_shared<UndoRedo_Update>(repository, evidence_before_update, evidence_to_update));
		Redo.clear();
	}
	this->notify();
}

void Service::deleteEvidence(const std::string& id)
{
	Evidence evidence_to_delete{ id,"",0,0,"" };
	vector<Evidence> all_evidences = repository.getEvidences();
	Evidence evidence_for_undo;
	for (Evidence& evidence : all_evidences)
	{
		if (evidence == evidence_to_delete)
		{
			evidence_for_undo = evidence;
			break;
		}
	}

	bool check_success = repository.delete_evidence(evidence_to_delete);
	if (check_success == false)
		throw RepositoryException("Cannot delete evidence!");
	else
	{
		Undo.push_back(std::make_shared<UndoRedo_Delete>(repository, evidence_for_undo));
		Redo.clear();
	}
	this->notify();
}
Evidence Service::nextEvidence()const
{
	int current_index = repository.next_evidence_iterator();
	std::vector<Evidence> allEvidences = repository.getEvidences();
	Evidence current_evidence = { "","",0,0,"" };
	for (size_t i = 0; i < allEvidences.size(); i++)
	{
		if (i == current_index)
			current_evidence = allEvidences.at(i);
	}
	return current_evidence;
}
std::vector<Evidence> Service::mylist()const {
	return my_list.getEvidences();
}

void Service::saveEvidence(const std::string& id)
{
	std::vector<Evidence> allEvidences = repository.getEvidences();
	Evidence evidence = { id,"",0,0,"" };
	auto iterator = std::find(allEvidences.begin(), allEvidences.end(), evidence);
	if (iterator != allEvidences.end())
	{
		auto index = std::distance(allEvidences.begin(), iterator);
		const Evidence evidence_to_save = allEvidences.at(index);
		bool truth_value = my_list.save_evidence(evidence_to_save);
		if (truth_value == false)
			throw RepositoryException("Evidence already saved! ");
	}
	else {
		throw RepositoryException("The given evidence does not exist! ");
	}
	//this->notify();
}

void Service::setFileLocation(const std::string& fileLocation)
{
	//this->repository.setPath(fileLocation);
}

bool Service::check_if_there_are_undos_left()
{
	if (Undo.empty())
		return true;
	return false;
}

bool Service::check_if_there_are_redos_left()
{
	if (Redo.empty())
		return true;
	return false;
}

void Service::undo()
{

	if (Undo.empty())
		return;
	auto action = std::move(Undo.back());
	Undo.pop_back();
	action->Undo();
	Redo.push_back(std::move(action));
	this->notify();
}

void Service::redo()
{
	if (Redo.empty())
		return;
	auto action = std::move(Redo.back());
	Redo.pop_back();
	action->Redo();
	Undo.push_back(std::move(action));
	this->notify();
}

std::vector<CaseFile> Service::get_users() const
{
	return repository.getUsers();
}

std::vector<Evidence> Service::get_fileEvidences(CaseFile c) const
{
	std::vector<Evidence> evidences=this->getAllEvidences();
	std::vector<std::string> evidencesId;
	evidencesId = c.getEvidencesId();
	std::vector<Evidence> FileEvidences;
	for (auto e : evidencesId)
		for (auto ev : evidences)
			if (e == ev.get_Id())
			{
				FileEvidences.push_back(ev);
				
			}

	return FileEvidences;
}
