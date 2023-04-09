#ifndef LEV_4_WINDOW_H
#define LEV_4_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QUrl>
#include <QMovie>
#include "static_object.h"

class Lev_4_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_4_Window();

public:
    explicit Lev_4_Window(QWidget *parent = nullptr);

    QLabel                  *Background;                                    // Фон экрана
    QPushButton             *Button_Return;                                 // кнопка назад
    QLabel                  *Subject_Area;                                  // область карандашей
    Static_Object           *Vnuchka;                                       // Внучка раскраска
    Static_Object           *Pen;                                           // Карандаши
    Static_Object           *Mysl_Object;                                   // Объекты в мыслях
    Static_Object           *Masha;                                         // Внучка
    Static_Object           *Mysl;                                          // Мысль
    Static_Object           *Holst;                                         // Холст
    QMediaPlayer            *yes;
    QMediaPlayer            *no;
    QMediaPlayer            *ura;
    QMovie                  *movie;                                         // анимация
    QLabel                  *Shariki;                                       // анимация
    QTimer                  *viktory;                                       // Таймер победа (шарики)
    QTimer                  *timer_help;                                    // таймер подсказки
    Static_Object           *Hand1;                                         // рука для подсказки


    int level;                                                              // номер уровня
    int index;                                                              // номер взятого карандаша
    int number;                                                             // номер нужного карандаша
    int old_x;                                                              // начальные координаты карандаша
    int old_y;
    int old_x1;                                                             // начальные координаты первого карандаша для подсказки
    int old_y1;
    bool                    FLAG_START_GAME;                                // true - игрок хоть один раз кликнул мышкой

    int                 rnd(int a, int b);                                  // генератор случайных чисел в диапазоне от a до b
    void init();                                                            // инициализация, расстановка карандашей

signals:
    void                number_level(int);                                  // сигнал передает номер экрана

public slots:

    void return_to_mainwindow();                                            // возврат на карту
    void pobeda();                                                          // Победа
    void help_game();                                                       // подсказка в игре

protected:
    virtual void mousePressEvent(QMouseEvent   *pe);                        // события при нажатии кнопки мышки
    virtual void mouseMoveEvent(QMouseEvent    *pe);                        // события при движении мышки
    virtual void mouseReleaseEvent(QMouseEvent *pe);                        // события при отпускании кнопки мышки


};

#endif // LEV_4_WINDOW_H
