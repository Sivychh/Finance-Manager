#include "outputitemswidget.h"

OutputItemWidget::OutputItemWidget(QWidget *pwgt) : QObject(pwgt)
{
    //объект класса MenuListWidget ответственен за удаление объектов класса StorageItems
    pCopyParent = pwgt;

    //объект класса QListWidget через который и происходит вывод всех объектов класса StorageItems
    pListWidget = new QListWidget;

    pListItem = new QListWidgetItem("Расходов нет");
    pListWidget->addItem(pListItem);
    //переменная нужна для проверки того существует ли уже объект класса StorageItems в определенной категории
    isRepeat = false;
    //переменная нужна для вывода сортированного по определенной дате массива объектов класса StorageItems
    //если значение равно истине и вывода всех объектов класса StorageItems если значение ложное
    vecIsCopy = false;

    //соединения для определения какой объект класса StorageItems вызван
    QObject::connect(pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(slotListItemActivated(QListWidgetItem*)));
    QObject::connect(pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slotListItemActivated(QListWidgetItem*)));

    //обновление отображаемого списка данных
    QObject::connect(this, SIGNAL(update(QVector<StorageItems*>)), SLOT(slotUpdate(QVector<StorageItems*>)));

    //загрузка всех объектов класса Item из файла
    loadItems();
    update(vecOfStorageItems);
}

QListWidget* OutputItemWidget::getListWidget()
{
    return pListWidget;
}

void OutputItemWidget::slotAddItem(Item *pItem)
{
    //сигнал приходит от объекта класса AddItemWidget
    this->addItemInVec(vecOfStorageItems, pItem);
    emit update(vecOfStorageItems);
    vecIsCopy = false;
}

double OutputItemWidget::getTotalPrice(QVector<StorageItems*> vec)
{
    //итоговая стоимость всех трат для индикатора на главном виджете
    double sum = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        sum += vec[i]->getSum();
    }
    return sum;
}

void OutputItemWidget::slotUpdate(QVector<StorageItems*> vec)
{
    //обновление диаграммы
    emit updatePie(vec);

    double sum = getTotalPrice(vec);
    emit sendTotalPrice(sum);

    pListWidget->clear();

    //повторное создание и вывод списка
    if(vec.isEmpty())
    {
        pListItem = new QListWidgetItem("Расходов нет");
        pListWidget->addItem(pListItem);
    }
    else
    {
        for(int i = 0; i < vec.size(); i++)
        {
            pListItem = new QListWidgetItem(vec[i]->nameCategory + " - "
                                            + QString::number(vec[i]->getSum())
                                            + " Byn"
                                            + " (" + QString::number(vec[i]->getSum() / getTotalPrice(vec) * 100)
                                            + " %)");
            pListItem->setIcon(createIcon(vec[i]->getColor()));
            pListWidget->addItem(pListItem);
        }
    }
    //сохранение всей объектов класса Item в файле
    saveItems();
}

void OutputItemWidget::addItemInVec(QVector<StorageItems*>& vec, Item* pItem)
{
    //здесь идет проверка существует ли уже хранилище с категорией объекта класса Item
    //если есть, то добавляется уже к существующему массиву внутри объекта класса StorageItems
    //если нет, то создается новый объект класса StorageItems и Item добавляется в него
    for(int i = 0; i < vec.size(); i++)
    {
        if(pItem->getCategory() == vec[i]->nameCategory)
        {
            vec[i]->vecOfItems.push_back(pItem);

            //соединение позволяющее удалить объект класса Item по желанию пользователя
            QObject::connect(pItem, SIGNAL(deleteItem(Item*)), vec[i], SLOT(slotDeleteItem(Item*)));
            //соединение благодаря которому при изменении объекта класса Item обновляется весь список объектов
            QObject::connect(pItem, SIGNAL(updateOutputWgt()), SLOT(slotUpdateByItem()));

            isRepeat = true;
            break;
        }
    }

    if(!isRepeat)
    {
        pNewStorage = new StorageItems(pItem, pCopyParent);
        vec.push_back(pNewStorage);

        //соединение позволяющее удалить объект класса StorageItems, если в нем не осталось объектов класса Item
        QObject::connect(pNewStorage, SIGNAL(deleteStorage(StorageItems*)), SLOT(slotDeleteStorage(StorageItems*)));
        //соединение благодаря которому при изменении объекта класса StorageItems обновляется весь список объектов
        QObject::connect(pNewStorage, SIGNAL(updateOutputWgt()), SLOT(slotUpdateByItem()));

        QObject::connect(pItem, SIGNAL(deleteItem(Item*)), pNewStorage, SLOT(slotDeleteItem(Item*)));
        QObject::connect(pItem, SIGNAL(updateOutputWgt()), SLOT(slotUpdateByItem()));
    }

    isRepeat = false;
}

