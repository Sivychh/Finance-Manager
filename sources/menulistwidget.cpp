#include "menulistwidget.h"

MenuListWidget::MenuListWidget(QWidget *pwgt) : QWidget(pwgt)
{
    //добавление элементво для QListWidget
    strList << "Главная" << "Графики";

    for(int i = 0; i < strList.size(); i++)
    {
        pListItem = new QListWidgetItem(strList[i]);
        pListWidget->addItem(pListItem);
    }

    //первоначальный сетап виджета
    pBtn = new QPushButton("Добавить оплату");
    pVBox = new QVBoxLayout;
    pHBox = new QHBoxLayout;

    pCalendarWgt = new CalendarWidget(this);
    pDiagramWgt = new DiagramWidget(this);
    pAddWidget = new AddItemWidget(this);
    pOutputItemWgt = new OutputItemWidget(this);

    //соединение для отслеживания какой элемент списка был нажат
    QObject::connect(pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(slotListItemActivated(QListWidgetItem*)));
    QObject::connect(pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slotListItemActivated(QListWidgetItem*)));
    //смена виджета в зависимости от названия элемента, которое передается сигналом
    QObject::connect(this, SIGNAL(changeLayout(QString)), SLOT(slotChangedLayout(QString)));

    //эта переменная нужна, чтобы виджет не перерисовывался при нажатии одного и того же элемента списка
    isRepeat = "Профиль";

    emit changeLayout("Главная");
}

QListWidget* MenuListWidget::getPListWidget()
{
    return pListWidget;
}

void MenuListWidget::clearLayout(QLayout* layout)
{
    //метод для очистки pOutputLayout
    //чтобы после добавить в него новые виджета
    if (layout->isEmpty())
        return;

    while (QLayoutItem *item = layout->takeAt(0))
    {
        if (QWidget *widget = item->widget())
        {
            layout->removeWidget(widget);
            widget->deleteLater();
        }
        else if (QLayout *childLayout = item->layout())
        {
            clearLayout(childLayout);
            childLayout->deleteLater();
        }
        delete item;
    }

}

