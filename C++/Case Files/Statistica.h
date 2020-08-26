#pragma once

#include <QWidget>
#include "ui_Statistica.h"
#include "Service.h"
#include "Table.h"

class Statistica : public QWidget
{
	Q_OBJECT

public:
	Statistica(Service& service, QWidget* parent = Q_NULLPTR);
	void open_pie_chart();
	~Statistica();

private:
	Service& service;
	Ui::Statistica ui;
};
