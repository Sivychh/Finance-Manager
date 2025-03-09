#include "additemwidget.h"

AddItemWidget::AddItemWidget(QWidget *pwgt) : QObject(pwgt)
{
    //Далее идет инициализация всех объектов, которые нужны для вывода виджета

    pDate = new QDate(QDate::currentDate()); //текущая дата по умолчанию если пользователь не выбрал другую

    pCopyParent = pwgt; //предок класса AddItemWidget ответственен за уничтожение всех объектов класса Item
    pMainWidget = new QWidget; //через этот виджет все выводится на экран

    pCalendarIcon = new QCalendarWidget;
    pCalendarBtn = new QPushButton("  Выберите дату");

    pSelectCategWgt = new QWidget;

    pVBox = new QVBoxLayout;
    pHBox = new QHBoxLayout;
    pGridLayout = new QGridLayout;

    pLblPrice = new QLabel("Стоимость:");
    pLineEditPrice = new QLineEdit;
    pLblComment = new QLabel("Комментарий:");
    pLineEditComment = new QLineEdit;

    pBtnDone = new QPushButton("Готово");
    pBtnCancel = new QPushButton("Отмена");
    pBtnSelectCateg = new QPushButton("Выберите категорию:");

    //регулярное выражение необходимо, чтобы пользователь мог ввести только цифры и "." если это не целое число
    //число может быть положительным или отрицательным

    QRegularExpression regExp("[+-]?\\d*\\.?\\d+");
    pLineEditPrice->setValidator(new QRegularExpressionValidator(regExp, pLineEditPrice));
    pLblPrice->setBuddy(pLineEditPrice);
    pLblComment->setBuddy(pLineEditComment);

    pCalendarIcon->setGridVisible(true);
    pCalendarIcon->setMinimumDate(QDate(2025, 1, 1));
    pCalendarIcon->setMaximumDate(QDate(2025, 12, 31));

    pCalendarBtn->setIcon(QPixmap(QDir::currentPath() + "/Picture/CalendarIcon.png"));
    pCalendarBtn->setIconSize(QSize(32,32));

    pCalendarBtn->setFlat(true);

    pHBox->addWidget(pBtnCancel);
    pHBox->addWidget(pBtnDone);

    pVBox->addWidget(pCalendarBtn);

    pVBox->addWidget(pLblPrice);
    pVBox->addWidget(pLineEditPrice);

    pVBox->addWidget(pBtnSelectCateg);

    pVBox->addWidget(pLblComment);
    pVBox->addWidget(pLineEditComment);

    pVBox->addLayout(pHBox);

    pMainWidget->setLayout(pVBox);
    pMainWidget->setFixedSize(300,300);
    pMainWidget->setWindowFlags(Qt::FramelessWindowHint);

    //по этому словарю загружаются изображения из папки Picture
    //и после объекту класса Item передается цвет
    mapCategories.insert("Здоровье", QColor(139, 0, 0));
    mapCategories.insert("Продукты", QColor(60, 179, 113));
    mapCategories.insert("Досуг", QColor(128, 0, 128));
    mapCategories.insert("Семья", QColor(255, 215, 0));
    mapCategories.insert("Дом", QColor(0, 0, 205));
    mapCategories.insert("Транспорт", QColor(169, 169, 169));
    mapCategories.insert("Работа", QColor(75, 0, 130));
    mapCategories.insert("Подарки", QColor(255, 0, 0));
    mapCategories.insert("Спорт", QColor(144, 238, 144));
    mapCategories.insert("Другое", QColor(0, 0, 0));
    mapCategories.insert("Инвестиции", QColor(255, 255, 0));
    mapCategories.insert("Путешествия", QColor(135, 206, 250));
    mapCategories.insert("Образование", QColor(0, 0, 128));
    mapCategories.insert("Заказы", QColor(255, 0, 255));
    mapCategories.insert("Кафе", QColor(255, 69, 0));

    pGridLayout->setSpacing(5);

    int i = 0;

    //инициализация всех иконок категорий в виде таблицы 5 на 3
    //все изображения сгенерированны нейросетью, так что с авторскими правами, в теории, проблем нет =)
    for(auto it = mapCategories.begin(); it != mapCategories.end(); ++it)
    {
        pCategoryIcon = new CategoryIcon(QPixmap(QDir::currentPath() + "/Picture/"
                                                 + it.key() + ".jpg"), it.key(), it.value());
        QObject::connect(pCategoryIcon, SIGNAL(clicked(QString, QColor)), SLOT(slotSelectedCategory(QString, QColor)));
        pGridLayout->addWidget(pCategoryIcon, i / 5, i % 5);
        i++;
    }

    pSelectCategWgt->setLayout(pGridLayout);
    pSelectCategWgt->setWindowFlags(Qt::FramelessWindowHint);

    //соединение кнопки для закрытия виджета
    QObject::connect(pBtnCancel, SIGNAL(clicked(bool)), SLOT(cancelButtonClicked()));
    //соединение кнопки для создания и передачи объекта класса Item
    QObject::connect(pBtnDone, SIGNAL(clicked(bool)), SLOT(doneButtonClicked()));
    //соединение кнопки для открытия виджета календаря
    QObject::connect(pCalendarBtn, SIGNAL(clicked(bool)), SLOT(slotCalendarBtnClicked()));
    //после выбора даты в виджете календаря следует ее сохранение в указателе pDate
    QObject::connect(pCalendarIcon, SIGNAL(selectionChanged()), SLOT(slotSelectionChanged()));
    //соединение кнопки для открытия виджета выбора категории
    QObject::connect(pBtnSelectCateg, SIGNAL(clicked(bool)), SLOT(slotBtnSelectCategory()));
}

