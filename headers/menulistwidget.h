#ifndef MENULISTWIDGET_H
#define MENULISTWIDGET_H

#include "outputitemswidget.h"
#include "additemwidget.h"
#include "diagramwidget.h"
#include "profilewidget.h"
#include "calendarwidget.h"
#include "profileeditwidget.h"
#include "drawingprofile.h"
#include "graphicswidget.h"

/*
Данный класс связывается все остальные классы и выводит их в одном виджете
так же этот класс предоставляет QListWidget, который отображается списком в левой части
главного виджета, при выборе одного из элементов списка виджет этого класса удаляет
добавленные в него виджеты и отрисовывает другие необходимые виджеты
*/

class MenuListWidget : public QWidget
{
    Q_OBJECT
private:

    QVBoxLayout *pOutputLayout = new QVBoxLayout; //таблица в которую добавляются все необходимые виджеты

    QVBoxLayout *pVBox;
    QHBoxLayout *pHBox;
    QHBoxLayout *pHBoxPrice;

    QLabel *pTotalPriceLbl;
    QLabel *pText1Lbl;
    QLabel *pText2Lbl;

    GraphicsWidget *pGraphicsWgt;
    OutputItemWidget *pOutputItemWgt;

    CalendarWidget *pCalendarWgt;
    DiagramWidget *pDiagramWgt;
    AddItemWidget *pAddWidget;
    ProfileEditWidget *pProfileEditWgt;

    QString isRepeat;

    QVector<StorageItems*> vecOfStorageItems;

    QPixmap *pPixmap;

    QStringList strList;

    QPushButton *pBtn;

    QListWidget *pListWidget = new QListWidget;
    QListWidgetItem *pListItem;

    void clearLayout(QLayout* layout);

public:

    MenuListWidget(QWidget *pwgt = 0);

    QListWidget* getPListWidget();

signals:

    void changeLayout(QString);
    void resendPhoto(QPixmap*);
    void sendNewName(QString);

public slots:

    void slotNameProfileChanged(QString);
    void slotResendPhoto(QPixmap*);
    void slotSaveVector(QVector<StorageItems*>);
    void slotChangedLayout(QString);
    void slotListItemActivated(QListWidgetItem*);
};

#endif // MENULISTWIDGET_H
