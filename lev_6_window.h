#ifndef LEV_6_WINDOW_H
#define LEV_6_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QMovie>
#include "static_object.h"
#include "global.h"

class Lev_6_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_6_Window();

public:
    explicit Lev_6_Window(QWidget *parent = nullptr );

    QLabel                  *Background;                                    // Фон
    QPushButton             *Button_Return;                                 // Кнопка возврата на карту
    Static_Object           *Cat;                                           // Кошка
    Static_Object           *Plitka_fon[16];                                // Тыльная сторона плитки
    Static_Object           *Plitka[16];                                    // Плитки
    QTimer                  *pause_timer;                                   // таймеры
    QTimer                  *pause1_timer;
    QTimer                  *pobeda;
    QTimer                  *help_timer;
    QMediaPlayer            *yes;                                           // звуки
    QMediaPlayer            *bah;
    QMovie                  *movie;                                         // анимация
    QLabel                  *Bah;                                           // анимация
    Static_Object           *Hand;                                          // подсказка
    Static_Object           *Hand_1;

    int                     level;                                          // Номер уровня
    int                     num_open_plitka;                                // Количество открытых плиток
    int                     current_plitka;                                 // текущая плитка
    int                     num_1;                                          // номер первой открытой плитки
    int                     num_2;                                          // номер второй открытой плитки
    bool                    FLAG_PAUSE;                                     // запрет открытия плиток при паузе, true - открывать можно
    bool                    FLAG_PLITKA[16];                                // Убрана ли плитка с поля, true - убрана
    int                     victory_plitka;                                 // количество угаданных плиток

    int                     rnd(int, int);                                  // генератор случайных чисел
    void                    init();                                         // Расстановка кусков пазла
    void                    check_victory();                                // проверка на победу
    void                    victory();                                      // победа

public slots:
    void return_to_mainwindow();                                            // возврат на карту
    void pause();                                                           // пауза при показе открытых плиток
    void pause_1();                                                         // пауза при показе выигрышных плиток
    void hand_move();                                                       // подсказка

protected:
    virtual void mousePressEvent(QMouseEvent   *pe);                        // события при нажатии кнопки мышки

signals:
    void                number_level(int);                                  // сигнал передает номер экрана
};

#endif // LEV_6_WINDOW_H