void OutputItemWidget::slotDateChanged(QDate *pDate, int day)
{
    //далее идет сортировка нового массива указателей на объекты класса StorageItems
    //в соответствии с датой выбранной пользователем
    for(int i = 0; i < sortVecOfStorItems.size(); i++)
    {
        //удаление старых указателей
        delete sortVecOfStorItems[i];
    }
    sortVecOfStorItems.clear();

    if(day == 1)
    {
        for(int i = 0; i < vecOfStorageItems.size(); i++)
        {
            for(int j = 0; j < vecOfStorageItems[i]->vecOfItems.size(); j++)
            {
                //если дата объекта класса Item совпадает с выбранной пользователем датой, то указатель
                //на объект копируется в новый массив
                if(vecOfStorageItems[i]->vecOfItems[j]->getDate() == *pDate)
                    this->addItemInVec(sortVecOfStorItems, vecOfStorageItems[i]->vecOfItems[j]);
            }
        }
        //список на главном виджете обновляется по новому массиву
        emit update(sortVecOfStorItems);
        vecIsCopy = true;
    }
    else if(day == 7)
    {
        for(int i = 0; i < vecOfStorageItems.size(); i++)
        {
            for(int j = 0; j < vecOfStorageItems[i]->vecOfItems.size(); j++)
            {
                //если дата объекта класса Item попадает в промежуток с выбранной пользователем датой, то указатель
                //на объект копируется в новый массив
                if(vecOfStorageItems[i]->vecOfItems[j]->getDate() >= pDate->addDays(-7) &&
                    vecOfStorageItems[i]->vecOfItems[j]->getDate() <= *pDate)
                    this->addItemInVec(sortVecOfStorItems, vecOfStorageItems[i]->vecOfItems[j]);
            }
        }
        //список на главном виджете обновляется по новому массиву
        emit update(sortVecOfStorItems);
        vecIsCopy = true;
    }
    else if(day == 30)
    {
        for(int i = 0; i < vecOfStorageItems.size(); i++)
        {
            for(int j = 0; j < vecOfStorageItems[i]->vecOfItems.size(); j++)
            {
                //если дата объекта класса Item попадает в промежуток с выбранной пользователем датой, то указатель
                //на объект копируется в новый массив
                if(vecOfStorageItems[i]->vecOfItems[j]->getDate() >= QDate(pDate->year(), pDate->month(), 1) &&
                    vecOfStorageItems[i]->vecOfItems[j]->getDate() <= QDate(pDate->year(), pDate->month(), pDate->daysInMonth()))
                    this->addItemInVec(sortVecOfStorItems, vecOfStorageItems[i]->vecOfItems[j]);
            }
        }
        //список на главном виджете обновляется по новому массиву
        emit update(sortVecOfStorItems);
        vecIsCopy = true;
    }
    else
    {
        //отправляется изначальный массив
        emit update(vecOfStorageItems);
        vecIsCopy = false;
    }
}

QIcon OutputItemWidget::createIcon(QColor color)
{
    //создание иконки слева от элемента списка
    QPixmap pixmap(20,20);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, 20, 20);

    return QIcon(pixmap);
}

