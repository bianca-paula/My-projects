#include "MemoryRepository.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
MemoryRepository::MemoryRepository() {
	this->position_of_the_current = 0;
}
bool MemoryRepository::add_evidence(const Evidence& new_evidence)
{
	std::vector<Evidence>::iterator iterate = find(evidences.begin(), evidences.end(), new_evidence);
	if (iterate == evidences.end())
	{
		evidences.push_back(new_evidence);
		return true;
	}
	return false;
}
int MemoryRepository::next_evidence_iterator()
{
	if (this->position_of_the_current == evidences.size())
		this->position_of_the_current = 0;
	return this->position_of_the_current++;
}
/*
This function gets the the index of the new_turret element and calls the dynamic array for update the element found at that index
*/
bool MemoryRepository::update_evidence(const Evidence& new_evidence)
{
	if (evidences.empty())
	{
		return false;
	}
	std::vector<Evidence>::iterator iterate = find(evidences.begin(), evidences.end(), new_evidence);
	if (iterate != evidences.end())
	{
		*iterate = new_evidence;
		return true;
	}
	return false;
}
/*
This function gets the the index of the turret and calls the dynamic array for delete the element found at that index
*/
bool  MemoryRepository::delete_evidence(const Evidence& evidence)
{
	if (evidences.empty())
	{
		return false;
	}
	auto iterate = std::find(evidences.begin(), evidences.end(), evidence);
	if (iterate != evidences.end())
	{
		evidences.erase(iterate);
		return true;
	}
	return false;
}
