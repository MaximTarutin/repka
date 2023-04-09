#include "lev_6_window.h"

Lev_6_Window::Lev_6_Window(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));

    level = 6;
    num_open_plitka = 0;
    victory_plitka = 0;
    FLAG_PAUSE = true;

    Background  = new QLabel(this);
    this->setCentralWidget(Background);
    Background->setStyleSheet("border-image: url(:/res6/fon.jpg);");
    Background->showFullScreen();

    pause_timer     = new QTimer;
    pause1_timer    = new QTimer;
    pobeda          = new QTimer;
    help_timer      = new QTimer;

    Button_Return   = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);
    Button_Return->raise();

    Cat     = new Static_Object(":/res6/cat.png", 500, 500, this);
    Cat->move(desktop_width-Cat->width(), desktop_height-Cat->height());

    Plitka_fon  = new Static_Object[16];
    Plitka      = new Static_Object[16];

    for(int i=0; i<16; ++i)
    {
        Plitka_fon[i].setParent(this);
        Plitka_fon[i].resize_obj(200,200);
        Plitka_fon[i].pic_obj(":/res6/plitka.jpg");
        Plitka_fon[i].raise();
        Plitka_fon[i].show();
        Plitka[i].setParent(this);
        Plitka[i].resize_obj(200,200);
        Plitka[i].hide();
        FLAG_PLITKA[i]=false;
    }

    Plitka[0].pic_obj(":/res6/dedka.png");
    Plitka[1].pic_obj(":/res6/dedka.png");
    Plitka[2].pic_obj(":/res6/babka.png");
    Plitka[3].pic_obj(":/res6/babka.png");
    Plitka[4].pic_obj(":/res6/vnuchka.png");
    Plitka[5].pic_obj(":/res6/vnuchka.png");
    Plitka[6].pic_obj(":/res6/zuchka.png");
    Plitka[7].pic_obj(":/res6/zuchka.png");
    Plitka[8].pic_obj(":/res6/koshka.png");
    Plitka[9].pic_obj(":/res6/koshka.png");
    Plitka[10].pic_obj(":/res6/myshka.png");
    Plitka[11].pic_obj(":/res6/myshka.png");
    Plitka[12].pic_obj(":/res6/repka.png");
    Plitka[13].pic_obj(":/res6/repka.png");
    Plitka[14].pic_obj(":/res6/tomat.png");
    Plitka[15].pic_obj(":/res6/tomat.png");

    yes = new QMediaPlayer;
    yes->setMedia(QUrl("qrc:/res1/yes.mp3"));
    yes->setVolume(0);
    yes->play();

    bah = new QMediaPlayer;
    bah->setMedia(QUrl("qrc:/res1/bah.mp3"));
    bah->setVolume(0);
    bah->play();

    init();

    help_timer->start(10);

    movie   = new QMovie(":/res6/giphy.gif");                                           // анимация взрыва
    Bah     = new QLabel(this);
    Bah->setMovie(movie);
    Bah->resize(1000, 1000);
    Bah->move(Cat->x()-Cat->width()/4, Cat->y()-Cat->height()/2);

    Hand    = new Static_Object(":/res/ruka.png", 100, 100, this);
    Hand_1  = new Static_Object(":/res/ruka.png", 100, 100, this);

    connect(Button_Return,      &QPushButton::clicked,      this,       &Lev_6_Window::return_to_mainwindow);
    connect(pause_timer,        &QTimer::timeout,           this,       &Lev_6_Window::pause);
    connect(pause1_timer,       &QTimer::timeout,           this,       &Lev_6_Window::pause_1);
    connect(pobeda      ,       &QTimer::timeout,           this,       &Lev_6_Window::victory);
    connect(help_timer,         &QTimer::timeout,           this,       &Lev_6_Window::hand_move);
}

Lev_6_Window::~Lev_6_Window()
{
    delete Cat;
    delete Button_Return;
    delete Background;
    delete[] Plitka_fon;
    delete[] Plitka;
    delete pause1_timer;
    delete pause_timer;
    delete pobeda;
    delete yes;
    delete bah;
    delete Bah;
    delete movie;
    delete help_timer;
}

//------------------------------- генератор случайных чисел в диапазоне от a до b ------------------------------

int Lev_6_Window::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k = rand()%b+a;
    return k;
}

//------------------------------------- Возвращаемся на карту -----------------------------------

