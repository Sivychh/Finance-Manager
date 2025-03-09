#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QLayout>
#include <QLabel>
#include "drawingprofile.h"

/*
Данный класс нужен для отображения небольшого виджета
в верхнем левом углу главного виджета в котором будет отображено
имя и изображение профиля  пользователя, при нажатии на изображение
откроется виджет объекта класса ProfileEditWidget
*/

class ProfileWidget : public QWidget
{
    Q_OBJECT
private:

    QIcon icon;
    QHBoxLayout *pHBox;
    QVBoxLayout *pVBox;
    QString name;

    void saveName();
    void loadName();

public:

    QLabel *pTextName;
    DrawingProfile draw;

    ProfileWidget(QWidget *wgt = 0);
    ~ProfileWidget();
};
#endif // PROFILEWIDGET_H
