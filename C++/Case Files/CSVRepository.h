#pragma once
#include "MyList.h"
#include "Domain.h"
#include <string>
#include <vector>

class CSVRepository :public MyList {
private:
	std::string CSV_filename;
public:
	CSVRepository(const string& path);
	void Set_path(const string& path)override;
	bool save_evidence(const Evidence& evidence)override;
	void write_to_file(vector<Evidence> saved_evidences) override;
	vector<Evidence> read_from_file() override;
	std::vector<Evidence> getEvidences()override;
	void open()override;
};