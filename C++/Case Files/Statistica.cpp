#include "Statistica.h"
#include <qfont.h>
#include <qsortfilterproxymodel.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
//#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


QT_CHARTS_USE_NAMESPACE

Statistica::Statistica(Service& service, QWidget* parent)
	: QWidget(parent), service{ service }
{
	ui.setupUi(this);
}

void Statistica::open_pie_chart()
{
    std::vector<Evidence>evidences{};
    evidences = this->service.getAllEvidences();


    QPieSeries* series = new QPieSeries();
    for (Evidence& evidence : evidences)
    {
        series->append(QString::fromStdString(evidence.get_Id()), evidence.get_Quantity());
    }
    QPieSlice* slice = new QPieSlice();
    for (size_t i = 0; i < evidences.size(); i++)
    {
        slice = series->slices().at(i);
        slice->setExploded();
        slice->setLabelVisible();
    }
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("The bar chart of evidences with corresponding quantity");
    chart->legend()->setVisible(false);
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow* window = new QMainWindow{ this };
    window->setCentralWidget(chartView);
    window->resize(500, 500);
    window->setWindowTitle("Statistic");
    window->show();
}

Statistica::~Statistica()
{
}
