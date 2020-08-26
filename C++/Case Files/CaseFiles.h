#pragma once
#include "Service.h"
#include<QWidget>
#include "ui_CaseFiles.h"
#include "Observer.h"
#include<qmodelindex>
#include "Domain.h"



class CaseFiles : public QWidget, public Observer
{
	Q_OBJECT

public:
	CaseFiles(Service& service, CaseFile user, QWidget* parent = Q_NULLPTR);
	~CaseFiles();

private:
	Ui::CaseFiles ui;
	Service& service;
	CaseFile user;
	void update() override;
	int get_selected_index() const;
	void populate_list();
	void make_connection();

public:
	void exit_function();

};
