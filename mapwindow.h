#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMouseEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include "static_object.h"
#include "lev_2_window.h"
#include "lev_3_window.h"
#include "lev_4_window.h"
#include "lev_5_window.h"
#include "lev_6_window.h"
#include "lev_7_window.h"
#include "global.h"

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow();

    QLabel          *Background;                    // фон
    QPushButton     *Button_Return;                 // кнопка назад
    QPushButton     *Button_Next;                   // кнопка перейти к следущему уровню

    Lev_2_Window    *level2win;                     //  2 уровень   -   Дедка
    Lev_3_Window    *level3win;                     //  3 уровень   -   Бабка
    Lev_4_Window    *level4win;                     //  4 уровень   -   Внучка
    Lev_5_Window    *level5win;                     //  5 уровень   -   Жучка
    Lev_6_Window    *level6win;                     //  6 уровень   -   Кошка
    Lev_7_Window    *level7win;                     //  7 уровень   -   Мышка

    Static_Object   *Repka;                         // Репка
    Static_Object   *Dedka;                         // Дедка
    Static_Object   *Babka;                         // Бабка
    Static_Object   *Vnuchka;                       // Внучка
    Static_Object   *Zuchka;                        // Жучка
    Static_Object   *Koshka;                        // Кошка
    Static_Object   *Myshka;                        // Мышка
    Static_Object   *Gray_Chesnok;                  // серый чеснок
    Static_Object   *Chesnok;                       // чеснок
    Static_Object   *Grusha;                        // груша
    Static_Object   *Gray_Grusha;                   // серая груша
    Static_Object   *Kartoshka;                     // картошка
    Static_Object   *Gray_Kartoshka;                // серая картошка
    Static_Object   *Morkovka;                      // морковка
    Static_Object   *Gray_Morkovka;                 // серая морковка
    Static_Object   *Ogurec;                        // огурец
    Static_Object   *Gray_Ogurec;                   // серый огурец
    Static_Object   *Rediska;                       // редиска
    Static_Object   *Gray_Rediska;                  // серая редиска
    Static_Object   *Tykva;                         // тыква
    Static_Object   *Gray_Tykva;                    // серая тыква
    Static_Object   *Tomat;                         // помидор
    Static_Object   *Gray_Tomat;                    // серый помидор
    Static_Object   *Hand;                          // рука для подсказки
    Static_Object   *The_End;                       // Надпись конец игры

    QTimer          *hinttimer;                     // таймер для победы
    QTimer          *hand_timer;                    // таймер для подсказки
    QTimer          *persona_timer;                 // таймер для появления дедки
    QTimer          *victory_timer;                 // таймер появления надписи победы

    QMediaPlaylist  *playlist;                      // фоновая музыка
    QMediaPlayer    *fon_sound;                     // Звуки
    QMediaPlayer    *yes;
    QMediaPlayer    *no;
    QMediaPlayer    *Repka_Wav;
    QMediaPlayer    *Viktory;
    QMediaPlayer    *Tada;



    int             level;                          // номер уровня
    int             active_vegetables;              // активный овощ (объект)
                                                    // 1 - репка
                                                    // 2 - чеснок
                                                    // 3 - груша
                                                    // 4 - картошка
                                                    // 5 - морковка
                                                    // 6 - огурец
                                                    // 7 - редиска
                                                    // 8 - тыква

    int             old_vegetables_x;               // начальные координаты овощей
    int             old_vegetables_y;

    bool            FLAG_VEGETABLES;                // true - выбран объект, false - нет
    bool            FLAG_START_GAME;                // true - игрок хоть один раз кликнул мышкой
    bool            FLAG_WAV;                       // флаг проигрывания звука персонажа


    void            check_flag_vegetables(Static_Object *vegetables,
                                          Static_Object *vegetables_yes,
                                          QMouseEvent   *pe);               // проверка состояния флага выбран или нет объект (овощ)
    void            move_vegetables(Static_Object *vegetables,
                                    QMouseEvent   *pe);                     // перемещение объекта
    void            Victory();                                              // Победа и смена экрана



signals:
    void number_level(int);                         // Сигнал передает номер уровня


public slots:
    void return_to_mainwindow();                    // возврат на главный экран
    void return_to_mapwindow(int num);              // возврат на карту
    void hint();                                    // событие по таймеру, овощи разлетаются
    void help_level();                              // подсказка в игре
    void priem_level(int lev);                      // принимаем номер уровня
    void next_level();                              // переход на следующий уровень
    void persona_show();                            // появляется очередной персонаж
    void the_end_game();                                 // появляется надпись о конце игры

protected:
    virtual void mousePressEvent(QMouseEvent   *pe);            // события при нажатии кнопки мышки
    virtual void mouseMoveEvent(QMouseEvent    *pe);            // события при движении мышки
    virtual void mouseReleaseEvent(QMouseEvent *pe);            // события при отпускании кнопки мышки


};

#endif // MAPWINDOW_H
