#include "storageitems.h"

StorageItems::StorageItems(Item *pItem, QWidget *pwgt) : QObject(pwgt)
{
    pCopyParent = pwgt;
    pStorage = this;

    vecOfItems.push_back(pItem);
    //т.к. все объекты класса Item внутри объекта класса StorageItems имеют одинаковое название категории
    //это название я вынес отдельную переменную
    nameCategory = pItem->getCategory();
    //соединение кнопки для закрытия виджета
    QObject::connect(pBtnClose, SIGNAL(clicked(bool)), SLOT(closeWidget()));
    //соединения для отображения виджета класса Item
    QObject::connect(pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(slotItemActivated(QListWidgetItem*)));
    QObject::connect(pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slotItemActivated(QListWidgetItem*)));
}

void StorageItems::widgetActivated()
{
    //метод вызывается объектом класса OutputItemWidget
    //здесь в объект класса QListWidget добавляются все названия объектов класса Item
    //и после открывается виджет
    pListWidget->clear();
    for(int i = 0; i < vecOfItems.size(); i++)
    {
        pListItem = new QListWidgetItem(vecOfItems[i]->getDate().toString("d.MM.yyyy") + "\n"
                                        + vecOfItems[i]->getCategory() + " - "
                                        + QString::number(vecOfItems[i]->getPrice()));
        pListWidget->addItem(pListItem);
    }
    pListWidget->setSpacing(5);
    pVBox->addWidget(pListWidget);
    pVBox->addWidget(pBtnClose);

    pWgtArray->setLayout(pVBox);
    pWgtArray->setFixedSize(400,200);
    pWgtArray->setWindowFlags(Qt::FramelessWindowHint);

    pWgtArray->show();
}

float StorageItems::getSum()
{
    //метод для подсчета общей стоимости всех объекто класса Item
    sumPrice = 0;
    for(int i = 0; i < vecOfItems.size(); i++)
    {
        sumPrice += vecOfItems[i]->getPrice();
    }
    return sumPrice;
}

void StorageItems::closeWidget()
{
    pWgtArray->close();
}

QColor StorageItems::getColor()
{
    return vecOfItems[0]->getColor();
}

void StorageItems::slotItemActivated(QListWidgetItem *pItem)
{
    //слот для открытия виджета объекта класса Item
    for(int i = 0; i < vecOfItems.size(); i++)
    {
        if(pItem == pListWidget->item(i))
        {
            qDebug() << QString::number(i);
            vecOfItems[i]->isClicked();
        }
    }
}

void StorageItems::slotDeleteItem(Item *pItem)
{
    //здесь идет удаление объекта класса Item
    //если после удаления объект класса StorageItems остается пустым
    //то отправляется сигнал для удаления этого объекта
    for(int i = 0; i < vecOfItems.size(); i++)
    {
        if(vecOfItems[i] == pItem)
        {
            vecOfItems.remove(i);
            break;
        }
    }

    pWgtArray->close();

    if(vecOfItems.isEmpty())
        emit deleteStorage(pStorage);
    else
        emit updateOutputWgt();

    pItem->~Item();
}

StorageItems::~StorageItems()
{
    pStorage = 0;
    delete pStorage;

    vecOfItems.clear();

    pCopyParent = 0;
    delete pCopyParent;
    delete pListItem;
    delete pListWidget;
    delete pBtnClose;
    delete pVBox;
    delete pWgtArray;
}
