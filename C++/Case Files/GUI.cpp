#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <vector>
#include <qmessagebox.h>
#include<qpalette.h>
#include<qlistwidget.h>
#include<qdialog.h>
using namespace std;
GUI::GUI(Service& service,QWidget *parent)
    : QMainWindow(parent), service{service}
{
    ui.setupUi(this);
    std::vector<CaseFile> all_users = service.get_users();
    for (int i = 0; i < all_users.size(); i++)
    {
        /*std::shared_ptr<Users> w = std::make_shared<Users>(service, all_users[i]);
        userWindows.push_back(w);*/
        //service.addObserver(w.get());

        CaseFiles* u = new CaseFiles{ this->service,all_users[i] };
        service.addObserver(u);
        elements.push_back(u);
    }
    this->populateProject();
    this->create_connections();
    this->populateSavedEvidences();


}

void GUI::populateProject()
{
    this->ui.evidencesListWidget->clear();
    this->ui.filterListWidget->clear();
    vector<Evidence> evidences = this->service.getAllEvidences();
    for (auto evidence : evidences)
        this->ui.evidencesListWidget->addItem(QString::fromStdString(evidence.get_Id() + "," + evidence.get_Measurement() + "," + to_string(evidence.get_imageClarityLevel()) + "," + to_string(evidence.get_Quantity()) + "," + evidence.get_Photograph()));
}

int GUI::get_selected_index(QListWidget* list)
{
    QModelIndexList selectedIndexes = list->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 0)
        return -1;
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void GUI::create_connections()
{
    QObject::connect(this->ui.evidencesListWidget,&QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->get_selected_index(this->ui.evidencesListWidget);
        if (selectedIndex < 0)
            return;
        Evidence evidence = this->service.getAllEvidences()[selectedIndex];
        this->ui.idLineEdit->setText(QString::fromStdString(evidence.get_Id()));
        this->ui.measurementLineEdit->setText(QString::fromStdString(evidence.get_Measurement()));
        this->ui.clarityLevelLineEdit->setText(QString::fromStdString(std::to_string(evidence.get_imageClarityLevel())));
        this->ui.quantityLineEdit->setText(QString::fromStdString(std::to_string(evidence.get_Quantity())));
        this->ui.photographLineEdit->setText(QString::fromStdString(evidence.get_Photograph()));
        });
    



    QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &GUI::addEvidence);
    QObject::connect(this->ui.deletePushButton, &QPushButton::clicked, this, &GUI::deleteEvidence);
    QObject::connect(this->ui.updatePushButton, &QPushButton::clicked, this, &GUI::updateEvidence);


    QObject::connect(this->ui.savePushButton, &QPushButton::clicked, this, &GUI::save);
    QObject::connect(this->ui.nextPushButton, &QPushButton::clicked, this, &GUI::next);
    QObject::connect(this->ui.openPushButton, &QPushButton::clicked, this, &GUI::open);
    QObject::connect(this->ui.filterPushButton, &QPushButton::clicked, this, &GUI::filter);

    QObject::connect(this->ui.mylistOpenpushButton, &QPushButton::clicked, this, &GUI::mylist_table_window);

    QObject::connect(this->ui.UndoPushButton, &QPushButton::clicked, this, &GUI::undo_operation);
    QObject::connect(this->ui.redoPushButton, &QPushButton::clicked, this, &GUI::redo_operation);
    QObject::connect(this->ui.listpushButton, &QPushButton::clicked, this, &GUI::populateProject);
    
    //QObject::connect(this->ui.user_pushButton, &QPushButton::clicked, this, &GUI::open_users);
    //QObject::connect(this->ui.exitAll_pushButton, &QPushButton::clicked, this, &GUI::exitAll);
    QObject::connect(ui.pie_chart_check_box, &QCheckBox::stateChanged, this, [this]() { checkBoxPieChart(); });
    QObject::connect(ui.seeUsers_checkBox, &QCheckBox::stateChanged, this, [this]() { checkBoxUsers(); });



}



void GUI::addEvidence()
{
    string id = this->ui.idLineEdit->text().toStdString();
    string measurement = this->ui.measurementLineEdit->text().toStdString();
    string imageClarity = this->ui.clarityLevelLineEdit->text().toStdString();
    string quantity = this->ui.quantityLineEdit->text().toStdString();
    string photograph = this->ui.photographLineEdit->text().toStdString();

    this->service.addEvidence(id, measurement, stof(imageClarity), stoi(quantity), photograph);
    this->populateProject();
    int lastElement = this->service.getAllEvidences().size() - 1;
    this->ui.evidencesListWidget->setCurrentRow(lastElement);
}

void GUI::deleteEvidence()
{
    int selectedIndex = this->get_selected_index(this->ui.evidencesListWidget);

    if (selectedIndex < 0) {
        return;
    }

    Evidence evidence = this->service.getAllEvidences()[selectedIndex];

    this->service.deleteEvidence(evidence.get_Id());

    this->populateProject();
}

