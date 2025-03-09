#include "item.h"

Item::Item(float price, QString category, QDate date, QString comment, QColor color, QWidget *pwgt) : QObject(pwgt)
{
    //данный класс выводит виджет, если был нажат соответствующий объект
    //класса QListWidgetItem в листе виджета объекта класса StorageItems
    //далее инициализируется виджет и все необходимое ему

    pCopyParent = pwgt;
    pBtnClose = new QPushButton("Отмена");
    pBtnEdit = new QPushButton("Исправить");
    pBtnDelete = new QPushButton("Удалить");

    pWgtData = new QWidget;
    pVBox = new QVBoxLayout;
    pHBox = new QHBoxLayout;

    pPriceLbl = new QLabel("Стоимость");
    pLinePrice = new QLineEdit;
    pPriceLbl->setBuddy(pLinePrice);
    pLinePrice->setReadOnly(true);

    pCategoryLbl = new QLabel;

    pCommentLbl = new QLabel("Комментарий");
    pLineComment = new QLineEdit;
    pCommentLbl->setBuddy(pLineComment);
    pLineComment->setReadOnly(true);

    pDateLbl = new QLabel;

    pHBox->addWidget(pBtnDelete);
    pHBox->addWidget(pBtnEdit);
    pHBox->addWidget(pBtnClose);

    pVBox->addWidget(pDateLbl);

    pVBox->addWidget(pPriceLbl);
    pVBox->addWidget(pLinePrice);

    pVBox->addWidget(pCategoryLbl);

    pVBox->addWidget(pCommentLbl);
    pVBox->addWidget(pLineComment);

    pVBox->addLayout(pHBox);

    pWgtData->setLayout(pVBox);
    pWgtData->setFixedSize(400,200);
    pWgtData->setWindowFlags(Qt::FramelessWindowHint);

    this->price = price;
    this->category = category;
    this->date = date;
    this->comment = comment;
    this->color = color;

    //через этот счетчик проверяется состояние pLinePrice и pLineComment
    //т.е. информацию в них можно изменять или нет
    count = 1;

    //соединение кнопки для закрытия виджета
    QObject::connect(pBtnClose, SIGNAL(clicked(bool)), SLOT(slotBtnClose()));
    //соединение кнопки для возможности изменения pLinePrice и pLineComment
    QObject::connect(pBtnEdit, SIGNAL(clicked(bool)), SLOT(slotBtnEdit()));
    //соединение кнопки для удаления объекта класса Item
    QObject::connect(pBtnDelete, SIGNAL(clicked(bool)), SLOT(slotBtnDelete()));
}

void Item::isClicked()
{
    //отображение виджета
    pLinePrice->setText(QString::number(price));

    pCategoryLbl->setText(category);

    pLineComment->setText(comment);

    pDateLbl->setText(date.toString("d.MM.yyyy"));

    pWgtData->show();
}

QDate Item::getDate()
{
    return date;
}

void Item::setDate(QDate date)
{
    this->date = date;
}

QString Item::getCategory()
{
    return category;
}

void Item::setCategory(QString category)
{
    this->category = category;
}

float Item::getPrice()
{
    return price;
}

void Item::setPrice(float price)
{
    this->price = price;
}

QString Item::getComment()
{
    return comment;
}

void Item::setComment(QString comment)
{
    this->comment = comment;
}

QColor Item::getColor()
{
    return color;
}

void Item::setColor(QColor color)
{
    this->color = color;
}

void Item::slotBtnClose()
{
    //закрытие виджета и отправка сигнала объекту класса OutputItemWidget
    //для обновления всего отображаемого листа данных
    this->price = pLinePrice->text().toInt();
    this->comment = pLineComment->text();
    pWgtData->close();
    emit updateOutputWgt();
}

void Item::slotBtnEdit()
{
    //изменение состояния pLineComment и pLinePrice
    //для возможности вводить в них другие данные
    if(count)
    {
        pLinePrice->setReadOnly(false);
        pLineComment->setReadOnly(false);
        count = 0;
    }
    else
    {
        pLinePrice->setReadOnly(true);
        pLineComment->setReadOnly(true);
        count = 1;
    }
}

void Item::slotBtnDelete()
{
    pWgtData->close();
    emit deleteItem(this);
}

Item::~Item()
{
    delete pBtnClose;
    delete pBtnEdit;
    delete pBtnDelete;
    delete pPriceLbl;
    delete pLinePrice;
    delete pCategoryLbl;
    delete pDateLbl;
    delete pCommentLbl;
    delete pLineComment;
    delete pHBox;
    delete pVBox;
    delete pWgtData;
}
