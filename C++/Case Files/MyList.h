#pragma once
#include "Domain.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class MyList{
private:
	std::string path_of_file;
	virtual vector<Evidence> read_from_file() = 0;
	virtual void write_to_file(std::vector<Evidence> saved_evidences) = 0;
public:
	MyList() {}
	virtual bool save_evidence(const Evidence& new_evidence) = 0;
	virtual std::vector<Evidence> getEvidences() = 0;
	virtual void Set_path(const string& path) = 0;
	virtual void open()=0;
};