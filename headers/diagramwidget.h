#ifndef DIAGRAMWIDGET_H
#define DIAGRAMWIDGET_H

#include <QtCharts>
#include "storageitems.h"

/*
Данный класс представляет собою круговую диаграмму
которая на главном виджете отображает процентное соотношение
цен всех объектов класса Item
*/

class DiagramWidget : public QObject
{
    Q_OBJECT
private:

    QPieSlice *pPieSlice;
    QPieSeries *pPie;
    QChart *pChart;
    QChartView *pView;

public:

    DiagramWidget(QWidget *pwgt = 0);
    ~DiagramWidget();

    QChartView* getPChartView();

public slots:

    void slotUpdatePie(QVector<StorageItems*> vecOfStorageItems);
};

#endif // DIAGRAMWIDGET_H
