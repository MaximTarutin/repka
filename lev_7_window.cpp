#include "lev_7_window.h"

Lev_7_Window::Lev_7_Window(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));
    level = 7;

    pobeda_timer = new QTimer;

    Background  = new QLabel(this);
    Background->setStyleSheet("border-image: url(:/res7/dvor.jpg);");
    this->setCentralWidget(Background);
    Background->showFullScreen();

    Button_Return   = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);
    Button_Return->raise();

    Myschka         = new Static_Object(":/res7/myshka.png", 400, 400, this);
    Myschka->move(desktop_width-Myschka->width()*1.5, desktop_height-Myschka->height());
    Myschka->show();

    Mysl    = new Static_Object(":/res2/mysl.png", 500, 500, this);
    Mysl->move(Myschka->x()+50, Myschka->y()-Myschka->height());
    Mysl->show();

    Mysl_1  = new Static_Object(":/res7/put.png", 150, 150, Mysl);
    Mysl_1->move(190,140);

    Plitka      = new Static_Object[16];

    for(int i=0; i<16; ++i)
    {
        Plitka[i].setParent(this);
        Plitka[i].resize_obj(200,200);
    }

    Plitka[0].pic_obj(":/res7/01.png");
    Plitka[1].pic_obj(":/res7/02.png");
    Plitka[2].pic_obj(":/res7/03.png");
    Plitka[3].pic_obj(":/res7/04.png");
    Plitka[4].pic_obj(":/res7/05.png");
    Plitka[5].pic_obj(":/res7/06.png");
    Plitka[6].pic_obj(":/res7/07.png");
    Plitka[7].pic_obj(":/res7/08.png");
    Plitka[8].pic_obj(":/res7/09.png");
    Plitka[9].pic_obj(":/res7/10.png");
    Plitka[10].pic_obj(":/res7/11.png");
    Plitka[11].pic_obj(":/res7/12.png");
    Plitka[12].pic_obj(":/res7/13.png");
    Plitka[13].pic_obj(":/res7/14.png");
    Plitka[14].pic_obj(":/res7/15.png");
    Plitka[15].pic_obj(":/res7/16.png");

    Chees   = new Static_Object(":/res7/syr.png", 200, 200, this);
    Chees->move(desktop_width/6-150, desktop_height/8+100);
    Chees->show();

    init();

    movie   = new QMovie(":/res7/ura1.gif");                                           // анимация взрыва
    Mouse   = new QLabel(this);
    Mouse->setMovie(movie);
    Mouse->resize(1000, 1000);
    Mouse->move(desktop_width/2, desktop_height/4);

    connect(Button_Return,      &QPushButton::clicked,          this,       &Lev_7_Window::return_to_mainwindow);
    connect(pobeda_timer,       &QTimer::timeout,               this,       &Lev_7_Window::pobeda);
}

Lev_7_Window::~Lev_7_Window()
{
    delete Background;
    delete Button_Return;
    delete Myschka;
    delete Chees;
    delete [] Plitka;
    delete Mysl;
    delete Mysl_1;
    delete pobeda_timer;
    delete Mouse;
    delete movie;
}

//------------------------------------- Возвращаемся на карту -----------------------------------

void Lev_7_Window::return_to_mainwindow()
{
    emit number_level(level);        // передаем сигнал с номером уровня
    this->hide();
}

//------------------------------- генератор случайных чисел в диапазоне от a до b ------------------------------

int Lev_7_Window::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k = rand()%b+a;
    return k;
}

//------------------------------------ расстановка плиток ------------------------------------------

void Lev_7_Window::init()
{
    int i;

    Plitka[0].move(desktop_width/6+100,     desktop_height/8+100);
    Plitka[1].move(desktop_width/6+300, desktop_height/8+100);
    Plitka[2].move(desktop_width/6+500, desktop_height/8+100);
    Plitka[3].move(desktop_width/6+700, desktop_height/8+100);
    Plitka[4].move(desktop_width/6+100,     desktop_height/8+300);
    Plitka[5].move(desktop_width/6+300, desktop_height/8+300);
    Plitka[6].move(desktop_width/6+500, desktop_height/8+300);
    Plitka[7].move(desktop_width/6+700, desktop_height/8+300);
    Plitka[8].move(desktop_width/6+100,     desktop_height/8+500);
    Plitka[9].move(desktop_width/6+300, desktop_height/8+500);
    Plitka[10].move(desktop_width/6+500, desktop_height/8+500);
    Plitka[11].move(desktop_width/6+700, desktop_height/8+500);
    Plitka[12].move(desktop_width/6+100,     desktop_height/8+700);
    Plitka[13].move(desktop_width/6+300, desktop_height/8+700);
    Plitka[14].move(desktop_width/6+500, desktop_height/8+700);
    Plitka[15].move(desktop_width/6+700, desktop_height/8+700);

    for(i=0; i<16; ++i)
    {
        plitka_sost[i] = rnd(0,3);
        switch(plitka_sost[i])
        {
        case 0: radian[i] = 0;      break;
        case 1: radian[i] = 90;     break;
        case 2: radian[i] = 180;    break;
        case 3: radian[i] = 270;    break;
        }

        Plitka[i].pic_rotate(radian[i]);
    }
}

//---------------------------------- события при нажатии кнопки мышки по плитке -----------------------------

