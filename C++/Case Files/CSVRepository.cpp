#include "CSVRepository.h"
#include "Domain.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <Windows.h>
#include <ShellApi.h>

CSVRepository::CSVRepository (const std::string& path)
{
	this->CSV_filename = path;
}
bool CSVRepository::save_evidence(const Evidence& evidence)
{
	std::vector<Evidence> saved_evidences = this->read_from_file();
	std::vector<Evidence>::iterator iterate = find(saved_evidences.begin(), saved_evidences.end(), evidence);
	if (iterate == saved_evidences.end())
	{
		saved_evidences.push_back(evidence);

		this->write_to_file(saved_evidences);
		return true;
	}
	return false;
}
void CSVRepository::write_to_file(vector<Evidence> saved_evidences)
{
	std::ofstream fout(CSV_filename);
	for (auto evidence :saved_evidences)
	{
		fout << evidence<<endl;
	}
	fout.close();
}
void CSVRepository::Set_path(const string& path)
{
	this->CSV_filename = path;
}
vector<Evidence> CSVRepository::read_from_file()
{
	vector<Evidence> saved_evidences;
	std::ifstream input_file(this->CSV_filename);
	Evidence evidence;
	while (input_file >> evidence)
	{
		saved_evidences.push_back(evidence);
	}
	input_file.close();
	return saved_evidences;
}

std::vector<Evidence> CSVRepository::getEvidences()
{
	std::vector<Evidence> saved_evidences = read_from_file();
	return saved_evidences;
}

void CSVRepository::open()
{
	std::string path= this->CSV_filename;
	system(path.c_str());
	return;
}
