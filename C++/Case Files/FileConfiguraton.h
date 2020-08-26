#pragma once
#include <string>
#include <qwidget.h>

using std::string;
class FileConfiguration : public QWidget
{
public:
	string LoadRepoType();
};