void Lev_7_Window::mousePressEvent(QMouseEvent *pe)
{
    if((pe->x()>Plitka[0].x())&&(pe->x()<Plitka[15].x()+Plitka[15].width())&&           // попадает ли курсор в область пазлов
        (pe->y()>Plitka[0].y())&&(pe->y()<Plitka[15].y()+Plitka[15].height()))
    {
        if((pe->x()>Plitka[0].x())&&(pe->x()<Plitka[0].x()+Plitka[0].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[0].y())&&(pe->y()<Plitka[0].y()+Plitka[0].height()))
        {
            index = 0;
        }
        if((pe->x()>Plitka[1].x())&&(pe->x()<Plitka[1].x()+Plitka[1].width())&&
           (pe->y()>Plitka[1].y())&&(pe->y()<Plitka[1].y()+Plitka[1].height()))
        {
            index = 1;
        }
        if((pe->x()>Plitka[2].x())&&(pe->x()<Plitka[2].x()+Plitka[2].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[2].y())&&(pe->y()<Plitka[2].y()+Plitka[2].height()))
        {
            index = 2;
        }
        if((pe->x()>Plitka[3].x())&&(pe->x()<Plitka[3].x()+Plitka[3].width())&&
           (pe->y()>Plitka[3].y())&&(pe->y()<Plitka[3].y()+Plitka[3].height()))
        {
            index = 3;
        }
        if((pe->x()>Plitka[4].x())&&(pe->x()<Plitka[4].x()+Plitka[4].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[4].y())&&(pe->y()<Plitka[4].y()+Plitka[4].height()))
        {
            index = 4;
        }
        if((pe->x()>Plitka[5].x())&&(pe->x()<Plitka[5].x()+Plitka[5].width())&&
           (pe->y()>Plitka[5].y())&&(pe->y()<Plitka[5].y()+Plitka[5].height()))
        {
            index = 5;
        }
        if((pe->x()>Plitka[6].x())&&(pe->x()<Plitka[6].x()+Plitka[6].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[6].y())&&(pe->y()<Plitka[6].y()+Plitka[6].height()))
        {
            index = 6;
        }
        if((pe->x()>Plitka[7].x())&&(pe->x()<Plitka[7].x()+Plitka[7].width())&&
           (pe->y()>Plitka[7].y())&&(pe->y()<Plitka[7].y()+Plitka[7].height()))
        {
            index = 7;
        }
        if((pe->x()>Plitka[8].x())&&(pe->x()<Plitka[8].x()+Plitka[8].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[8].y())&&(pe->y()<Plitka[8].y()+Plitka[8].height()))
        {
            index = 8;
        }
        if((pe->x()>Plitka[9].x())&&(pe->x()<Plitka[9].x()+Plitka[9].width())&&
           (pe->y()>Plitka[9].y())&&(pe->y()<Plitka[9].y()+Plitka[9].height()))
        {
            index = 9;
        }
        if((pe->x()>Plitka[10].x())&&(pe->x()<Plitka[10].x()+Plitka[10].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[10].y())&&(pe->y()<Plitka[10].y()+Plitka[10].height()))
        {
            index = 10;
        }
        if((pe->x()>Plitka[11].x())&&(pe->x()<Plitka[11].x()+Plitka[11].width())&&
           (pe->y()>Plitka[11].y())&&(pe->y()<Plitka[11].y()+Plitka[11].height()))
        {
            index = 11;
        }
        if((pe->x()>Plitka[12].x())&&(pe->x()<Plitka[12].x()+Plitka[12].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[12].y())&&(pe->y()<Plitka[12].y()+Plitka[12].height()))
        {
            index = 12;
        }
        if((pe->x()>Plitka[13].x())&&(pe->x()<Plitka[13].x()+Plitka[13].width())&&
           (pe->y()>Plitka[13].y())&&(pe->y()<Plitka[13].y()+Plitka[13].height()))
        {
            index = 13;
        }
        if((pe->x()>Plitka[14].x())&&(pe->x()<Plitka[14].x()+Plitka[14].width())&&         // на какую именно плитку кликнули
           (pe->y()>Plitka[14].y())&&(pe->y()<Plitka[14].y()+Plitka[14].height()))
        {
            index = 14;
        }
        if((pe->x()>Plitka[15].x())&&(pe->x()<Plitka[15].x()+Plitka[15].width())&&
           (pe->y()>Plitka[15].y())&&(pe->y()<Plitka[15].y()+Plitka[15].height()))
        {
            index = 15;
        }


        if(index>=0&&index<=15)                         // если индекс существут, то переварачиваем плитку на 90 градусов
        {
            int k=0;
            if(radian[index]==360) radian[index]=0;
            radian[index]+=90;
            Plitka[index].pic_rotate(radian[index]);
            plitka_sost[index]++;                       // проверяем в каком положении находится плитка
            if(plitka_sost[index]>3) plitka_sost[index]=0;

            for(int u=0; u<=15; u++)                    // проверка на выигрыш
            {
              if(plitka_sost[u]==0) k++;
              if(k==16) pobeda_timer->start(100);
            }
        }
        index = 17;                                     // создаем индекс несуществующей плитки
    }
}

//------------------------------ Победа -------------------------------------

void Lev_7_Window::pobeda()
{
    static int l;

    if(l<40)
    {
        Myschka->hide();
        Mysl->hide();
        Mysl_1->hide();
        Chees->move(Myschka->x(), Myschka->y());
        movie->start();
        l++;
    } else
    {
        movie->stop();
        level++;
        delete Background;
        delete Button_Return;
        delete Myschka;
        delete Chees;
        delete [] Plitka;
        delete Mysl_1;
        delete Mysl;
        delete pobeda_timer;
        delete Mouse;
        delete movie;
        return_to_mainwindow();
    }
}
