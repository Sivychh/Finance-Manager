#include "profilewidget.h"

ProfileWidget::ProfileWidget(QWidget* pwgt) : QWidget(pwgt)
{
    //создание виджета
    pTextName = new QLabel;
    pTextName->setText("Пользователь");
    loadName(); //загрузка имени из файла
    pTextName->setFixedSize(100,30);
    pTextName->setAlignment(Qt::AlignCenter);

    pVBox = new QVBoxLayout;
    pVBox->addWidget(pTextName);

    pHBox = new QHBoxLayout;
    draw.setFixedSize(75,75);
    pHBox->addWidget(&draw);
    pHBox->addLayout(pVBox);
    setLayout(pHBox);
    setFixedSize(200,100);
}

void ProfileWidget::saveName()
{
    //сохранение имени пользователя в файле
    name = pTextName->text();

    QFile file("Name.dat");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << name;
        file.close();
    }
}

void ProfileWidget::loadName()
{
    //загрузка имени пользователя из файла
    QFile file("Name.dat");
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> name;
        pTextName->setText(name);
        file.close();
    }
}

ProfileWidget::~ProfileWidget()
{
    saveName();
    delete pTextName;
    delete pHBox;
    delete pVBox;
}
