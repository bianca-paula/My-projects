#pragma once

#include <QWidget>
#include "ui_Mylist_Table_Class.h"
#include "Service.h"
#include "Table.h"

class Mylist_Table_Class : public QWidget
{
	Q_OBJECT

public:
	Mylist_Table_Class(Service& service, QWidget* parent = Q_NULLPTR);
	~Mylist_Table_Class();

private:
	Service& service;
	Ui::Mylist_Table_Class ui;
};