void Lev_6_Window::return_to_mainwindow()
{
    emit number_level(level);                               // передаем сигнал с номером уровня
    this->hide();
}

//------------------------------------ Расстановка плиток -------------------------------------

void Lev_6_Window::init()
{
    int x[15], y[15], arr[15];
    int i=0, k;

    while(i<16)                                          // пока не установлены координаты всех пазлов выполняем цикл
    {
        k = rnd(0,15);                                   // берем случайное число

        for(int j=i; j>=0; --j)                         // для j от i пока не станет равным 1
        {
            if(arr[j] == k) break;                      // если j-е число массива равно k, то прерываем цикл
            else if(j==0)                               // иначе, если совпадений нет, то
            {
                arr[i] = k;                             // присваиваем j-му числу массива значение k

                switch (k)                              // определяем координаты для случайного числа k
                {
                case 0:     x[i] = desktop_width/6;     y[i] = desktop_height/8;        break;
                case 1:     x[i] = desktop_width/6+210; y[i] = desktop_height/8;        break;
                case 2:     x[i] = desktop_width/6+420; y[i] = desktop_height/8;        break;
                case 3:     x[i] = desktop_width/6+630; y[i] = desktop_height/8;        break;
                case 4:     x[i] = desktop_width/6;     y[i] = desktop_height/8+210;    break;
                case 5:     x[i] = desktop_width/6+210; y[i] = desktop_height/8+210;    break;
                case 6:     x[i] = desktop_width/6+420; y[i] = desktop_height/8+210;    break;
                case 7:     x[i] = desktop_width/6+630; y[i] = desktop_height/8+210;    break;
                case 8:     x[i] = desktop_width/6;     y[i] = desktop_height/8+420;    break;
                case 9:     x[i] = desktop_width/6+210; y[i] = desktop_height/8+420;    break;
                case 10:    x[i] = desktop_width/6+420; y[i] = desktop_height/8+420;    break;
                case 11:    x[i] = desktop_width/6+630; y[i] = desktop_height/8+420;    break;
                case 12:    x[i] = desktop_width/6;     y[i] = desktop_height/8+630;    break;
                case 13:    x[i] = desktop_width/6+210; y[i] = desktop_height/8+630;    break;
                case 14:    x[i] = desktop_width/6+420; y[i] = desktop_height/8+630;    break;
                case 15:    x[i] = desktop_width/6+630; y[i] = desktop_height/8+630;    break;
                }
                    Plitka[i].raise();
                    Plitka[i].move(x[i], y[i]);       // размещаем объект со случайными координатами
                    Plitka_fon[i].move(x[i], y[i]);
                    ++i;
                }
            }
    }
}

//------------------------------- события при нажатии кнопки мышки ----------------------------------

