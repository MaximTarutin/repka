#ifndef MAXTARLIBRARY_H
#define MAXTARLIBRARY_H

#include <QObject>
#include <QApplication>
#include <QDesktopWidget>

class MaxTarLibrary: public QObject
{
    Q_OBJECT
public:
    MaxTarLibrary();

    int Screen_Width();
    int Screen_Height();
    int rnd(int a, int b);
};

#endif // MAXTARLIBRARY_H
