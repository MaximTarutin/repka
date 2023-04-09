#ifndef LEV_3_WINDOW_H
#define LEV_3_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QTimer>
#include "static_object.h"

class Lev_3_Window : public QMainWindow
{
    Q_OBJECT
    ~Lev_3_Window();

public:
    explicit Lev_3_Window(QWidget *parent = nullptr);

    QLabel              *Background;                                // Фоновая картинка
    QPushButton         *Button_Return;                             // кнопка назад
    Static_Object       *Stol;                                      // стол
    Static_Object       *Babka;                                     // Бабка
    Static_Object       *Mysl;                                      // мысль
    Static_Object       *Produkt;                                   // массив продуктов
    Static_Object       *Produkt_Babka;                             // продукт о котором думает бабка
    Static_Object       *Tazik;                                     // варианты тазика
    Static_Object       *Hand;                                      // рука
    QTimer              *timer_help;                                // таймер подсказки
    QTimer              *timer_help_kolobok;                        // таймер подсказки: тесто в печку
    QTimer              *timer_show_kolobok;                        // таймер появления колобка
    QTimer              *timer_move_kolobok;                        // перемещение колобка

    QMediaPlayer        *yes;                                       // звуки
    QMediaPlayer        *no;
    QMediaPlayer        *stuk;
    QMediaPlayer        *shows;

    bool                FLAG_PRODUKT;                               // флаг выбран ли нужный предмет или кликнули по пустому месту
    bool                FLAG_KOLOBOK;                               // флаг готово ли тесто, чтобы испечь колобка в печи
    bool                FLAG_MOVE_KOLOBOK_X;                        // флаг движения колобка по Х: false - вправо
    bool                FLAG_MOVE_KOLOBOK_Y;                        // флаг движения колобка по Y: false - вниз

    int                 level;                                      // номер уровня
    int                 index;                                      // номер актуального предмета
    int                 old_x;                                      // хранение прежних координат предмета
    int                 old_y;
    int                 kol_x, kol_y;                               // координаты колобка

    int                 rnd(int a, int b);                          // генератор случайных чисел в диапазоне от a до b
    void                init();                                     // инициализация массива продуктов


public slots:
    void return_to_mainwindow();                                    // возврат в главное меню
    void help_game();                                               // подсказка вначале уровня
    void help_game_kolobok();                                       // подсказка: тесто в печку
    void show_kolobok();                                            // показать колобка
    void move_kolobok();                                            // перемкещение колобка

signals:
    void                number_level(int);                          // сигнал передает номер экрана

protected:
    virtual void mousePressEvent(QMouseEvent   *pe);            // события при нажатии кнопки мышки
    virtual void mouseMoveEvent(QMouseEvent    *pe);            // события при движении мышки
    virtual void mouseReleaseEvent(QMouseEvent *pe);            // события при отпускании кнопки мышки

};

#endif // LEV_3_WINDOW_H
