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

class Lev_2_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_2_Window();

public:
    explicit Lev_2_Window(QWidget *parent = nullptr);

    QLabel              *Background = nullptr;                                // фоновая картинка
    QLabel              *Subject_Area = nullptr;                              // область найденных предметов
    QPushButton         *Button_Return = nullptr;                             // кнопка назад
    Static_Object       *Dedka = nullptr;                                     // дедка
    Static_Object       *Mysl = nullptr;                                      // мысль
    Static_Object       *Tools [8];                                 // указатель на массив инструментов
    Static_Object       *Tools_Ded[8];                              // Текущий инструмент о котором думает дедка
    Static_Object       *Hand = nullptr;                                      // Рука для подсказки
    QMediaPlayer        *yes = nullptr;                                       // звуки
    QMediaPlayer        *no = nullptr;
    QMediaPlayer        *victory = nullptr;
    QMediaPlayer        *salut_wav = nullptr;
    QTimer              *timer_move = nullptr;                                // таймер для перемещения предметов
    QTimer              *timer_salut = nullptr;                               // таймер для салюта
    QTimer              *timer_hand = nullptr;                                      // таймер для подсказки
    QMovie              *movie = nullptr;                                     // анимация салюта
    QLabel              *Salut = nullptr;                                     // анимация салюта
    QLabel              *Help = nullptr;                                      // подсказка

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
