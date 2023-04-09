#include "maxtarlibrary.h"

MaxTarLibrary::MaxTarLibrary()
{

}

//------------------- Ширина экрана ------------------------------

int MaxTarLibrary::Screen_Width()
{
    QDesktopWidget *deskt_size = QApplication::desktop();
    int a = deskt_size->width();
    delete deskt_size;
    return(a);
}


//------------------- Высота экрана ------------------------------

int MaxTarLibrary::Screen_Height()
{
    QDesktopWidget *deskt_size = QApplication::desktop();
    int a = deskt_size->height();
    delete deskt_size;
    return(a);
}

//___________________ СЛУЧАЙНЫЕ ЧИСЛА ________________________________

int MaxTarLibrary::rnd(int a, int b)
{
    srand(time(NULL));
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}
