#include "lev_2_window.h"
#include <ctime>
#include "global.h"

Lev_2_Window::Lev_2_Window(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));
    level = 2;
    tool  = 0;

    timer_move  = new QTimer;                                                           // таймер перемещения предметов
    timer_salut = new QTimer;                                                           // таймер победы (салют)
    timer_hand  = new QTimer;                                                           // таймер подсказки

    Background  = new QLabel(this);
    setCentralWidget(Background);                                                       // QLabel назначаем центральным виджетом
    Background->setStyleSheet("border-image: url(:/res2/level_2.jpg);");                // ставим фон
    Background->showFullScreen();

    Subject_Area    = new QLabel(this);
    Subject_Area->setStyleSheet("border-image: url(:/res2/fon.png);");                  // Область собранных предметов
    Subject_Area->resize(desktop_width/2, desktop_height/10);
    Subject_Area->move(desktop_width/4,0);

    Button_Return   = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);
    Button_Return->raise();

    Dedka       = new Static_Object(":/res2/dedka.png", 400, 400, this);
    Dedka->move(0, desktop_height-Dedka->height());                                     // Дедка думает о предмете
    Mysl        = new Static_Object(":/res2/mysl.png", 300, 300, this);
    Mysl->move(Dedka->x()+Dedka->width()/2, Dedka->y()-Dedka->height()/2-50);

    Hand    = new Static_Object(":/res/ruka.png", 100, 100, this);

    yes = new QMediaPlayer;
    yes->setMedia(QUrl("qrc:/res1/yes.mp3"));
    yes->setVolume(0);
    yes->play();
    no  = new QMediaPlayer;
    no->setMedia(QUrl("qrc:/res1/nea.wav"));                                            // Звуки
    no->setVolume(0);
    no->play();
    victory = new QMediaPlayer;
    victory->setMedia(QUrl("qrc:/res1/viktory.wav"));
    victory->setVolume(0);
    victory->play();
    salut_wav   = new QMediaPlayer;
    salut_wav->setMedia(QUrl("qrc:/res1/salut.mp3"));
    salut_wav->setVolume(0);
    salut_wav->play();

    init();                                                                             // инициализация игрового уровня

    Tools_Ded[0]->move(Mysl->x()+Mysl->width()/3, Mysl->y()+Mysl->height()/4);          // Первый инструмент о котором думает дедка
    Tools_Ded[0]->raise();
    Tools_Ded[0]->show();

    movie   = new QMovie(":/res2/salut.gif");                                           // анимация салюта при выигрыше
    Salut   = new QLabel(this);
    Salut->setMovie(movie);
    Salut->resize(desktop_width/2, desktop_height/2);
    Salut->move(desktop_width/4, desktop_height/4);

    Hand->move(Tools[0]->x(), Tools[0]->y()+Tools[0]->height());                        // Начальная позиция подсказки

    timer_hand->start(10);                                                               // Запускаем подсказку

    connect(Button_Return,  &QPushButton::clicked,  this,   &Lev_2_Window::return_to_mainwindow);   // возврат на карту
    connect(timer_move,     &QTimer::timeout,       this,   &Lev_2_Window::move_tool);              // перемещение предметов
    connect(timer_salut,    &QTimer::timeout,       this,   &Lev_2_Window::salut_show);             // показываем салют
    connect(timer_hand,     &QTimer::timeout,       this,   &Lev_2_Window::move_hand);              // показываем подсказку
}


Lev_2_Window::~Lev_2_Window()
{
    delete Background;
    delete Subject_Area;
    delete Dedka;
    delete Mysl;
    delete Button_Return;                                   // освобождаем память
    delete yes;
    delete no;
    delete victory;
    delete salut_wav;
    delete timer_move;
    delete timer_salut;
    delete Salut;
    delete movie;
    for(int i=0; i<8; ++i) delete Tools[i];
    for(int i=0; i<8; ++i) delete Tools_Ded[i];
}

//-------------------------- возвращение на главный экран -----------------------------------

