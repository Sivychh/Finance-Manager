#include "profileeditwidget.h"

ProfileEditWidget::ProfileEditWidget(QWidget *pwgt) : QWidget(pwgt)
{
    //создание виджета
    pLineEditName = new QLineEdit;
    pLabelName = new QLabel("Имя профиля:");
    pVBox = new QVBoxLayout;

    pLabelName->setBuddy(pLineEditName);
    pLabelName->setFixedSize(140,50);

    pLineEditName->setFixedWidth(100);
    pLineEditName->setFixedSize(140, 25);

    drawingIcon.setParent(this);
    drawingIcon.setFixedSize(140,140);
    drawingIcon.setIconSize(QSize(140,140));

    pVBox->addWidget(&drawingIcon);
    pVBox->addSpacing(10);
    pVBox->addWidget(pLabelName);
    pVBox->addWidget(pLineEditName);
    pVBox->setSpacing(0);

    pVBox->setAlignment(Qt::AlignCenter);
    pVBox->addStretch();

    setLayout(pVBox);

    //сигнал для возможности открытия проводника Windows
    QObject::connect(&drawingIcon, SIGNAL(openFolder()), &drawingIcon, SLOT(slotOpenFolder()));
}

ProfileEditWidget::~ProfileEditWidget()
{
    delete pLineEditName;
    delete pLabelName;
    delete pVBox;
}
