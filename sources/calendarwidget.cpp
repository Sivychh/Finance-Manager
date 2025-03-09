#include "calendarwidget.h"

CalendarWidget::CalendarWidget(QWidget *pWgt) : QObject(pWgt)
{
    //инициализация всех кнопок и добавление их в горизонтальную таблицу
    pSelectedDay = new QDate(QDate::currentDate());

    pCalendarWidget = new QCalendarWidget;

    pIconBtn = new QPushButton;
    pBtnDay = new QPushButton("Траты за день");
    pBtnWeek = new QPushButton("за неделю");
    pBtnMonth = new QPushButton("за месяц");
    pBtnAllTime = new QPushButton("за все время");

    //данный индикатор используется, чтобы пользователь лучше понимал за какой период
    //времени отображаются объекты класса Item
    pDateLbl = new QLabel("");
    pDateLbl->setAlignment(Qt::AlignCenter);

    pVBox = new QVBoxLayout;
    pHBoxBtns = new QHBoxLayout;

    pCalendarWidget->setGridVisible(true);
    pCalendarWidget->setMinimumDate(QDate(2025, 1, 1));
    pCalendarWidget->setMaximumDate(QDate(2025, 12, 31));

    pIconBtn->setIcon(QPixmap(QDir::currentPath() + "/Picture/CalendarIcon.png"));
    pIconBtn->setIconSize(QSize(32,32));

    pIconBtn->setFlat(true);
    pBtnDay->setFlat(true);
    pBtnWeek->setFlat(true);
    pBtnMonth->setFlat(true);
    pBtnAllTime->setFlat(true);

    pHBoxBtns->addWidget(pBtnDay);
    pHBoxBtns->addWidget(pBtnWeek);
    pHBoxBtns->addWidget(pBtnMonth);
    pHBoxBtns->addWidget(pBtnAllTime);
    pHBoxBtns->addWidget(pIconBtn);

    pVBox->addLayout(pHBoxBtns);
    pVBox->addWidget(pDateLbl);

    //соединение кнопки для открытия виджета календаря
    QObject::connect(pIconBtn, SIGNAL(clicked(bool)), SLOT(slotCalendarClicked()));
    //сохранение выбранной даты в виджете календаря
    QObject::connect(pCalendarWidget, SIGNAL(selectionChanged()), SLOT(slotSelectionChanged()));
    //после нажатия кнопки слот отправляет сигнал объекту класса OutputItemWidget за какой период вывести объекты Item
    //все следующие соединения делают тоже самое
    QObject::connect(pBtnDay, SIGNAL(clicked(bool)), SLOT(slotDayBtnClicked()));
    QObject::connect(pBtnWeek, SIGNAL(clicked(bool)), SLOT(slotWeekBtnClicked()));
    QObject::connect(pBtnMonth, SIGNAL(clicked(bool)), SLOT(slotMonthBtnClicked()));
    QObject::connect(pBtnAllTime, SIGNAL(clicked(bool)), SLOT(slotAllDaysBtnClicked()));
}

CalendarWidget::CalendarWidget(const CalendarWidget &other) : QObject(other.parent())
{
    //конструктор копирования
    this->pSelectedDay = other.pSelectedDay;
    this->pCalendarWidget = other.pCalendarWidget;
    this->pIconBtn = other.pIconBtn;

    pIconBtn->setFlat(true);
    pBtnDay->setFlat(true);
    pBtnWeek->setFlat(true);
    pBtnMonth->setFlat(true);
    pBtnAllTime->setFlat(true);

    this->pHBoxBtns = other.pHBoxBtns;

    QObject::connect(pIconBtn, SIGNAL(clicked(bool)), SLOT(slotCalendarClicked()));
    QObject::connect(pCalendarWidget, SIGNAL(selectionChanged()), SLOT(slotSelectionChanged()));
    QObject::connect(pBtnDay, SIGNAL(clicked(bool)), SLOT(slotDayBtnClicked()));
    QObject::connect(pBtnWeek, SIGNAL(clicked(bool)), SLOT(slotWeekBtnClicked()));
    QObject::connect(pBtnMonth, SIGNAL(clicked(bool)), SLOT(slotMonthBtnClicked()));
    QObject::connect(pBtnAllTime, SIGNAL(clicked(bool)), SLOT(slotAllDaysBtnClicked()));
}

CalendarWidget& CalendarWidget::operator =(const CalendarWidget &other)
{
    return *this;
}

void CalendarWidget::slotCalendarClicked()
{
    //вывод виджета календаря
    pCalendarWidget->resize(300,200);
    pCalendarWidget->setWindowFlags(Qt::FramelessWindowHint);
    pCalendarWidget->show();
}

void CalendarWidget::slotSelectionChanged()
{
    //сохранение выбранной даты
    *pSelectedDay = pCalendarWidget->selectedDate();
    pCalendarWidget->hide();
}

void CalendarWidget::slotDayBtnClicked()
{
    //на индикаторе отображается выбранная дата
    pDateLbl->setText(pSelectedDay->toString("d.MM.yyyy"));
    emit updateOutputWgt(pSelectedDay, 1);
}

void CalendarWidget::slotWeekBtnClicked()
{
    //на индикаторе отображается выбранная неделя
    QDate booferDate = pSelectedDay->addDays(-7);
    pDateLbl->setText(booferDate.toString("d.MM.yyyy") + " - " + pSelectedDay->toString("d.MM.yyyy"));
    emit updateOutputWgt(pSelectedDay, 7);
}

void CalendarWidget::slotMonthBtnClicked()
{
    //на индикаторе отображается выбранный месяц
    pDateLbl->setText(QDate(pSelectedDay->year(), pSelectedDay->month(), 1).toString("d.MM.yyyy")
                      + " - " + pSelectedDay->toString("d.MM.yyyy"));
    emit updateOutputWgt(pSelectedDay, 30);
}

void CalendarWidget::slotAllDaysBtnClicked()
{
    pDateLbl->setText("");
    emit updateOutputWgt(pSelectedDay, 0);
}

QVBoxLayout* CalendarWidget::getVBoxLayout()
{
    return pVBox;
}

CalendarWidget::~CalendarWidget()
{
    delete pIconBtn;
    delete pBtnDay;
    delete pBtnWeek;
    delete pBtnMonth;
    delete pBtnAllTime;
    delete pSelectedDay;
    delete pHBoxBtns;
    delete pCalendarWidget;
}
