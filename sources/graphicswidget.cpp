#include "graphicswidget.h"

GraphicsWidget::GraphicsWidget(QVector<StorageItems*> vec, QWidget *pwgt) : QWidget(pwgt)
{
    //здесь отображается первая диаграмма в которой собраны все категории и все траты
    pScrollArea = new QScrollArea;
    pBarSeries = new QBarSeries(this);
    pBarSet = new QBarSet("", this);
    for(int j = 0; j < vec.size(); j++)
    {
        pBarSet = new QBarSet(vec[j]->nameCategory, this);
        pBarSet->setColor(vec[j]->getColor());

        for(int y = 0; y < 12; y++)
        {
            //изначально вся диаграмма пустая
            pBarSet->append(0);
        }

        for(int i = 0; i < vec[j]->vecOfItems.size(); i++)
        {
            //уже здесь пустые ячейки диаграммы заменяются в соответствии с общими тратами конкретной категории
            pBarSet->replace(vec[j]->vecOfItems[i]->getDate().month() - 1,
                             pBarSet->at(vec[j]->vecOfItems[i]->getDate().month() - 1)
                                 + vec[j]->vecOfItems[i]->getPrice());
        }

        pBarSeries->append(pBarSet);
    }

    pChart = new QChart();
    pChart->addSeries(pBarSeries);
    pChart->setAnimationOptions(QChart::AllAnimations);

    pCategoryAxisX = new QBarCategoryAxis(this);
    pCategoryAxisX->append(monthsOfYear);
    pChart->addAxis(pCategoryAxisX, Qt::AlignBottom);
    pBarSeries->attachAxis(pCategoryAxisX);

    pValueAxisY = new QValueAxis(this);
    pValueAxisY->setRange(0, 500);
    pValueAxisY->setTickInterval(100);
    pChart->addAxis(pValueAxisY, Qt::AlignLeft);
    pBarSeries->attachAxis(pValueAxisY);

    pView = new QChartView(pChart, this);
    pView->setRenderHint(QPainter::Antialiasing);
    pView->setMinimumSize(520,400);

    pVBox = new QVBoxLayout;
    pVBox->addWidget(pView);

    //тут происходит тоже самое что и прежде, только диаграмма создается не по всем категориям сразу
    //а по одной категории со своей отдельной диаграммой
    for(int i = 0; i < vec.size(); i++)
    {
        pBarSeries = new QBarSeries(this);

        pBarSet = new QBarSet(vec[i]->nameCategory, this);
        pBarSet->setColor(vec[i]->getColor());

        for(int y = 0; y < 12; y++)
        {
            pBarSet->append(0);
        }

        for(int j = 0; j < vec[i]->vecOfItems.size(); j++)
        {
            pBarSet->replace(vec[i]->vecOfItems[j]->getDate().month() - 1,
                             pBarSet->at(vec[i]->vecOfItems[j]->getDate().month() - 1)
                                 + vec[i]->vecOfItems[j]->getPrice());

            pBarSeries->append(pBarSet);
        }

        pChart = new QChart();
        pChart->addSeries(pBarSeries);
        pChart->setAnimationOptions(QChart::AllAnimations);

        pCategoryAxisX = new QBarCategoryAxis(this);
        pCategoryAxisX->append(monthsOfYear);
        pChart->addAxis(pCategoryAxisX, Qt::AlignBottom);
        pBarSeries->attachAxis(pCategoryAxisX);

        pValueAxisY = new QValueAxis(this);
        pValueAxisY->setRange(0, 500);
        pValueAxisY->setTickInterval(100);
        pChart->addAxis(pValueAxisY, Qt::AlignLeft);
        pBarSeries->attachAxis(pValueAxisY);

        pView = new QChartView(pChart, this);
        pView->setRenderHint(QPainter::Antialiasing);
        pView->setMinimumSize(520,400);

        pVBox->addWidget(pView);
    }

    setLayout(pVBox);
    pScrollArea->setWidgetResizable(true);
    pScrollArea->setWidget(this);
}

GraphicsWidget::~GraphicsWidget()
{
    delete pBarSet;
    pBarSeries->deleteLater();
    delete pCategoryAxisX;
    delete pValueAxisY;
    pChart->removeAllSeries();
    pChart->deleteLater();
    delete pView;
    delete pVBox;
    pScrollArea->deleteLater();
    qDeleteAll(this->children());
}
