#ifndef LEV_7_WINDOW_H
#define LEV_7_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QMovie>
#include "global.h"
#include "static_object.h"

class Lev_7_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_7_Window();

public:
    Lev_7_Window(QWidget *parent = nullptr );

    QLabel                  *Background;                                    // фон
    QPushButton             *Button_Return;                                 // кнопка назад
    Static_Object           *Myschka;                                       // Мышка
    Static_Object           *Mysl;                                          // Мысль
    Static_Object           *Mysl_1;                                        // Мысль о картине в сборе
    Static_Object           *Plitka[16];                                    // Плитки
    Static_Object           *Chees;                                         // сыр
    QTimer                  *pobeda_timer;                                  // таймер победы
    QMovie                  *movie;                                         // анимация
    QLabel                  *Mouse;                                         // танцующая мышь

    int                     level;                                          // номер уровня
    int                     plitka_sost[16];                                // состояние плитки, на сколько градусов повернута
                                                                            // 0-0, 1-90, 2-180, 3-270
    int                     radian[16];                                     // градусы поворота плитки 0, 90, 180, 270
    int                     index;                                          // номер текущей плитки

    int                     rnd(int, int);                                  // генератор случайных чисел
    void                    init();                                         // расстановка плиток



public slots:
    void return_to_mainwindow();                                            // возврат на карту
    void pobeda();

protected:
    virtual void mousePressEvent(QMouseEvent   *pe);                        // события при нажатии кнопки мышки


signals:
    void                number_level(int);                                  // сигнал передает номер экрана

};

#endif // LEV_7_WINDOW_H
