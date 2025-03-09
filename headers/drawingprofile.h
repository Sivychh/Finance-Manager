#ifndef DRAWINGPROFILE_H
#define DRAWINGPROFILE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QFileInfo>

/*
Данный класс используется классами ProfileWidget и ProfileEditWidget
для класса ProfileWidget он нужен для отображения кругового изображения
в левом верхнем углу всей программы, при нажатии на изображение
открывается виджет класса ProfileEditWidget, в котором уже есть
такое же изображение большего размера и при нажатие на которое
можно изменить данное изображение выбрав фото при помощи проводника Windows
*/

class DrawingProfile : public QWidget
{
    Q_OBJECT
private:

    QSize size;
    QPointF point;
    QPainter painter;
    QString filePath;
    QPixmap *pPixmap;

public:

    DrawingProfile(QWidget *pparent = 0);
    ~DrawingProfile();

    void setIconSize(QSize);
    void setPoint(QPointF);

protected:

    void paintEvent(QPaintEvent *pevent) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void slotOpenFolder();
    void slotChangePhoto(QPixmap*);

signals:

    void clickedIcon(QString);
    void openFolder();
    void changePhoto(QPixmap*);
};
#endif // DRAWINGPROFILE_H
