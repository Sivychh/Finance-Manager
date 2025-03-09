#include "categoryicon.h"

CategoryIcon::CategoryIcon(QPixmap pixmap, QString nameOfCategory, QColor color, QWidget *pwgt) : QLabel(pwgt)
{
    pVBox = new QVBoxLayout;

    //индикатор выступает в роли эдакого тела изображения, чтобы
    //название категории не перекрывалось изображением
    pLabel = new QLabel;

    this->pixmap = pixmap;
    this->nameOfCategory = nameOfCategory;
    this->color = color;

    pTextLabel = new QLabel(nameOfCategory);
    pTextLabel->setAlignment(Qt::AlignCenter);

    setFixedSize(125,130);
    pTextLabel->setFixedSize(85,20);

    pVBox->addWidget(pLabel);
    pVBox->addWidget(pTextLabel);
    setLayout(pVBox);
}

void CategoryIcon::mousePressEvent(QMouseEvent *event)
{
    //перегрузка события клика мыши
    //после клика отправляется сигнал классу AddItemWidget, о том
    //какая категория выбрана
    if (event->button() == Qt::LeftButton)
    {
        emit clicked(nameOfCategory, color);
    }
}

void CategoryIcon::paintEvent(QPaintEvent *pevent)
{
    //отрисовка изображения
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black, pixmap.scaled(QSize(100,100), Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    painter.drawEllipse(0,0,100,100);

    painter.end();
}

CategoryIcon::~CategoryIcon()
{
    delete pLabel;
    delete pTextLabel;
    delete pVBox;
}
