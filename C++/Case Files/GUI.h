#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include <qwidget.h>
#include"Service.h"
//#include "QWidgetsClass.h"
//#include <qlistwidget.h>
//#include <qlineedit.h>
//#include <qpushbutton.h>
#include "Domain.h"
#include "CaseFiles.h"
#include<cstring>
#include<vector>
//#include "PieChart_Class.h"
#include "Statistica.h"
#include "Mylist_Table_Class.h"


class GUI : public QMainWindow
{
    Q_OBJECT
        

public:
    GUI(Service& service,QWidget *parent = Q_NULLPTR);

private:
    Ui::GUIClass ui;
    Service& service;
    void populateProject();
    int get_selected_index(QListWidget* list);
    void create_connections();
    void addEvidence();
    void deleteEvidence();
    void updateEvidence();
    void checkBoxPieChart();
    void populateSavedEvidences();
    void save();
    void next();
    void open();
    void filter();

    void Undo();
    void Redo();
    void undo_operation();
    void redo_operation();

    std::vector<CaseFiles*> open_users();
    std::vector<CaseFiles*> elements;

    void mylist_table_window();
    void checkBoxUsers();
    void exitAll();

 
    
    
};