void Lev_2_Window::return_to_mainwindow()
{
    emit number_level(level);                               // передаем сигнал с номером уровня
    this->hide();
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Lev_2_Window::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

//---------------------- инициализация массива инструментов и их расстановка--------------------------------

void Lev_2_Window::init()
{
    int i=0, k=0, m=0;
    int arr[7];
    int arr1[7];
    int x = desktop_width;
    int y = desktop_height;


    while (i<8)                     // инструменты повторяться не должны
    {
        k = rnd(0,7);               // случайный инструмент
        m = rnd(0,7);               // случайное местоположение инструмента

        for(int j=i; j>=0; --j)
        {
            if((arr[j] == k)||(arr1[j] == m)) break;
            else if(j==0)
            {
                arr[i]  = k;
                arr1[i] = m;
                        switch (k)      // создаем массив инструментов
                        {
                        case 0: Tools[i]     = new Static_Object(":/res2/fomka.png",   100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/fomka.png",   100, 100, this);
                                tools_x[i] = x-150; tools_y[i] = y-300;
                                tools_x_end[i] = Subject_Area->x(); tools_y_end[i] = Subject_Area->y(); break;
                        case 1: Tools[i]     = new Static_Object(":/res2/leyka.png",   100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/leyka.png",   100, 100, this);
                                tools_x[i] = x/2; tools_y[i] = y/2-30;
                                tools_x_end[i] = Subject_Area->x()+120; tools_y_end[i] = Subject_Area->y(); break;
                        case 2: Tools[i]     = new Static_Object(":/res2/lopata.png",  100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/lopata.png",  100, 100, this);
                                tools_x[i] = x-450; tools_y[i] = y/2-30;
                                tools_x_end[i] = Subject_Area->x()+240; tools_y_end[i] = Subject_Area->y(); break;
                        case 3: Tools[i]     = new Static_Object(":/res2/molotok.png", 100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/molotok.png", 100, 100, this);
                                tools_x[i] = x/4; tools_y[i] = y-380;
                                tools_x_end[i] = Subject_Area->x()+360; tools_y_end[i] = Subject_Area->y(); break;
                        case 4: Tools[i]     = new Static_Object(":/res2/serp.png",    100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/serp.png",    100, 100, this);
                                tools_x[i] = x/2-450; tools_y[i] = y/2-180;
                                tools_x_end[i] = Subject_Area->x()+480; tools_y_end[i] = Subject_Area->y(); break;
                        case 5: Tools[i]     = new Static_Object(":/res2/topor.png",   100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/topor.png",   100, 100, this);
                                tools_x[i] = x/2+x/6; tools_y[i] = y/5+70;
                                tools_x_end[i] = Subject_Area->x()+600; tools_y_end[i] = Subject_Area->y(); break;
                        case 6: Tools[i]     = new Static_Object(":/res2/vedro.png",   100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/vedro.png",   100, 100, this);
                                tools_x[i] = 50; tools_y[i] = y/2-50;
                                tools_x_end[i] = Subject_Area->x()+720; tools_y_end[i] = Subject_Area->y(); break;
                        case 7: Tools[i]     = new Static_Object(":/res2/vily.png",    100, 100, this);
                                Tools_Ded[i] = new Static_Object(":/res2/vily.png",    100, 100, this);
                                tools_x[i] = x/8; tools_y[i] = y/8-80;
                                tools_x_end[i] = Subject_Area->x()+840; tools_y_end[i] = Subject_Area->y(); break;
                        }

                Tools[i]->move(tools_x[i], tools_y[i]);
                Tools[i]->resize(150,150);
                Tools_Ded[i]->hide();
                i++;
            }
        }
    }
}

//----------------------------------- Кликаем мышкой по предмету ---------------------------------------

void Lev_2_Window::mousePressEvent(QMouseEvent *pe)
{
    if((pe->x() >= Tools[tool]->x())&&(pe->x() <= Tools[tool]->x()+Tools[tool]->width())&&          // если курсор в области нужного
       (pe->y() >= Tools[tool]->y())&&(pe->y() <= Tools[tool]->y()+Tools[tool]->height()))          // инструмента
    {
        yes->setVolume(100);
        yes->play();
        Tools_Ded[tool]->hide();
        timer_move->start(5);
        timer_hand->stop();
        Hand->hide();
    } else
    {
        no->setVolume(100);
        no->play();
    }
}

//---------------------- перемещаем инструмент в область инструментов -----------------------------

void Lev_2_Window::move_tool()
{
    if(tools_x[tool] <  tools_x_end[tool])
    {
        tools_x[tool] = tools_x[tool]+10;
        if(tools_x[tool] >= tools_x_end[tool])
        {
            tools_x[tool] = tools_x_end[tool];
        }
    }
    if(tools_x[tool] >  tools_x_end[tool])
    {
        tools_x[tool] = tools_x[tool]-10;
        if(tools_x[tool] <= tools_x_end[tool])
        {
            tools_x[tool] = tools_x_end[tool];
        }
    }
    if(tools_y[tool] <  tools_y_end[tool])
    {
        tools_y[tool] = tools_y[tool]+10;
        if(tools_y[tool] >= tools_y_end[tool])
        {
            tools_y[tool] = tools_y_end[tool];
        }
    }
    if(tools_y[tool] >  tools_y_end[tool])
    {
        tools_y[tool] = tools_y[tool]-10;
        if(tools_y[tool] <= tools_y_end[tool])
        {
            tools_y[tool] = tools_y_end[tool];
        }
    }

    if((tools_x[tool] == tools_x_end[tool])&&(tools_y[tool] == tools_y_end[tool])&&(tool < 8))
    {
        Tools[tool]->resize_obj(100,100);
        tool++;
        if(tool > 7)
        {
            salut_wav->setVolume(100);
            salut_wav->play();
            movie->start();
            tool = 8;
            Tools_Ded[7]->hide();
            Mysl->hide();
            timer_salut->start(1000);
        } else
        {
            Tools_Ded[tool]->move(Mysl->x()+Mysl->width()/3, Mysl->y()+Mysl->height()/4);
            Tools_Ded[tool]->raise();
            Tools_Ded[tool]->show();                                                                // обновляем мысли дедки ;)
            timer_move->stop();
        }
    }


    Tools[tool]->move(tools_x[tool], tools_y[tool]);
}

//-------------------------------------------- Время показа салюта ----------------------------------------------------

void Lev_2_Window::salut_show()
{
    static int i;
    i++;
    if(i==10)
    {
        level++;
        delete Background;
        delete Subject_Area;
        delete Dedka;
        delete Mysl;
        delete Button_Return;                                   // освобождаем память
        delete yes;
        delete no;
        delete victory;
        delete salut_wav;
        delete timer_move;
        delete timer_salut;
        delete Salut;
        delete movie;
        for(int i=0; i<8; ++i) delete Tools[i];
        for(int i=0; i<8; ++i) delete Tools_Ded[i];
        return_to_mainwindow();
    }
}

//---------------------------------------------- Подсказка ----------------------------------------------------------

void Lev_2_Window::move_hand()
{
    static int step_y;
    static int flag;

    if(flag!=1)
    {
            step_y++;
            Hand->move(Tools[0]->x(), Tools[0]->y()+Tools[0]->height()+step_y);
            if(step_y == 35) flag = 1;
    } else
    {
        step_y--;
        Hand->move(Tools[0]->x(), Tools[0]->y()+Tools[0]->height()+step_y);
        if(step_y == 0) flag = 0;
    }

}
