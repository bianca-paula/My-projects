#include "HTMLRepository.h"
#include "Domain.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <Windows.h>
#include <ShellApi.h>
#define Garbage_lines 5

HTMLRepository::HTMLRepository(const std::string& path)
{
	this->HTML_filename = path;
}
bool HTMLRepository::save_evidence(const Evidence& evidence)
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
void HTMLRepository::write_to_file(vector<Evidence> saved_evidences)
{
	std::string content_of_file = "";
	content_of_file += "<!DOCTYPE hr=tml>\n";
	content_of_file += "<html>\n";
	content_of_file += "\t<head>\n";
	content_of_file += "\t\t<title>My List</title>\n";
	content_of_file += "\t</head>\n";
	content_of_file += "\t<body>\n";
	content_of_file += "\t\t<table border=\"1\">\n";
	content_of_file += "\t\t<tr>\n";
	content_of_file += "\t\t\t<td>Id</td>\n";
	content_of_file += "\t\t\t<td>Measurement</td>\n";
	content_of_file += "\t\t\t<td>imageClarity</td>\n";
	content_of_file += "\t\t\t<td>Quantity</td>\n";
	content_of_file += "\t\t\t<td>Photograph</td>\n";
	content_of_file += "\t\t</tr>\n";
	for (auto evidence : saved_evidences)
	{
		content_of_file += "\t\t<tr>\n";
		content_of_file += "\t\t\t<td>" + evidence.get_Id() + "</td>\n";
		content_of_file += "\t\t\t<td>" + evidence.get_Measurement() + "</td>\n";
		content_of_file += "\t\t\t<td>" + std::to_string(evidence.get_imageClarityLevel()) + "</td>\n";
		content_of_file += "\t\t\t<td>" + std::to_string(evidence.get_Quantity()) + "</td>\n";
		content_of_file += "\t\t\t<td>" + evidence.get_Photograph() + "</td>\n";
		content_of_file += "\t\t</tr>\n";
	}
	content_of_file += "\t\t</table>\n";
	content_of_file += "\t</body>\n";
	content_of_file += "</html>\n";

	std::ofstream file_out(this->HTML_filename);
	file_out << content_of_file;
	file_out.close();
}
void HTMLRepository::Set_path(const string& path)
{
	this->HTML_filename = path;
}
vector<Evidence> HTMLRepository::read_from_file()
{
	vector<Evidence> saved_evidences;
	std::ifstream input_file(this->HTML_filename);
	Evidence evidence;
	int unused_lines = Garbage_lines;
	std::string line_from_file;
	std::string id, measurement, imageClarity, quantity, photograph;
	while (getline(input_file, line_from_file))
	{
		if (line_from_file.substr(0, 7) == "\t\t\t<td>")
		{
			if (unused_lines)
				unused_lines--;
			else
			{
				int first_position = line_from_file.find('>') + 1;
				id = line_from_file.substr(first_position, line_from_file.rfind('<') - first_position);
				getline(input_file, line_from_file);
				measurement = line_from_file.substr(first_position, line_from_file.rfind('<') - first_position);
				getline(input_file, line_from_file);
				imageClarity = line_from_file.substr(first_position, line_from_file.rfind('<') - first_position);
				getline(input_file, line_from_file);
				quantity = line_from_file.substr(first_position, line_from_file.rfind('<') - first_position);
				getline(input_file, line_from_file);
				photograph = line_from_file.substr(first_position, line_from_file.rfind('<') - first_position);
				evidence = Evidence(id, measurement, stof(imageClarity), stoi(quantity), photograph);
				saved_evidences.push_back(evidence);
			}
		}
	}
	input_file.close();
	return saved_evidences;
}

std::vector<Evidence> HTMLRepository::getEvidences()
{
	std::vector<Evidence> saved_evidences = this->read_from_file();
	return saved_evidences;
}
void HTMLRepository::open()
{
	std::string path = this->HTML_filename;
	system(path.c_str());
}
