#ifndef LEV_5_WINDOW_H
#define LEV_5_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QMovie>
#include <QMediaPlayer>
#include <QTimer>
#include "static_object.h"

class Lev_5_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_5_Window();

public:
    explicit Lev_5_Window(QWidget *parent = nullptr);

    QLabel                  *Background;                                    // Фон
    QPushButton             *Button_Return;                                 // Кнопка возврата на карту
    Static_Object           *Dog;                                           // Жучка
    Static_Object           *Area_Puzzle;                                   // Область для сборки пазла
    Static_Object           *Mysl;                                          // Мысль
    Static_Object           *Mysl_1;                                        // Мысль о картине в сборе
    Static_Object           *Pazl;                                          // Части пазла
    QMovie                  *movie;                                         // анимация
    QLabel                  *Smile;                                         // анимация
    QTimer                  *viktory_timer;                                 // Таймер победа
    QMediaPlayer            *yes;
    QMediaPlayer            *lay;
    Static_Object           *Hand;                                          // рука
    QTimer                  *timer_help;                                    // таймер подсказки

    int                     level;                                          // Номер уровня
    int                     old_x1;                                         // хранение начальных координат первого пазла
    int                     old_y1;

    int                     rnd(int, int);                                  // генератор случайных чисел
    void                    init();                                         // Расстановка кусков пазла


    bool                    FLAG_PAZZLE[10];                                 // Флаг указывающий можно ли перемещать
                                                                            // пазл, true - можно, false - пазл уже на месте
    int                     number_pazzle;                                  // номер перемещаемого пазла

protected:
    virtual void mousePressEvent(QMouseEvent   *pe);                        // события при нажатии кнопки мышки
    virtual void mouseMoveEvent(QMouseEvent    *pe);                        // события при движении мышки
    virtual void mouseReleaseEvent(QMouseEvent *pe);                        // события при отпускании кнопки мышки

public slots:
    void return_to_mainwindow();                                            // возврат на карту
    void viktory();                                                         // победа
    void help_game();                                                       // подсказка вначале уровня

signals:
    void                number_level(int);                                  // сигнал передает номер экрана

};

#endif // LEV_5_WINDOW_H
