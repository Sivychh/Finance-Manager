#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>
#include <QDir>
#include "outputitemswidget.h"

/*
Данный класс нужен для вывода горизонтальной таблицы
в верхней части главного виджета, которая позволяет
пользователю выбрать за какую дату отобразить категории оплат.
Таблица содержит 5 плоских кнопок, их цель:

pIconBtn - при нажатии на эту кнопку открывается виджет календаря, относительно выбранной
даты и происходит сортировка объектов класса Item

pBtnDay - отправляет объекту класса OutputItemWidget сигнал, по которому все объекты
класса Item нужно отсортировать и вывести за выбранную дату в виджете календаря;

pBtnWeek - сортировка объектов класса Item и их вывод за неделю относительно выбранной даты;

pBtnMonth - сортировка объектов класса Item и их вывод за месяц относительно выбранной даты;

pBtnAllTime - сортировка объектов класса Item и их вывод за все время;
*/

class CalendarWidget : public QObject
{
    Q_OBJECT
private:

    QCalendarWidget *pCalendarWidget;
    QDate *pSelectedDay;

    QPushButton *pIconBtn;
    QPushButton *pBtnDay;
    QPushButton *pBtnWeek;
    QPushButton *pBtnMonth;
    QPushButton *pBtnAllTime;
    QLabel *pDateLbl;

    QHBoxLayout *pHBoxBtns;
    QVBoxLayout *pVBox;

public:

    CalendarWidget(QWidget *pWgt = 0);
    ~CalendarWidget();

    CalendarWidget(const CalendarWidget &other);

    CalendarWidget& operator=(const CalendarWidget &other);

    QVBoxLayout* getVBoxLayout();

signals:

    void updateOutputWgt(QDate* pDate, int days);

public slots:

    void slotCalendarClicked();
    void slotSelectionChanged();
    void slotDayBtnClicked();
    void slotWeekBtnClicked();
    void slotMonthBtnClicked();
    void slotAllDaysBtnClicked();

};

#endif // CALENDARWIDGET_H
