#include "Table.h"
#include <qfont.h>
#include <qbrush.h>

Table::Table(Service& service, QObject* parent) : QAbstractTableModel{ parent }, service{ service }
{
}

int Table::rowCount(const QModelIndex& parent) const
{
	int totalRows = this->service.mylist().size();
	return totalRows + 1;
}

int Table::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant Table::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	std::vector<Evidence> all_evidences = this->service.mylist();

	if (row == all_evidences.size())
		return QVariant();

	Evidence evidence = all_evidences[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(evidence.get_Id());
		case 1:
			return QString::fromStdString(evidence.get_Measurement());
		case 2:
			return QString::fromStdString(to_string(evidence.get_imageClarityLevel()));
		case 3:
			return QString::fromStdString(to_string(evidence.get_Quantity()));
		case 4:
			return QString::fromStdString(evidence.get_Photograph());
		default:
			break;
		}
	}

	if (role == Qt::FontRole)
	{
		QFont font("Arial", 14, 10, true);
		font.setItalic(false);
		return font;
	}

	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			return QBrush{ QColor{ 0, 250, 154 } };
		}
	}

	return QVariant{};
}

QVariant Table::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Id" };
			case 1:
				return QString{ "Measurement" };
			case 2:
				return QString{ "ImageClarity" };
			case 3:
				return QString{ "Quantity" };
			case 4:
				return QString{ "Photograph" };
			default:
				break;
			}
		}
	}

	if (role == Qt::FontRole)
	{
		QFont font("Arial", 12, 10, true);
		font.setBold(true);
		font.setItalic(false);
		return font;
	}

	if (role == Qt::BackgroundRole)
	{
		return QBrush{ QColor{ 0, 180, 154 } };
	}

	return QVariant{};
}


Table::~Table() {}
