#ifndef LEV_2_WINDOW_H
#define LEV_2_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QUrl>
#include <QMovie>
#include "static_object.h"
#include <ctime>
#include "global.h"

// Уровень 2

class Lev_2_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_2_Window();

public:
    explicit Lev_2_Window(QWidget *parent = nullptr);

    QLabel              *Background;                                // фоновая картинка
    QLabel              *Subject_Area;                              // область найденных предметов
    QPushButton         *Button_Return;                             // кнопка назад
    Static_Object       *Dedka;                                     // дедка
    Static_Object       *Mysl;                                      // мысль
    Static_Object       *Tools [8];                                 // указатель на массив инструментов
    Static_Object       *Tools_Ded[8];                              // Текущий инструмент о котором думает дедка
    Static_Object       *Hand;                                      // Рука для подсказки
    QMediaPlayer        *yes;                                       // звуки
    QMediaPlayer        *no;
    QMediaPlayer        *victory;
    QMediaPlayer        *salut_wav;
    QTimer              *timer_move;                                // таймер для перемещения предметов
    QTimer              *timer_salut;                               // таймер для салюта
    QTimer              *timer_hand;                                      // таймер для подсказки
    QMovie              *movie;                                     // анимация салюта
    QLabel              *Salut;                                     // анимация салюта
    QLabel              *Help;                                      // подсказка

    int                 level;                                      // номер уровня
    int                 tool;                                       // текущий инструмент
    int                 tools_x[8];                                 // координата х инструмента
    int                 tools_y[8];                                 // координата y инструмента
    int                 tools_x_end[8];                             // конечная координата после перемещения
    int                 tools_y_end[8];

    int                 rnd(int a, int b);                          // генератор случайных чисел в диапазоне от a до b
    void                init();                                     // инициализация массива инструментов

signals:
    void                number_level(int);                          // сигнал передает номер экрана

public slots:
    void return_to_mainwindow();                                    // возврат в главное меню
    void move_tool();                                               // перемещение инструмента в область собранных инструментов
    void salut_show();                                              // показать салют
    void move_hand();                                               // анимирует подсказку

protected:
    virtual void mousePressEvent(QMouseEvent *pe);                  // события по нажатию кнопки мышки

};

#endif // LEV_2_WINDOW_H
