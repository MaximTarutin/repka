#include "lev_5_window.h"
#include "global.h"

Lev_5_Window::Lev_5_Window(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));

    viktory_timer     = new QTimer;
    timer_help        = new QTimer;

    level = 5;

    Background  = new QLabel(this);
    this->setCentralWidget(Background);
    Background->setStyleSheet("border-image: url(:/res5/dvor.jpeg);");
    Background->showFullScreen();

    Hand   = new Static_Object(":/res/ruka.png", 100, 100, this);

    Button_Return   = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);
    Button_Return->raise();

    Dog             = new Static_Object(":/res5/zuchka.png", 500, 500, this);
    Dog->move(desktop_width-550, desktop_height-550);
    Dog->show();

    Area_Puzzle     = new Static_Object(":/res5/cyan.png", 600, 600, this);
    Area_Puzzle->move(50, 250);
    Area_Puzzle->show();

    Mysl    = new Static_Object(":/res2/mysl.png", 570, 570, this);
    Mysl->move(Dog->x()+50, Dog->y()-Dog->height());
    Mysl->show();

    Mysl_1  = new Static_Object(":/res5/dog.jpg", 200, 200, Mysl);
    Mysl_1->move(190,140);

    Pazl    = new Static_Object[10];
    Pazl[0].pic_obj(":/res5/kadr-1.png");
    Pazl[1].pic_obj(":/res5/kadr-1.png");
    Pazl[2].pic_obj(":/res5/kadr-2.png");
    Pazl[3].pic_obj(":/res5/kadr-3.png");
    Pazl[4].pic_obj(":/res5/kadr-4.png");
    Pazl[5].pic_obj(":/res5/kadr-5.png");
    Pazl[6].pic_obj(":/res5/kadr-6.png");
    Pazl[7].pic_obj(":/res5/kadr-7.png");
    Pazl[8].pic_obj(":/res5/kadr-8.png");
    Pazl[9].pic_obj(":/res5/kadr-9.png");

    for(int i=0; i<10; ++i)
    {
        Pazl[i].setParent(this);
        Pazl[i].resize_obj(200, 200);
        FLAG_PAZZLE[i] = true;
    }

    movie   = new QMovie(":/res5/viktory.gif");                                           // анимация
    Smile   = new QLabel(this);
    Smile->setMovie(movie);
    Smile->resize(250,250);
    Smile->move(desktop_width/4, 10);

    yes = new QMediaPlayer;
    yes->setMedia(QUrl("qrc:/res1/yes.mp3"));
    yes->setVolume(0);
    yes->play();

    lay = new QMediaPlayer;
    lay->setMedia(QUrl("qrc:/res1/lay.mp3"));
    lay->setVolume(0);
    lay->play();

    number_pazzle = 0;
    init();

    Hand->show();
    Hand->raise();
    Hand->move(Pazl[1].x()+100+Hand->width(), Pazl[1].y()+100);
    timer_help->start(4);

    connect(Button_Return,      &QPushButton::clicked,      this,   &Lev_5_Window::return_to_mainwindow);       // нажимаем кнопку назад
    connect(viktory_timer,      &QTimer::timeout,           this,   &Lev_5_Window::viktory);                    // победа
    connect(timer_help,         &QTimer::timeout,           this,   &Lev_5_Window::help_game);
}

Lev_5_Window::~Lev_5_Window()
{
    delete Background;
    delete [] Pazl;
    delete Mysl;
    delete Mysl_1;
    delete Area_Puzzle;
    delete Dog;
    delete Button_Return;
    delete yes;
    delete Hand;
    delete timer_help;
    delete viktory_timer;
    delete lay;
    delete movie;
    delete Smile;
}

//-------------------------------------- возвращение на главный экран -----------------------------------------

void Lev_5_Window::return_to_mainwindow()
{
    emit number_level(level);                               // передаем сигнал с номером уровня
    this->hide();
}

//------------------------------- генератор случайных чисел в диапазоне от a до b ------------------------------

int Lev_5_Window::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k = rand()%b+a;
    return k;
}

// ----------------------------------------- инициализация --------------------------------------------------

void Lev_5_Window::init()
{
    int x[9], y[9], arr[9];
    int i=1, k;

    while(i<10)                                          // пока не установлены координаты всех пазлов выполняем цикл
    {
        k = rnd(1,9);                                   // берем случайное число

        for(int j=i; j>=1; --j)                         // для j от i пока не станет равным 1
        {
            if(arr[j] == k) break;                      // если j-е число массива равно k, то прерываем цикл
            else if(j==1)                               // иначе, если совпадений нет, то
            {
                arr[i] = k;                             // присваиваем j-му числу массива значение k

                switch (k)                              // определяем координаты для случайного числа k
                {
                case 1: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50;
                        y[i] = 20; break;
                case 2: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50+Pazl[i].width()+50;
                        y[i] = 20; break;
                case 3: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50;
                        y[i] = 40+Pazl[i].height(); break;
                case 4: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50+Pazl[i].width()+50;
                        y[i] = 40+Pazl[i].height(); break;
                case 5: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50;
                        y[i] = 60+Pazl[i].height()*2; break;
                case 6: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50+Pazl[i].width()+50;
                        y[i] = 60+Pazl[i].height()*2; break;
                case 7: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50;
                        y[i] = 80+Pazl[i].height()*3; break;
                case 8: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50+Pazl[i].width()+50;
                        y[i] = 80+Pazl[i].height()*3; break;
                case 9: x[i] = Area_Puzzle->x()+Area_Puzzle->width()+50;
                        y[i] = 100+Pazl[i].height()*4; break;
                }
                    Pazl[0].hide();
                    Pazl[i].move(x[i], y[i]);       // размещаем объект со случайными координатами
                    Pazl[i].show();
                    ++i;
                }
            }
    }
    old_x1 = Pazl[1].x()+100+Hand->width(); old_y1 = Pazl[1].y()+100;
}

