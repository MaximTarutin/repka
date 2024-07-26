#include "static_object.h"
#include <QLabel>

Static_Object::Static_Object(QWidget *parent): QLabel(parent)
{

}

Static_Object::Static_Object(QString str, QWidget *parent)
    : QLabel(parent), path_to_image(str)
{
    QPixmap pic(str);
    setPixmap(pic);
    resize(this->sizeHint());   // растягивает QLabel под размер картинки
}

Static_Object::Static_Object(QString str, int a, int b, QWidget *parent)
    : QLabel(parent), width_object(a), height_object(b), path_to_image(str)
{
    resize(width_object, height_object);
    QPixmap pic(str);
    QSize PicSize(this->width(), this->height());               // Здесь вписываем картинку в размер QLabel
    pic = pic.scaled(PicSize,Qt::KeepAspectRatio);
    setPixmap(pic);
}

Static_Object::~Static_Object()
{

}

void Static_Object::resize_obj(int w, int h)
{
    resize(w,h);
    QPixmap pic(path_to_image);
    QSize PicSize(this->width(), this->height());               // Здесь вписываем картинку в размер QLabel
    pic = pic.scaled(PicSize,Qt::KeepAspectRatio);
    setPixmap(pic);
}

void Static_Object::pic_obj(QString str)        // Здесь проблема (виснет запуск)
{
    //QLabel lab;
    //lab.setStyleSheet("border-image: "+str+";");
    // QPixmap pic(str);
    // QSize PicSize(this->width(), this->height());               // Здесь вписываем картинку в размер QLabel
    // pic = pic.scaled(PicSize,Qt::KeepAspectRatio);
    // setPixmap(pic);
}

void Static_Object::pic_rotate(int r)
{
    // QPixmap pic(path_to_image);
    // QSize PicSize(this->width(), this->height());               // Здесь вписываем картинку в размер QLabel
    // QPixmap rotatePixmap(pic);//создаём промежуточный Pixmap
    //         rotatePixmap.fill(Qt::transparent);//Заполняем его прозрачным
    //         QPainter p(&rotatePixmap);//Создаем Painter
    //         p.setRenderHint(QPainter::Antialiasing); // сглаживание
    //         p.setRenderHint(QPainter::SmoothPixmapTransform); //смягчение, советую убрать, а то картинка расплывается
    //         p.setRenderHint(QPainter::HighQualityAntialiasing);// ещё сглаживание
    //         p.translate(rotatePixmap.size().width() / 2, rotatePixmap.size().height() / 2); //перенос начала системы координат в центр картинки
    //         p.rotate(r); // градус, вращение системы координат её относительно начала
    //         p.translate(-rotatePixmap.size().width() / 2, -rotatePixmap.size().height() / 2);//систему координат обратно в левый верхний угол для нормальной отрисовки
    //         p.drawPixmap(0, 0, pic);//рисуем изображение в новой системе координат
    //         p.end();//просто нужен
    //         pic = rotatePixmap;//запоминаем текущее состояние
    //         pic = pic.scaled(PicSize,Qt::KeepAspectRatio);
    //         setPixmap(pic);//выводим картинку
}