void Lev_6_Window::mousePressEvent(QMouseEvent *pe)
{
 if(FLAG_PAUSE)                                                                 // если разрешено открывать плитки
 {
    help_timer->stop();                                                         // скрываем подсказку
    Hand->hide();
    Hand_1->hide();

    if((pe->x()>Plitka[0].x())&&(pe->x()<Plitka[0].x()+Plitka[0].width())&&     // проверяем по какой плитке кликнули
       (pe->y()>Plitka[0].y())&&(pe->y()<Plitka[0].y()+Plitka[0].height())&&
       (!FLAG_PLITKA[0]))
    {
        num_open_plitka++;
        current_plitka = 0;
    }
    if((pe->x()>Plitka[1].x())&&(pe->x()<Plitka[1].x()+Plitka[1].width())&&
       (pe->y()>Plitka[1].y())&&(pe->y()<Plitka[1].y()+Plitka[1].height())&&
            (!FLAG_PLITKA[1]))
    {
        num_open_plitka++;
        current_plitka = 1;
    }
    if((pe->x()>Plitka[2].x())&&(pe->x()<Plitka[2].x()+Plitka[2].width())&&
       (pe->y()>Plitka[2].y())&&(pe->y()<Plitka[2].y()+Plitka[2].height())&&
            (!FLAG_PLITKA[2]))
    {
        num_open_plitka++;
        current_plitka = 2;
    }
    if((pe->x()>Plitka[3].x())&&(pe->x()<Plitka[3].x()+Plitka[3].width())&&
       (pe->y()>Plitka[3].y())&&(pe->y()<Plitka[3].y()+Plitka[3].height())&&
            (!FLAG_PLITKA[3]))
    {
        num_open_plitka++;
        current_plitka = 3;
    }
    if((pe->x()>Plitka[4].x())&&(pe->x()<Plitka[4].x()+Plitka[4].width())&&
       (pe->y()>Plitka[4].y())&&(pe->y()<Plitka[4].y()+Plitka[4].height())&&
            (!FLAG_PLITKA[4]))
    {
        num_open_plitka++;
        current_plitka = 4;
    }
    if((pe->x()>Plitka[5].x())&&(pe->x()<Plitka[5].x()+Plitka[5].width())&&
       (pe->y()>Plitka[5].y())&&(pe->y()<Plitka[5].y()+Plitka[5].height())&&
            (!FLAG_PLITKA[5]))
    {
        num_open_plitka++;
        current_plitka = 5;
    }
    if((pe->x()>Plitka[6].x())&&(pe->x()<Plitka[6].x()+Plitka[6].width())&&
       (pe->y()>Plitka[6].y())&&(pe->y()<Plitka[6].y()+Plitka[6].height())&&
            (!FLAG_PLITKA[6]))
    {
        num_open_plitka++;
        current_plitka = 6;
    }
    if((pe->x()>Plitka[7].x())&&(pe->x()<Plitka[7].x()+Plitka[7].width())&&
       (pe->y()>Plitka[7].y())&&(pe->y()<Plitka[7].y()+Plitka[7].height())&&
            (!FLAG_PLITKA[7]))
    {
        num_open_plitka++;
        current_plitka = 7;
    }
    if((pe->x()>Plitka[8].x())&&(pe->x()<Plitka[8].x()+Plitka[8].width())&&
       (pe->y()>Plitka[8].y())&&(pe->y()<Plitka[8].y()+Plitka[8].height())&&
            (!FLAG_PLITKA[8]))
    {
        num_open_plitka++;
        current_plitka = 8;
    }
    if((pe->x()>Plitka[9].x())&&(pe->x()<Plitka[9].x()+Plitka[9].width())&&
       (pe->y()>Plitka[9].y())&&(pe->y()<Plitka[9].y()+Plitka[9].height())&&
            (!FLAG_PLITKA[9]))
    {
        num_open_plitka++;
        current_plitka = 9;
    }
    if((pe->x()>Plitka[10].x())&&(pe->x()<Plitka[10].x()+Plitka[10].width())&&
       (pe->y()>Plitka[10].y())&&(pe->y()<Plitka[10].y()+Plitka[10].height())&&
            (!FLAG_PLITKA[10]))
    {
        num_open_plitka++;
        current_plitka = 10;
    }
    if((pe->x()>Plitka[11].x())&&(pe->x()<Plitka[11].x()+Plitka[11].width())&&
       (pe->y()>Plitka[11].y())&&(pe->y()<Plitka[11].y()+Plitka[11].height())&&
            (!FLAG_PLITKA[11]))
    {
        num_open_plitka++;
        current_plitka = 11;
    }
    if((pe->x()>Plitka[12].x())&&(pe->x()<Plitka[12].x()+Plitka[12].width())&&
       (pe->y()>Plitka[12].y())&&(pe->y()<Plitka[12].y()+Plitka[12].height())&&
            (!FLAG_PLITKA[12]))
    {
        num_open_plitka++;
        current_plitka = 12;
    }
    if((pe->x()>Plitka[13].x())&&(pe->x()<Plitka[13].x()+Plitka[13].width())&&
       (pe->y()>Plitka[13].y())&&(pe->y()<Plitka[13].y()+Plitka[13].height())&&
            (!FLAG_PLITKA[13]))
    {
        num_open_plitka++;
        current_plitka = 13;
    }
    if((pe->x()>Plitka[14].x())&&(pe->x()<Plitka[14].x()+Plitka[14].width())&&
       (pe->y()>Plitka[14].y())&&(pe->y()<Plitka[14].y()+Plitka[14].height())&&
            (!FLAG_PLITKA[14]))
    {
        num_open_plitka++;
        current_plitka = 14;
    }
    if((pe->x()>Plitka[15].x())&&(pe->x()<Plitka[15].x()+Plitka[15].width())&&
       (pe->y()>Plitka[15].y())&&(pe->y()<Plitka[15].y()+Plitka[15].height())&&
            (!FLAG_PLITKA[15]))
    {
        num_open_plitka++;
        current_plitka = 15;
    }

    if((num_open_plitka==1)||(num_open_plitka==2))                  // открываем плитку
    {
        Plitka[current_plitka].show();
        if(num_open_plitka==1) num_1=current_plitka;                // запоминаем номера открытых плиток
        if(num_open_plitka==2) num_2=current_plitka;
    }
    if(num_open_plitka==2)                                          // если открыто две плитки, делаем паузу и проверяем на победу
    {
        pause_timer->start(100);
        num_open_plitka=0;
        check_victory();
    }
 }
}