//-------------------------------------- События при нажатии кнопки мышки ------------------------------

void Lev_5_Window::mousePressEvent(QMouseEvent *pe)
{
    if((pe->x()>Pazl[1].x())&&(pe->x()<Pazl[1].x()+Pazl[1].width())&&
       (pe->y()>Pazl[1].y())&&(pe->y()<Pazl[1].y()+Pazl[1].height())&&
       (FLAG_PAZZLE[1])) number_pazzle = 1;
    if((pe->x()>Pazl[2].x())&&(pe->x()<Pazl[2].x()+Pazl[2].width())&&
       (pe->y()>Pazl[2].y())&&(pe->y()<Pazl[2].y()+Pazl[2].height())&&
       (FLAG_PAZZLE[2])) number_pazzle = 2;
    if((pe->x()>Pazl[3].x())&&(pe->x()<Pazl[3].x()+Pazl[3].width())&&
       (pe->y()>Pazl[3].y())&&(pe->y()<Pazl[3].y()+Pazl[3].height())&&
       (FLAG_PAZZLE[3])) number_pazzle = 3;
    if((pe->x()>Pazl[4].x())&&(pe->x()<Pazl[4].x()+Pazl[4].width())&&
       (pe->y()>Pazl[4].y())&&(pe->y()<Pazl[4].y()+Pazl[4].height())&&
       (FLAG_PAZZLE[4])) number_pazzle = 4;
    if((pe->x()>Pazl[5].x())&&(pe->x()<Pazl[5].x()+Pazl[5].width())&&
       (pe->y()>Pazl[5].y())&&(pe->y()<Pazl[5].y()+Pazl[5].height())&&
       (FLAG_PAZZLE[5])) number_pazzle = 5;
    if((pe->x()>Pazl[6].x())&&(pe->x()<Pazl[6].x()+Pazl[6].width())&&
       (pe->y()>Pazl[6].y())&&(pe->y()<Pazl[6].y()+Pazl[6].height())&&
       (FLAG_PAZZLE[6])) number_pazzle = 6;
    if((pe->x()>Pazl[7].x())&&(pe->x()<Pazl[7].x()+Pazl[7].width())&&
       (pe->y()>Pazl[7].y())&&(pe->y()<Pazl[7].y()+Pazl[7].height())&&
       (FLAG_PAZZLE[7])) number_pazzle = 7;
    if((pe->x()>Pazl[8].x())&&(pe->x()<Pazl[8].x()+Pazl[8].width())&&
       (pe->y()>Pazl[8].y())&&(pe->y()<Pazl[8].y()+Pazl[8].height())&&
       (FLAG_PAZZLE[8])) number_pazzle = 8;
    if((pe->x()>Pazl[9].x())&&(pe->x()<Pazl[9].x()+Pazl[9].width())&&
       (pe->y()>Pazl[9].y())&&(pe->y()<Pazl[9].y()+Pazl[9].height())&&
       (FLAG_PAZZLE[9])) number_pazzle = 9;

    timer_help->stop();
    Hand->hide();
}

//--------------------------------------- События при отпускании кнопки мышки --------------------------

