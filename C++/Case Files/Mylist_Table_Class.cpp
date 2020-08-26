#include "Mylist_Table_Class.h"
#include <qfont.h>
#include <qsortfilterproxymodel.h>
//#include "Picture_Mylist.h"

Mylist_Table_Class::Mylist_Table_Class(Service& service, QWidget* parent)
	: QWidget(parent), service{ service }
{
	ui.setupUi(this);
	QFont font("Thames", 14, 10, true);
	this->ui.tableView->setFont(font);
	this->ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	Table* tabel = new Table{ this->service };
	this->ui.tableView->setModel(tabel);
	ui.tableView->resizeColumnsToContents();
	ui.tableView->resizeRowsToContents();
	ui.tableView->verticalHeader()->hide();
}

Mylist_Table_Class::~Mylist_Table_Class()
{

}
