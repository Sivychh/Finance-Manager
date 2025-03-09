#ifndef PROFILEEDITWIDGET_H
#define PROFILEEDITWIDGET_H

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include "drawingprofile.h"

/*
Данный класс нужен для создания виджета, который предоставляет возможность
пользователю изменить имя и изображение профиля
*/

class ProfileEditWidget : public QWidget
{
    Q_OBJECT
private:

    QVBoxLayout* pVBox;

    QLabel* pLabelName;

public:

    ProfileEditWidget(QWidget *pwgt = 0);
    ~ProfileEditWidget();

    QLineEdit* pLineEditName;

    DrawingProfile drawingIcon;
};

#endif // PROFILEEDITWIDGET_H