void AddItemWidget::doneButtonClicked()
{
    //после нажатия кнопки "готово" виджет закрывается и
    //указатель на объект класса Item отправляется объекту класса OutputItemWidget
    pItem = new Item;
    pItem->setCategory(itemCategory);
    pItem->setColor(itemColor);
    pItem->setComment(pLineEditComment->text());
    pItem->setDate(*pDate);
    pItem->setPrice(pLineEditPrice->text().toFloat());
    pItem->setParent(pCopyParent);
    emit sendData(pItem);
    pMainWidget->hide();
}

void AddItemWidget::cancelButtonClicked()
{
    pMainWidget->hide();
}

void AddItemWidget::isClicked()
{
    pMainWidget->show();
}

void AddItemWidget::slotCalendarBtnClicked()
{
    //при нажатии на иконку календаря открывается виджет, в котором можно выбрать дату оплаты
    pCalendarIcon->resize(300,200);
    pCalendarIcon->setWindowFlags(Qt::FramelessWindowHint);
    pCalendarIcon->show();
}

void AddItemWidget::slotSelectionChanged()
{
    *pDate = pCalendarIcon->selectedDate();
    pCalendarIcon->hide();
}

void AddItemWidget::slotBtnSelectCategory()
{
    pSelectCategWgt->show();
}

void AddItemWidget::slotSelectedCategory(QString nameOfCategory, QColor color)
{
    //как только пользователь выбрал категорию, ее название и цвет сохраняются
    //в соответствующих переменных, чтобы далее передать объекту класса Item
    itemCategory = nameOfCategory;
    itemColor = color;
    pBtnSelectCateg->setText(nameOfCategory);
    pSelectCategWgt->hide();
}

AddItemWidget::~AddItemWidget()
{
    delete pCalendarIcon;
    delete pCalendarBtn;
    delete pCategoryIcon;
    delete pLblPrice;
    delete pLineEditPrice;
    delete pDate;
    delete pLblComment;
    delete pLineEditComment;
    delete pBtnDone;
    delete pBtnCancel;
    delete pBtnSelectCateg;
    delete pHBox;
    delete pVBox;
    delete pGridLayout;
    delete pSelectCategWgt;
    pItem = 0;
    delete pItem;
    delete pMainWidget;
    qDeleteAll(this->children());
}
