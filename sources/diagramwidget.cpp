#include "diagramwidget.h"

DiagramWidget::DiagramWidget(QWidget *pwgt) : QObject(pwgt)
{
    //инициализация диаграммы
    pPieSlice = new QPieSlice;
    pPie = new QPieSeries;
    pChart = new QChart();
    pView = new QChartView(pChart);

    pPie->setLabelsVisible(false);
    pChart->legend()->setVisible(false);

    //по умолчанию вся диаграмма черная
    pPie->append(" ", 1);
    pPie->slices().at(0)->setColor(Qt::black);

    pChart->setAnimationOptions(QChart::AllAnimations);
    pChart->addSeries(pPie);
    pChart->setTheme(QChart::ChartThemeDark);

    pView->setRenderHint(QPainter::Antialiasing);
    pView->resize(200,200);
}

QChartView* DiagramWidget::getPChartView()
{
    return pView;
}

void DiagramWidget::slotUpdatePie(QVector<StorageItems*> vecOfStorageItems)
{
    //сигнал присылается от объекта класса OutputItemWidget
    //по присланному вектору и отображается диаграмма
    //каждый раз диаграмма рисуется заново
    pPie->clear();
    if(vecOfStorageItems.isEmpty())
    {
        pPieSlice = new QPieSlice(" ", 0);
        pPieSlice->setColor(Qt::black);
        pPie->append(pPieSlice);
    }
    else
    {
        for(int i = 0; i < vecOfStorageItems.size(); i++)
        {
            pPieSlice = new QPieSlice(vecOfStorageItems[i]->nameCategory, vecOfStorageItems[i]->getSum());
            pPieSlice->setColor(vecOfStorageItems[i]->getColor());
            pPie->append(pPieSlice);
        }
    }
}

DiagramWidget::~DiagramWidget()
{
    pPieSlice->deleteLater();
    pPie->clear();
    pPie->deleteLater();
    pChart->removeAllSeries();
    pChart->deleteLater();
    pView->deleteLater();
}