//------------------------------------- Пауза при показе плиток ------------------------------------

void Lev_6_Window::pause()
{
    static int f;

    if(f>10)
    {
        f=0;
        pause_timer->stop();
        FLAG_PAUSE=true;
        Plitka[num_1].hide();
        Plitka[num_2].hide();
        if(!FLAG_PLITKA[num_1]&&!FLAG_PLITKA[num_2])        // если плитки не совпали, то показываем тыльную сторону плитки
        {
            Plitka_fon[num_1].show();
            Plitka_fon[num_2].show();
        }

    } else
    {
        f++;
        FLAG_PAUSE=false;
    }
}

//------------------------------------- Проверка на победу ---------------------------------------------

void Lev_6_Window::check_victory()
{
    if((num_1==0&&num_2==1)||(num_1==1&&num_2==0))
    {
        Plitka_fon[0].hide();
        Plitka_fon[1].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==2&&num_2==3)||(num_1==3&&num_2==2))
    {
        Plitka_fon[2].hide();
        Plitka_fon[3].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==4&&num_2==5)||(num_1==5&&num_2==4))
    {
        Plitka_fon[4].hide();
        Plitka_fon[5].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==6&&num_2==7)||(num_1==7&&num_2==6))
    {
        Plitka_fon[6].hide();
        Plitka_fon[7].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==8&&num_2==9)||(num_1==9&&num_2==8))
    {
        Plitka_fon[8].hide();
        Plitka_fon[9].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==10&&num_2==11)||(num_1==11&&num_2==10))
    {
        Plitka_fon[10].hide();
        Plitka_fon[11].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==12&&num_2==13)||(num_1==13&&num_2==12))
    {
        Plitka_fon[12].hide();
        Plitka_fon[13].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }
    if((num_1==14&&num_2==15)||(num_1==15&&num_2==14))
    {
        Plitka_fon[14].hide();
        Plitka_fon[15].hide();
        victory_plitka++;
        FLAG_PLITKA[num_1]=true;
        FLAG_PLITKA[num_2]=true;
        pause1_timer->start(100);
        yes->setVolume(100);
        yes->play();
    }

    if(victory_plitka==8) pobeda->start(100);
}

//------------------------------- Пауза при показе совпадающих плиток -------------------------------

void Lev_6_Window::pause_1()
{
    static int n;
    if(n<10)
    {
        Plitka[num_1].show();
        Plitka[num_2].show();
        n++;
    } else
    {
        n=0;
        pause1_timer->stop();
    }
}

//----------------------------------------- Победа ------------------------------------------------

void Lev_6_Window::victory()
{
    static int l;

    if(l<40)
    {
        movie->start();
        bah->setVolume(100);
        bah->play();
        Cat->hide();
        l++;
    } else
    {
        bah->stop();
        pobeda->stop();
        level++;
        delete Cat;
        delete Button_Return;
        delete[] Plitka_fon;
        delete[] Plitka;
        delete pause1_timer;
        delete pause_timer;
        delete pobeda;
        delete yes;
        delete bah;
        delete Bah;
        delete movie;
        delete help_timer;
        return_to_mainwindow();
    }

}

//---------------------------------------------- Подсказка ----------------------------------------------------------

void Lev_6_Window::hand_move()
{
    static int step_y;
    static int flag;

    if(flag!=1)
    {
            step_y++;
            Hand->move(Plitka[0].x()+Plitka[0].width()/2, Plitka[0].y()+Plitka[0].height()/2+step_y);
            Hand_1->move(Plitka[1].x()+Plitka[1].width()/2, Plitka[1].y()+Plitka[1].height()/2+step_y);
            if(step_y == 35) flag = 1;
    } else
    {
        step_y--;
        Hand->move(Plitka[0].x()+Plitka[0].width()/2, Plitka[0].y()+Plitka[0].height()/2+step_y);
        Hand_1->move(Plitka[1].x()+Plitka[1].width()/2, Plitka[1].y()+Plitka[1].height()/2+step_y);
        if(step_y == 0) flag = 0;
    }

}
