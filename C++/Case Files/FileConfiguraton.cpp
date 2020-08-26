#include "FileConfiguraton.h"
#include <qapplication.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include "Service.h"
#include <qmessagebox.h>
string FileConfiguration::LoadRepoType()
{

    QString filename = QFileDialog::getOpenFileName(this, "Open Configuration File", "C:\Files", "TEXT files (*.txt) ;; Csv files (*.csv) ;; Html files (*.html)");
    if (!filename.isNull())
    {
        qDebug() << "Selected file path: " << filename.toUtf8();
    }
    ifstream file_in;
    file_in.open(filename.toStdString());
    string type;
    file_in >> type;
    file_in.close();
    return type;
}
