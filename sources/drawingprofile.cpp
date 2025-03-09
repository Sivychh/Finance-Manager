#include "drawingprofile.h"

DrawingProfile::DrawingProfile(QWidget *pwgt) : QWidget(pwgt)
{
    //загрузка последнего сохраненного изображения
    pPixmap = new QPixmap;
    pPixmap->load(QDir::currentPath() + "/Picture/Avatarka");

    size.setHeight(75);
    size.setWidth(75);
    point.setX(0);
    point.setY(0);
}

void DrawingProfile::paintEvent(QPaintEvent *pevent)
{
    //отрисовка изображения
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::black, pPixmap->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    painter.drawEllipse(QRectF(point, size));

    painter.end();
}

void DrawingProfile::mousePressEvent(QMouseEvent *event)
{
    //перегрузка события клика мыши
    if (event->button() == Qt::LeftButton)
    {
        //сигнал отправляется классу MenuListWidget для отображения
        //виджета класса ProfileEditWidget
        emit clickedIcon(QString("Профиль"));

        //если клик мыши произошел в виджете класса ProfileEditWidget
        //то откроется проводник Windows
        emit openFolder();
    }
}

void DrawingProfile::setIconSize(QSize size)
{
    this->size = size;
}

void DrawingProfile::setPoint(QPointF point)
{
    this->point = point;
}

void DrawingProfile::slotOpenFolder()
{
    //открытие проводника Windows
    filePath.clear();
    filePath = QFileDialog::getOpenFileName(nullptr, "Выберите изображения профиля",
                                                    "C:/", "Файлы изображений (*.png *.jpg)");

    QFileInfo fileInfo(filePath);

    if(!filePath.isEmpty())
    {
        if(fileInfo.suffix() == "png" || fileInfo.suffix() == "jpg")
        {
            this->pPixmap->load(filePath);
        }
    }

    //очистка предыдущих изображений
    QFile::remove(QDir::currentPath() + "/Picture/Avatarka.jpg");
    QFile::remove(QDir::currentPath() + "/Picture/Avatarka.png");

    pPixmap->save(QDir::currentPath() + "/Picture/Avatarka." + fileInfo.suffix());

    //сигнал, чтобы все объекты DrawingProfile сменили изображение
    emit changePhoto(pPixmap);
}

void DrawingProfile::slotChangePhoto(QPixmap *pPixmap)
{
    //смена изображения
    this->pPixmap->load(QDir::currentPath() + "/Picture/Avatarka");
}

DrawingProfile::~DrawingProfile()
{
    delete pPixmap;
}
