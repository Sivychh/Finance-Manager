#include <QApplication>
#include <QtCharts>
#include "profilewidget.h"
#include "menulistwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    //главный виджет
    QWidget wgt;
    //виджет для списка меню и для иконки профиля
    QWidget wgt2;

    MenuListWidget menu(&wgt);

    ProfileWidget profileWgt(&wgt);

    QVBoxLayout *pVBox = new QVBoxLayout;
    pVBox->addWidget(&profileWgt);
    pVBox->addWidget(menu.getPListWidget());
    wgt2.setLayout(pVBox);
    wgt2.setFixedWidth(200);

    QHBoxLayout *pHBox = new QHBoxLayout;
    pHBox->addWidget(&wgt2);
    pHBox->addWidget(&menu);

    wgt.setLayout(pHBox);
    wgt.setMinimumSize(800,500);
    wgt.show();

    //соединение для вызова страницы профиля пользователя
    QObject::connect(&profileWgt.draw, SIGNAL(clickedIcon(QString)), &menu, SLOT(slotChangedLayout(QString)));
    //соединения для смены всех изображений пользователя
    QObject::connect(&menu, SIGNAL(resendPhoto(QPixmap*)), &profileWgt.draw, SLOT(slotChangePhoto(QPixmap*)));
    //соединение для смена имени пользователя
    QObject::connect(&menu, SIGNAL(sendNewName(QString)), profileWgt.pTextName, SLOT(setText(QString)));

    return app.exec();
}
