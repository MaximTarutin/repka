#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include <QObject>
#include <QLabel>
#include <QString>
#include <QWidget>
#include <QPixmap>
#include <QPainter>

class Static_Object: public QLabel
{
    Q_OBJECT

private:

    int width_object;                                   // ширина объекта
    int height_object;                                  // высота объекта
    QString     path_to_image;                          // путь к файлу изображения объекта
    QPixmap     pic;


public:
    Static_Object(QWidget *parent = nullptr);
    Static_Object(QString str, QWidget *parent = nullptr);
    Static_Object(QString str, int a = 0, int b = 0, QWidget *parent = nullptr);
    ~Static_Object();

    void resize_obj(int w, int h);                      // изменение размеров объекта
    void pic_rotate(int r);                             // Поворот обьекта на r градусов
};

#endif // STATIC_OBJECT_H
