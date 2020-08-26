#include "CaseFiles.h"
#include <vector>
#include "qmessagebox.h"
#include <exception>

CaseFiles::CaseFiles(Service& service, CaseFile user, QWidget* parent)
	: QWidget(parent), service{ service }, user{ user }
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(user.get_caseReference()));
	this->ui.userLineEdit->setText(QString::fromStdString(user.get_caseReference()));
	this->make_connection();
	this->populate_list();
}

CaseFiles::~CaseFiles()
{
}

void CaseFiles::update()
{
	this->populate_list();
}

int CaseFiles::get_selected_index() const
{
	QModelIndexList selectedIndexes = this->ui.evidencesListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{

		return -1;
	}
	int SelectedIndex = selectedIndexes.at(0).row();
	return SelectedIndex;
}
void CaseFiles::populate_list()
{
	this->ui.evidencesListWidget->clear();
	//std::vector<Evidence> evidences = this->service.getAllEvidences();
	//for (auto evidence : evidences)
	//{
	//	if(evidence.get_Id()==user.get_evidenceId())
	//		this->ui.evidencesListWidget->addItem(QString::fromStdString(evidence.toString()));
	//}
	std::vector<Evidence> evidences = this->service.get_fileEvidences(user);
	std::vector<std::string> ev = user.getEvidencesId();
	//this->ui.evidencesListWidget->addItem(QString::fromStdString(std::to_string(ev.size())));
	for (auto evidence : evidences)
		this->ui.evidencesListWidget->addItem(QString::fromStdString(evidence.toString()));

	//this->ui.evidencesListWidget->addItem(QString::fromStdString(user.toString()));


}



void CaseFiles::make_connection()
{
	//QObject::connect(this->ui.exit_pushButton, &QPushButton::clicked, this, &CaseFiles::exit_function);
}

void CaseFiles::exit_function()
{
	this->close();
}
