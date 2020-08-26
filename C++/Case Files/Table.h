#pragma once
#include "Service.h"
#include <qabstractitemmodel.h>

class Table : public QAbstractTableModel
{

private:
	Service& service;

public:
	Table(Service& service, QObject* parent = NULL);
	~Table();

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

};

