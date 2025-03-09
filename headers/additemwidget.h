#ifndef ADDITEMWIDGET_H
#define ADDITEMWIDGET_H

#include <QCoreApplication>
#include <QCalendarWidget>
#include <QDir>
#include "item.h"
#include "outputitemswidget.h"
#include "categoryicon.h"

/*
Данный класс нужен для вывода виджета после нажатия кнопки
на главном виджете "Добавить оплату", однако объект класса
инициализируется еще до нажатия кнопки. В этом виджете после
ввода пользователем даты оплаты, цены, категории оплаты и
комментария создается объект класса Item, указатель на который
передается классу OutputItemWidget посредством сигнала sendData()
в слот slotAddItem()
*/

class AddItemWidget : public QObject
{
    Q_OBJECT
private:

    QWidget *pCopyParent;
    QWidget *pMainWidget;

    QCalendarWidget *pCalendarIcon;
    QPushButton *pCalendarBtn;

    QMap<QString, QColor> mapCategories;

    QColor itemColor;
    QString itemCategory;

    Item *pItem;
    CategoryIcon* pCategoryIcon;

    QWidget *pSelectCategWgt;
    QVBoxLayout *pVBox;
    QHBoxLayout *pHBox;
    QGridLayout *pGridLayout;

    QLabel *pLblPrice;
    QLineEdit *pLineEditPrice;

    QDate *pDate;

    QLabel *pLblComment;
    QLineEdit *pLineEditComment;

    QPushButton *pBtnDone;
    QPushButton *pBtnCancel;
    QPushButton *pBtnSelectCateg;

public:
    AddItemWidget(QWidget *pwgt = 0);
    ~AddItemWidget();

public slots:

    void isClicked();
    void doneButtonClicked();
    void cancelButtonClicked();
    void slotCalendarBtnClicked();
    void slotSelectionChanged();
    void slotBtnSelectCategory();
    void slotSelectedCategory(QString nameOfCategory, QColor color);

signals:

    void sendData(Item* pItem);
};

#endif // ADDITEMWIDGET_H