void GUI::updateEvidence()
{
    string id = this->ui.idLineEdit->text().toStdString();
    string measurement = this->ui.measurementLineEdit->text().toStdString();
    string imageClarity = this->ui.clarityLevelLineEdit->text().toStdString();
    string quantity = this->ui.quantityLineEdit->text().toStdString();
    string photograph = this->ui.photographLineEdit->text().toStdString();

    this->service.updateEvidence(id, measurement, stof(imageClarity), stoi(quantity), photograph);
    this->populateProject();
    int lastElement = this->service.getAllEvidences().size() - 1;
}

void GUI::checkBoxPieChart()
{
    string fileN = this->service.getFile();
    Statistica* element = new Statistica{this->service};
    if (this->ui.pie_chart_check_box->isChecked())
        element->open_pie_chart();
    else
        element->close();
}

void GUI::populateSavedEvidences()
{
    this->ui.savedListWidget->clear();
    vector<Evidence> evidences = this->service.mylist();
    for (auto evidence : evidences)
        this->ui.savedListWidget->addItem(QString::fromStdString(evidence.get_Id() + "," + evidence.get_Measurement() + "," + to_string(evidence.get_imageClarityLevel()) + "," + to_string(evidence.get_Quantity()) + "," + evidence.get_Photograph()));
}

void GUI::save()
{
    int selectedIndex = this->get_selected_index(this->ui.evidencesListWidget);

    if (selectedIndex < 0) {
        return;
    }
    Evidence evidence = this->service.getAllEvidences()[selectedIndex];
    this->service.saveEvidence(evidence.get_Id());
    this->populateSavedEvidences();

}

void GUI::next()
{
    this->ui.nextListWidget->clear();
    Evidence evidence = this->service.nextEvidence();
    this->ui.nextListWidget->addItem(QString::fromStdString(evidence.get_Id() + "," + evidence.get_Measurement() + "," + to_string(evidence.get_imageClarityLevel()) + "," + to_string(evidence.get_Quantity()) + "," + evidence.get_Photograph()));
}

void GUI::open() {
    this->service.open();
}

void GUI::filter()
{
    this->ui.filterListWidget->clear();
    string measurement = this->ui.measurementFilterLineEdit->text().toStdString();
    string quantity = this->ui.quantityFilterLineEdit->text().toStdString();

    int quantityInt = stoi(quantity);

    vector<Evidence> evidences = this->service.getAllEvidences();

    for (Evidence evidence : evidences)
        if (evidence.get_Measurement() == measurement && evidence.get_Quantity() >= quantityInt)
            this->ui.filterListWidget->addItem(QString::fromStdString(evidence.get_Id() + "," + evidence.get_Measurement() + "," + to_string(evidence.get_imageClarityLevel()) + "," + to_string(evidence.get_Quantity()) + "," + evidence.get_Photograph()));


}

void GUI::mylist_table_window()
{
    Mylist_Table_Class* mylist_table = new Mylist_Table_Class{ this->service };
    mylist_table->show();

    
   
}

void GUI::checkBoxUsers()
{
    if (this->ui.seeUsers_checkBox->isChecked())
        for (auto elem : elements)
            elem->show();
    else
        for (auto elem : elements)
            elem->close();
        
}

std::vector<CaseFiles*> GUI::open_users()
{
    std::vector < CaseFiles*> userWindows;


    
    std::vector<CaseFile> all_users = service.get_users();
    for (int i = 0; i < all_users.size(); i++)
    {
        /*std::shared_ptr<Users> w = std::make_shared<Users>(service, all_users[i]);
        userWindows.push_back(w);*/
        //service.addObserver(w.get());

        CaseFiles* u = new CaseFiles{ this->service,all_users[i] };
        service.addObserver(u);
        userWindows.push_back(u);

        u->show();
    }
    //for (auto& item : userWindows)
    //{

    //    //item->show();

    //    item->setWindowModality(Qt::ApplicationModal);

    //    item->show();
    //    
    //    
    //}

    return userWindows;
}

void GUI::exitAll()
{
    std::vector < CaseFiles*> userWindows;
    userWindows = this->open_users();
    for (auto& item : userWindows)
        item->close();
}






void GUI::Undo()
{
    this->ui.evidencesListWidget->clear();
    if (this->service.check_if_there_are_undos_left())
    {
        QMessageBox::critical(this, "Error", "No more undos left!");
    }
    else
    {
        this->service.undo();
    }
    this->populateProject();
}

void GUI::Redo()
{
    this->ui.evidencesListWidget->clear();
    if (this->service.check_if_there_are_redos_left())
    {
        QMessageBox::critical(this, "Error", "No more redos left!");
    }
    else
    {
        this->service.redo();
    }
    this->populateProject();
}

void GUI::undo_operation()
{
    this->Undo();
}

void GUI::redo_operation()
{
    this->Redo();
}