void OutputItemWidget::slotListItemActivated(QListWidgetItem *pListItem)
{
    //при нажатии на элемент списка открывается виджет созданный классом StorageItems
    if(vecIsCopy)
    {
        for(int i = 0; i < sortVecOfStorItems.size(); i++)
        {
            if(pListItem == pListWidget->item(i))
            {
                sortVecOfStorItems[i]->widgetActivated();
            }
        }
    }
    else
    {
        for(int i = 0; i < vecOfStorageItems.size(); i++)
        {
            if(pListItem == pListWidget->item(i))
            {
                vecOfStorageItems[i]->widgetActivated();
            }
        }
    }
}

void OutputItemWidget::slotUpdateByItem()
{
    emit update(vecOfStorageItems);
}

void OutputItemWidget::slotDeleteStorage(StorageItems *pStorage)
{
    //удаление объекта класса StorageItems
    for(int i = 0; i < vecOfStorageItems.size(); i++)
    {
        if(vecOfStorageItems[i] == pStorage)
        {
            vecOfStorageItems.remove(i);
            break;
        }
    }

    emit update(vecOfStorageItems);
    vecIsCopy = false;

    pStorage->~StorageItems();
}

void OutputItemWidget::saveItems()
{
    //сохранение всех объектов класса Item в файл
    //а точнее всей информации необходимой для повторного создания объекта класса Item
    //конечно в качестве альтернативы можно перегрузить операторы >> и << класса Item под класс QDataStream
    vecOfItemsCategory.clear();
    vecOfItemsColor.clear();
    vecOfItemsComment.clear();
    vecOfItemsDate.clear();
    vecOfItemsPrice.clear();

    for(int i = 0; i < vecOfStorageItems.size(); i++)
    {
        for(int j = 0; j < vecOfStorageItems[i]->vecOfItems.size(); j++)
        {
            vecOfItemsCategory.push_back(vecOfStorageItems[i]->vecOfItems[j]->getCategory());
            vecOfItemsColor.push_back(vecOfStorageItems[i]->vecOfItems[j]->getColor());
            vecOfItemsComment.push_back(vecOfStorageItems[i]->vecOfItems[j]->getComment());
            vecOfItemsDate.push_back(vecOfStorageItems[i]->vecOfItems[j]->getDate());
            vecOfItemsPrice.push_back(vecOfStorageItems[i]->vecOfItems[j]->getPrice());
        }
    }

    QFile file("Items.dat");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << vecOfItemsCategory
            << vecOfItemsColor
            << vecOfItemsComment
            << vecOfItemsDate
            << vecOfItemsPrice;
        file.close();
    }
}

void OutputItemWidget::loadItems()
{
    //загрузка всех объектов класса Item из файла
    //а точнее всей информации необходимой для создания объекта класса Item
    //конечно в качестве альтернативы можно перегрузить операторы >> и << класса Item под класс QDataStream
    vecOfItemsCategory.clear();
    vecOfItemsColor.clear();
    vecOfItemsComment.clear();
    vecOfItemsDate.clear();
    vecOfItemsPrice.clear();

    QFile file("Items.dat");
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> vecOfItemsCategory
            >> vecOfItemsColor
            >> vecOfItemsComment
            >> vecOfItemsDate
            >> vecOfItemsPrice;
        file.close();
    }

    for(int i = 0; i < vecOfItemsCategory.size(); i++)
    {
        //создание новых объектов класса Item и передача им данных из файла
        Item *pItem = new Item;
        pItem->setCategory(vecOfItemsCategory[i]);
        pItem->setColor(vecOfItemsColor[i]);
        pItem->setComment(vecOfItemsComment[i]);
        pItem->setDate(vecOfItemsDate[i]);
        pItem->setPrice(vecOfItemsPrice[i]);

        addItemInVec(vecOfStorageItems, pItem);
    }

    emit update(vecOfStorageItems);
}

OutputItemWidget::~OutputItemWidget()
{
    saveItems();

    emit sendVector(vecOfStorageItems);

    vecOfStorageItems.clear();

    for(int i = 0; i < sortVecOfStorItems.size(); i++)
    {
        delete sortVecOfStorItems[i];
    }
    sortVecOfStorItems.clear();

    delete pListItem;
    delete pListWidget;
    pCopyParent = 0;
    delete pCopyParent;
}