void Lev_5_Window::mouseReleaseEvent(QMouseEvent *pe)
{
    if((number_pazzle == 1)&&(pe->x()>Area_Puzzle->x())&&(pe->x()<Area_Puzzle->x()+200)&&
       (pe->y()>Area_Puzzle->y())&&(pe->y()<Area_Puzzle->y()+200))
    {
        Pazl[1].move(Area_Puzzle->x(), Area_Puzzle->y());
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[1] = false;
    }
    if((number_pazzle == 2)&&(pe->x()>Area_Puzzle->x()+200)&&(pe->x()<Area_Puzzle->x()+400)&&
       (pe->y()>Area_Puzzle->y())&&(pe->y()<Area_Puzzle->y()+200))
    {
        Pazl[2].move(Area_Puzzle->x()+200, Area_Puzzle->y());
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[2] = false;
    }
    if((number_pazzle == 3)&&(pe->x()>Area_Puzzle->x()+400)&&(pe->x()<Area_Puzzle->x()+600)&&
       (pe->y()>Area_Puzzle->y())&&(pe->y()<Area_Puzzle->y()+200))
    {
        Pazl[3].move(Area_Puzzle->x()+400, Area_Puzzle->y());
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[3] = false;
    }
    if((number_pazzle == 4)&&(pe->x()>Area_Puzzle->x())&&(pe->x()<Area_Puzzle->x()+200)&&
       (pe->y()>Area_Puzzle->y()+200)&&(pe->y()<Area_Puzzle->y()+400))
    {
        Pazl[4].move(Area_Puzzle->x(), Area_Puzzle->y()+200);
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[4] = false;
    }
    if((number_pazzle == 5)&&(pe->x()>Area_Puzzle->x()+200)&&(pe->x()<Area_Puzzle->x()+400)&&
       (pe->y()>Area_Puzzle->y()+200)&&(pe->y()<Area_Puzzle->y()+400))
    {
        Pazl[5].move(Area_Puzzle->x()+200, Area_Puzzle->y()+200);
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[5] = false;
    }
    if((number_pazzle == 6)&&(pe->x()>Area_Puzzle->x()+400)&&(pe->x()<Area_Puzzle->x()+600)&&
       (pe->y()>Area_Puzzle->y()+200)&&(pe->y()<Area_Puzzle->y()+400))
    {
        Pazl[6].move(Area_Puzzle->x()+400, Area_Puzzle->y()+200);
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[6] = false;
    }
    if((number_pazzle == 7)&&(pe->x()>Area_Puzzle->x())&&(pe->x()<Area_Puzzle->x()+200)&&
       (pe->y()>Area_Puzzle->y()+400)&&(pe->y()<Area_Puzzle->y()+600))
    {
        Pazl[7].move(Area_Puzzle->x(), Area_Puzzle->y()+400);
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[7] = false;
    }
    if((number_pazzle == 8)&&(pe->x()>Area_Puzzle->x()+200)&&(pe->x()<Area_Puzzle->x()+400)&&
       (pe->y()>Area_Puzzle->y()+400)&&(pe->y()<Area_Puzzle->y()+600))
    {
        Pazl[8].move(Area_Puzzle->x()+200, Area_Puzzle->y()+400);
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[8] = false;
    }
    if((number_pazzle == 9)&&(pe->x()>Area_Puzzle->x()+400)&&(pe->x()<Area_Puzzle->x()+600)&&
       (pe->y()>Area_Puzzle->y()+400)&&(pe->y()<Area_Puzzle->y()+600))
    {
        Pazl[9].move(Area_Puzzle->x()+400, Area_Puzzle->y()+400);
        yes->setVolume(100);
        yes->play();
        FLAG_PAZZLE[9] = false;
    }

    if(!FLAG_PAZZLE[1]&&!FLAG_PAZZLE[2]&&!FLAG_PAZZLE[3]&&!FLAG_PAZZLE[4]&&!FLAG_PAZZLE[5]&&
       !FLAG_PAZZLE[6]&&!FLAG_PAZZLE[7]&&!FLAG_PAZZLE[8]&&!FLAG_PAZZLE[9])
    {
        Smile->raise();
        movie->start();
        viktory_timer->start(1);
        lay->setVolume(100);
        lay->play();
    }

    number_pazzle = 0;
}

//--------------------------------------- События при движении мышки ----------------------------------

void Lev_5_Window::mouseMoveEvent(QMouseEvent *pe)
{
    if(FLAG_PAZZLE[number_pazzle])
    {
        Pazl[number_pazzle].move(pe->x()-100, pe->y()-100);
        Pazl[number_pazzle].raise();
    }
}

//---------------------------------------- Победа -----------------------------------------------------

void Lev_5_Window::viktory()
{
    static int x, k;
    x++;
    Smile->move(desktop_width-x, desktop_height-250);
    if(x>desktop_width+250)
    {
        x=0;
        k++;
        lay->play();
    }
    if(k>2)
    {
        viktory_timer->stop();
        lay->stop();
        level++;

        delete [] Pazl;
        delete Mysl_1;
        delete Mysl;
        delete Area_Puzzle;
        delete Dog;
        delete Button_Return;
        delete yes;
        delete Hand;
        delete timer_help;
        delete viktory_timer;
        //delete lay;
        delete Smile;
        delete movie;
        delete Background;
        return_to_mainwindow();
    }
    if((x==0)&&(k<1)) lay->play(); else lay->stop();
}

//------------------------------------ Подсказка ----------------------------------------

void Lev_5_Window::help_game()
{
    static int hand_x1, hand_y1;            // счетчики
    int x, x1, y, y1;                       // начальные и конечные координаты руки

    x = Pazl[1].x()-Hand->width()/4+hand_x1;
    y = Pazl[1].y()+Pazl[1].height()/2+hand_y1;
    x1 = Area_Puzzle->x()+100;
    y1 = Area_Puzzle->y()+100;
    if(x==x1)
    {
        x=x1;
    } else
    {
        --hand_x1;
    }
    if(y==y1)
    {
        y=y1;
    } else
    {
        if(y>y1) --hand_y1; else ++hand_y1;
    }
    if((x==x1)&&(y==y1))
    {
        x=old_x1;
        y=old_y1;
        hand_x1=0;
        hand_y1=0;
    }

    Hand->move(x, y);

}
