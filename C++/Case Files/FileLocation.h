#pragma once
#include <string>
#include <qwidget.h>

using std::string;
class FileLocation : public QWidget
{
public:
	string LoadFileLocation();
};