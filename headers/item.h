#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>

/*
Данный класс содержит в себе всю информацию одной оплаты.
Предком его объектов является объект класса MenuListWidget, поэтому
объекты этого класса существуют на протяжении всего цикла программы,
если их, конечно, пользователь сам не удалил. Все объекты сохраняются
во время работы программы и при запуске загружаются при помощи объекта
класса OutputItemWidget
*/

class Item : public QObject
{
    Q_OBJECT
private:

    float price;
    int count;
    QString category;
    QDate date;
    QString comment;
    QColor color;

    QWidget *pCopyParent;
    QWidget *pWgtData;

    QVBoxLayout *pVBox;
    QHBoxLayout *pHBox;

    QPushButton *pBtnClose;
    QPushButton *pBtnEdit;
    QPushButton *pBtnDelete;

    QLabel *pPriceLbl;
    QLineEdit *pLinePrice;

    QLabel *pCategoryLbl;
    QLabel *pDateLbl;

    QLabel *pCommentLbl;
    QLineEdit *pLineComment;

public:

    Item(float price = 0, QString category = " ", QDate date = QDate::currentDate(),
         QString comment = " ", QColor color = QColor(0,0,0), QWidget *pwgt = 0);
    ~Item();

    QDate getDate();
    void setDate(QDate date);

    QString getCategory();
    void setCategory(QString category);

    QString getComment();
    void setComment(QString comment);

    float getPrice();
    void setPrice(float price);

    QColor getColor();
    void setColor(QColor color);

    void isClicked();

public slots:

    void slotBtnEdit();
    void slotBtnClose();
    void slotBtnDelete();

signals:

    void deleteItem(Item* pItem);
    void updateListCategory();
    void updateOutputWgt();
};
#endif // ITEM_H
