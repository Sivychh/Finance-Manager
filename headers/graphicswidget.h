#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QtCharts>
#include "storageitems.h"

/*
Данный класс представляет собою виджет в котором
отображаются столбчатые диаграммы всех категорий трат
за 2025 год
*/

class GraphicsWidget : public QWidget
{
    Q_OBJECT
private:

    QBarSet *pBarSet;
    QBarCategoryAxis *pCategoryAxisX;
    QStringList monthsOfYear //изначально были полные названия месяцев, после сократил
    {
        "01.2025", "02.2025", "03.2025",
        "04.2025", "05.2025", "06.2025",
        "09.2025", "08.2025", "09.2025",
        "10.2025", "11.2025", "12.2025"
    };

    QValueAxis *pValueAxisY;
    QBarSeries *pBarSeries;
    QChart *pChart;
    QChartView *pView;
    QVBoxLayout *pVBox;

public:

    GraphicsWidget(QVector<StorageItems*> vec, QWidget *pwgt = 0);
    ~GraphicsWidget();

    QScrollArea *pScrollArea;
};

#endif // GRAPHICSWIDGET_H
