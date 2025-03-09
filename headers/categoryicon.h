#ifndef CATEGORYICON_H
#define CATEGORYICON_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPainter>
#include <QMouseEvent>

/*
Данный класс используется классом AddItemWidget для
отображения иконок категорий. Каждый объект представляет
собою вертикальную таблицу состоящую из кругового изображения
и названия категории, а внутри себя объект содержит цвет категории
*/
class CategoryIcon : public QLabel
{
    Q_OBJECT
private:

    QString nameOfCategory;
    QColor color;
    QPixmap pixmap;
    QPainter painter;

    QVBoxLayout *pVBox;
    QLabel *pLabel;
    QLabel *pTextLabel;

public:

    CategoryIcon(QPixmap pixmap, QString nameOfCategory, QColor color, QWidget *pwgt = 0);
    ~CategoryIcon();

protected:

    void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *pevent) override;

signals:
    void clicked(QString nameOfCategory, QColor color);
};

#endif // CATEGORYICON_H
