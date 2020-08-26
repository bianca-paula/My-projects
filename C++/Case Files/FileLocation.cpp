#include"FileLocation.h"
#include <qapplication.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <vector>
#include "Service.h"
#include <qmessagebox.h>

string FileLocation::LoadFileLocation()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "C:\Files", "TEXT files (*.txt) ;; Csv files (*.csv) ;; Html files (*.html)");
    if (!filename.isNull())
    {
        qDebug() << "Selected file path: " << filename.toUtf8();
    }
    return filename.toStdString();
}