void MenuListWidget::slotChangedLayout(QString text)
{

    if(text == "Главная" && isRepeat != "Главная")
    {
        //далее идет повторное создание виджетов для
        //отрисовки главной страницы приложения

        //очитска памяти от старых виджетов
        delete this->findChild<ProfileEditWidget*>();
        delete this->findChild<CalendarWidget*>();
        delete this->findChild<DiagramWidget*>();
        delete this->findChild<AddItemWidget*>();
        delete this->findChild<OutputItemWidget*>();
        delete this->findChild<GraphicsWidget*>();

        clearLayout(pOutputLayout);

        //заполнение pOutputLayout новыми виджетами
        pCalendarWgt = new CalendarWidget(this);
        pDiagramWgt = new DiagramWidget(this);
        pAddWidget = new AddItemWidget(this);
        pOutputItemWgt = new OutputItemWidget(this);
        pTotalPriceLbl = new QLabel(this);
        pText1Lbl = new QLabel("Общая стоимость трат: ", this);
        pText2Lbl = new QLabel("Byn", this);

        pBtn = new QPushButton("Добавить оплату");
        pVBox = new QVBoxLayout;
        pHBox = new QHBoxLayout;
        pHBoxPrice = new QHBoxLayout;

        //соединение кнопки для открытия виджета объекта класса AddItemWidget
        QObject::connect(pBtn, SIGNAL(clicked()), pAddWidget, SLOT(isClicked()));
        //соединение для добавления нового объекта класса Item в общее хранилище этих объектов
        QObject::connect(pAddWidget, SIGNAL(sendData(Item*)), pOutputItemWgt, SLOT(slotAddItem(Item*)));
        //соединение для обновления круговой диаграммы
        QObject::connect(pOutputItemWgt, SIGNAL(updatePie(QVector<StorageItems*>)),
                         pDiagramWgt, SLOT(slotUpdatePie(QVector<StorageItems*>)));
        //соединение для отправки даты объекту класса OutputItemWidget для дальнейшей сортировки всех объектов класса Item
        QObject::connect(pCalendarWgt, SIGNAL(updateOutputWgt(QDate*,int)), pOutputItemWgt, SLOT(slotDateChanged(QDate*,int)));
        //этот сигнал позволяет сохранять указатели на объекты класса Item на протяжении всего цикла программы
        QObject::connect(pOutputItemWgt, SIGNAL(sendVector(QVector<StorageItems*>)), SLOT(slotSaveVector(QVector<StorageItems*>)));
        //сигнал для обновления индикатора общей стоимости всех трат
        QObject::connect(pOutputItemWgt, SIGNAL(sendTotalPrice(double)), pTotalPriceLbl, SLOT(setNum(double)));

        //повторное обновление диаграммы и индикатора всех трат
        emit pOutputItemWgt->updatePie(pOutputItemWgt->vecOfStorageItems);
        emit pOutputItemWgt->sendTotalPrice(pOutputItemWgt->getTotalPrice(pOutputItemWgt->vecOfStorageItems));

        pText1Lbl->setFixedHeight(30);
        pText2Lbl->setFixedHeight(30);
        pTotalPriceLbl->setFixedHeight(30);

        pHBoxPrice->addWidget(pText1Lbl);
        pHBoxPrice->addWidget(pTotalPriceLbl);
        pHBoxPrice->addWidget(pText2Lbl);
        pHBoxPrice->setAlignment(Qt::AlignCenter);

        pVBox->addWidget(pDiagramWgt->getPChartView());
        pVBox->addLayout(pHBoxPrice);
        pVBox->addWidget(pBtn);

        pHBox->addWidget(pOutputItemWgt->getListWidget());
        pHBox->addLayout(pVBox);

        pOutputLayout->addLayout(pCalendarWgt->getVBoxLayout());
        pOutputLayout->addLayout(pHBox);

        isRepeat = "Главная";
        setLayout(pOutputLayout);
    }
    else if(text == "Профиль" && isRepeat != "Профиль")
    {
        //далее идет создание виджета для отрисовки
        //страницы профиля пользователя

        delete this->findChild<ProfileEditWidget*>();
        delete this->findChild<CalendarWidget*>();
        delete this->findChild<DiagramWidget*>();
        delete this->findChild<AddItemWidget*>();
        delete this->findChild<OutputItemWidget*>();
        delete this->findChild<GraphicsWidget*>();

        clearLayout(pOutputLayout);

        pProfileEditWgt = new ProfileEditWidget(this);
        pOutputLayout->addWidget(pProfileEditWgt);

        //соединение для обновления имени пользователя
        QObject::connect(pProfileEditWgt->pLineEditName, SIGNAL(textChanged(QString)), SLOT(slotNameProfileChanged(QString)));
        //соединение для обновления изображения пользователя
        QObject::connect(&pProfileEditWgt->drawingIcon, SIGNAL(changePhoto(QPixmap*)), SLOT(slotResendPhoto(QPixmap*)));
        isRepeat = "Профиль";
        setLayout(pOutputLayout);
    }
    else if(text == "Графики" && isRepeat != "Графики")
    {
        //далее идет создание виджета для отрисовки
        //страницы со всеми диаграммами показывающие траты пользователя

        delete this->findChild<ProfileEditWidget*>();
        delete this->findChild<CalendarWidget*>();
        delete this->findChild<DiagramWidget*>();
        delete this->findChild<AddItemWidget*>();
        delete this->findChild<OutputItemWidget*>();
        delete this->findChild<GraphicsWidget*>();

        clearLayout(pOutputLayout);

        pGraphicsWgt = new GraphicsWidget(vecOfStorageItems, this);
        pOutputLayout->addWidget(pGraphicsWgt->pScrollArea);
        isRepeat = "Графики";
        setLayout(pOutputLayout);
    }
}

void MenuListWidget::slotListItemActivated(QListWidgetItem *pItemList)
{
    emit changeLayout(pItemList->text());
}

void MenuListWidget::slotNameProfileChanged(QString str)
{
    emit sendNewName(str);
}

void MenuListWidget::slotResendPhoto(QPixmap *pPixmap)
{
    this->pPixmap = pPixmap;
    emit resendPhoto(this->pPixmap);
}

void MenuListWidget::slotSaveVector(QVector<StorageItems*> vecOfStor)
{
    vecOfStorageItems = vecOfStor;
}
