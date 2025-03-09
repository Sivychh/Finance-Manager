#ifndef OUTPUTITEMSWIDGET_H
#define OUTPUTITEMSWIDGET_H

#include <QFile>
#include <QPainter>
#include "storageitems.h"
#include "item.h"

/*
Данный класс выступает в роли хранилища указателей на объекты класса StorageItems
а также этот класс ответственен за отображение всех объектов класса StorageItems
в виде списка на главном виджете
*/

class OutputItemWidget : public QObject
{
    Q_OBJECT
private:
    QWidget *pCopyParent;

    float sumPrices;
    float percent;
    bool isRepeat;
    bool vecIsCopy;

    QListWidget *pListWidget;
    QListWidgetItem *pListItem;
    StorageItems *pNewStorage;

    QVector<float> vecOfItemsPrice;
    QVector<QColor> vecOfItemsColor;
    QVector<QString> vecOfItemsCategory;
    QVector<QString> vecOfItemsComment;
    QVector<QDate> vecOfItemsDate;

    void addItemInVec(QVector<StorageItems*>& vec, Item* pItem);
    void saveItems();
    void loadItems();

    QIcon createIcon(QColor);

public:

    OutputItemWidget(QWidget *pwgt = 0);
    ~OutputItemWidget();

    double getTotalPrice(QVector<StorageItems*> vec);

    QVector<StorageItems*> vecOfStorageItems;
    QVector<StorageItems*> sortVecOfStorItems;

    QListWidget* getListWidget();

public slots:

    void slotAddItem(Item *pItem);
    void slotListItemActivated(QListWidgetItem* pListItem);
    void slotUpdate(QVector<StorageItems*> vec);
    void slotDateChanged(QDate* pDate, int day);
    void slotUpdateByItem();
    void slotDeleteStorage(StorageItems* pStorage);

signals:

    void sendTotalPrice(double);
    void sendVector(QVector<StorageItems*>);
    void update(QVector<StorageItems*>);
    void updatePie(QVector<StorageItems*>);
};
#endif // OUTPUTITEMSWIDGET_H
