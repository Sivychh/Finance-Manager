#ifndef STORAGEITEMS_H
#define STORAGEITEMS_H

#include <QListWidget>
#include "item.h"

/*
Данный класс выступает в роли хранилища указателей на объекты класса Item
а также этот класс ответственен за отображение всех объектов класса Item
в виде списка при вызове сигналом из объекта класса OutputItemWidget
*/

class StorageItems : public QObject
{
    Q_OBJECT
private:

    float sumPrice;

    QWidget *pWgtArray = new QWidget;

    QWidget *pCopyParent;

    QVBoxLayout *pVBox = new QVBoxLayout;
    QListWidget *pListWidget = new QListWidget;
    QListWidgetItem *pListItem = new QListWidgetItem;

    QPushButton *pBtnClose = new QPushButton("Отмена");

public:

    StorageItems* pStorage;

    StorageItems(Item *pItem, QWidget *pwgt = 0);
    ~StorageItems();

    QString nameCategory;
    QVector<Item*> vecOfItems;

    float getSum();
    void widgetActivated();
    QColor getColor();

public slots:

    void slotItemActivated(QListWidgetItem *pItem);
    void closeWidget();
    void slotDeleteItem(Item *pItem);

signals:

    void updateOutputWgt();
    void deleteStorage(StorageItems* pStorage);
};

#endif // STORAGEITEMS_H
