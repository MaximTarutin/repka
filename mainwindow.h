#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include "mapwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLabel          *Background;                        //  Заставка
    QPushButton     *Button_Start;                      //  Кнопка начать игру
    QPushButton     *Button_Exit;                       //  Кнопка выйти из игры
    MapWindow       *mapwindow;                         //  1 уровень (игровая карта)

    int             level;                              //  номер уровня

    void            desktop_size();                     //  присваивает значение переменным desktop_width и desktop_height


signals:
    void number_level(int);                             // Сигнал передает номер уровня

public slots:
    void exit_to_game();                                // выход из игры
    void go_to_mapwindow();                             // переход на окно карты игры
    void return_mainwindow(int);                        // возврат на главное окно
};
#endif // MAINWINDOW_H
