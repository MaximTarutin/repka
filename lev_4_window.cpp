#include "lev_4_window.h"

Lev_4_Window::Lev_4_Window(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));

    index  = 0;
    number = 1;
    level  = 4;
    FLAG_START_GAME = false;

    viktory     = new QTimer;
    timer_help  = new QTimer;

    Background  = new QLabel(this);
    this->setCentralWidget(Background);
    Background->setStyleSheet("border-image: url(:/res4/fon.jpg);");
    Background->showFullScreen();

    Button_Return   = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);
    Button_Return->raise();

    Subject_Area    = new QLabel(this);
    Subject_Area->setStyleSheet("border-image: url(:/res2/fon.png);");                  // Область карандашей
    Subject_Area->resize(desktop_width/2-desktop_width/12, desktop_height/10);
    Subject_Area->move(desktop_width/4,20);

    Masha   = new Static_Object(":/res4/vnuchka-111.png", 450, 450, this);
    Masha->move(50, desktop_height-Masha->height());
    Masha->show();

    Mysl    = new Static_Object(":/res2/mysl.png", 350, 350, this);
    Mysl->move(Masha->x()+Masha->width()/2, Masha->y()-Masha->height()/2);
    Mysl->show();

    Pen     = new Static_Object[8];
    Pen[0].pic_obj(":res4/karandash.png"); Pen[0].hide();
    Pen[1].pic_obj(":/res4/karandash-1.png");
    Pen[2].pic_obj(":/res4/karandash-2.png");
    Pen[3].pic_obj(":/res4/karandash-3.png");
    Pen[4].pic_obj(":/res4/karandash-4.png");
    Pen[5].pic_obj(":/res4/karandash-5.png");
    Pen[6].pic_obj(":/res4/karandash-6.png");
    Pen[7].pic_obj(":/res4/karandash-7.png");

    Mysl_Object = new Static_Object[8];
    Mysl_Object[1].pic_obj(":/res4/lico.png");
    Mysl_Object[2].pic_obj(":/res4/platok.png");
    Mysl_Object[3].pic_obj(":/res4/volosy.png");
    Mysl_Object[4].pic_obj(":/res4/grib.png");
    Mysl_Object[5].pic_obj(":/res4/korzina.png");
    Mysl_Object[6].pic_obj(":/res4/platie.png");
    Mysl_Object[7].pic_obj(":/res4/sapogi.png");

    Vnuchka     = new Static_Object[8];
    Vnuchka[0].pic_obj(":/res4/vnuchka.png");
    Vnuchka[1].pic_obj(":/res4/vnuchka-1.png");
    Vnuchka[2].pic_obj(":/res4/vnuchka-2.png");
    Vnuchka[3].pic_obj(":/res4/vnuchka-3.png");
    Vnuchka[4].pic_obj(":/res4/vnuchka-4.png");
    Vnuchka[5].pic_obj(":/res4/vnuchka-5.png");
    Vnuchka[6].pic_obj(":/res4/vnuchka-6.png");
    Vnuchka[7].pic_obj(":/res4/vnuchka-7.png");

    Holst   = new Static_Object(":/res4/holst.png", 800,800, this);
    Holst->move(desktop_width-Holst->width(), desktop_height-Holst->height());
    Holst->show();

    for(int i=0; i<8; ++i)
    {
            Mysl_Object[i].setParent(Mysl);
            Mysl_Object[i].resize_obj(100,100);
            Mysl_Object[i].move(Mysl->width()/2-Mysl_Object[1].width()/2, Mysl->height()/2-Mysl_Object[1].height()/2-20);
            Mysl_Object[i].hide();
            Pen[i].resize_obj(100,100);
            Pen[i].setParent(this);
            Vnuchka[i].setParent(this);
            Vnuchka[i].resize_obj(350,350);
            Vnuchka[i].move(Holst->x()+Holst->width()/6, Holst->y()+Holst->height()/8);
            Vnuchka[i].hide();
    }

    Mysl_Object[number].show();
    Vnuchka[0].show();

    Hand1   = new Static_Object(":/res/ruka.png", 100, 100, this);

    yes = new QMediaPlayer;
    yes->setMedia(QUrl("qrc:/res1/yes.mp3"));
    yes->setVolume(0);
    yes->play();

    no = new QMediaPlayer;
    no->setMedia(QUrl("qrc:/res1/nea.wav"));
    no->setVolume(0);
    no->play();

    ura = new QMediaPlayer;
    ura->setMedia(QUrl("qrc:/res1/ura.mp3"));
    ura->setVolume(0);
    ura->play();

    movie   = new QMovie(":/res4/confetti-12.gif");                                           // анимация салюта при выигрыше
    Shariki = new QLabel(this);
    Shariki->setMovie(movie);
    Shariki->resize(desktop_width, desktop_height);
    Shariki->move(desktop_width/4, 10);

    init();

    connect(Button_Return,      &QPushButton::clicked,      this,   &Lev_4_Window::return_to_mainwindow);       // нажимаем кнопку назад
    connect(viktory,            &QTimer::timeout,           this,   &Lev_4_Window::pobeda);                     // таймер победы
    connect(timer_help,         &QTimer::timeout,           this,   &Lev_4_Window::help_game);                  // подсказка

    timer_help->start(3);
}

Lev_4_Window::~Lev_4_Window()
{
    delete[] Vnuchka;
    delete[] Mysl_Object;
    delete[] Pen;
    delete yes;
    delete no;
    delete ura;
    delete Background;
    delete viktory;
    delete Shariki;
    delete movie;
    delete Mysl;
    delete Holst;
    delete Masha;
    delete Subject_Area;
    delete Button_Return;
}

//-------------------------------------- возвращение на главный экран -----------------------------------------

void Lev_4_Window::return_to_mainwindow()
{
    emit number_level(level);                               // передаем сигнал с номером уровня
    this->hide();
}

//------------------------------- генератор случайных чисел в диапазоне от a до b ------------------------------

int Lev_4_Window::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k = rand()%b+a;
    return k;
}

//------------------------------- Инициализация, расставляем карандаши -----------------------------------------

void Lev_4_Window::init()
{
    int x[8], y[8], arr[8];
    int i=1, k;

    while(i<8)                                          // пока не установлены координаты всех продуктов выполняем цикл
    {
        k = rnd(1,7);                                   // берем случайное число

        for(int j=i; j>=1; --j)                         // для j от i пока не станет равным 1
        {
            if(arr[j] == k) break;                      // если j-е число массива равно k, то прерываем цикл
            else if(j==1)                               // иначе, если совпадений нет, то
            {
                arr[i] = k;                             // присваиваем j-му числу массива значение k

                switch (k)                              // определяем координаты для случайного числа k
                {
                case 1: x[i] = Subject_Area->x()+Pen[1].width()+20;  y[i]=Subject_Area->y(); break;
                case 2: x[i] = Subject_Area->x()+Pen[1].width()+120; y[i]=Subject_Area->y(); break;
                case 3: x[i] = Subject_Area->x()+Pen[1].width()+220; y[i]=Subject_Area->y(); break;
                case 4: x[i] = Subject_Area->x()+Pen[1].width()+320; y[i]=Subject_Area->y(); break;
                case 5: x[i] = Subject_Area->x()+Pen[1].width()+420; y[i]=Subject_Area->y(); break;
                case 6: x[i] = Subject_Area->x()+Pen[1].width()+520; y[i]=Subject_Area->y(); break;
                case 7: x[i] = Subject_Area->x()+Pen[1].width()+620; y[i]=Subject_Area->y(); break;
                }

                    Pen[i].move(x[i], y[i]);       // размещаем объект со случайными координатами
                    Pen[i].show();
                    ++i;
                }
            }
    }

    old_x1 = Pen[1].x();                        // Начальные координаты первого карандаша
    old_y1 = Pen[1].y();
}

//------------------------------------ События при нажатии на кнопку мыши --------------------------------

void Lev_4_Window::mousePressEvent(QMouseEvent *pe)
{
    if((pe->x()>=Pen[1].x())&&(pe->x()<=Pen[1].x()+Pen[1].width())&&
       (pe->y()>=Pen[1].y())&&(pe->y()<=Pen[1].y()+Pen[1].height()))
    {
        index=1;
        timer_help->stop();
        Hand1->hide();
    }
    if((pe->x()>=Pen[2].x())&&(pe->x()<=Pen[2].x()+Pen[2].width())&&
       (pe->y()>=Pen[2].y())&&(pe->y()<=Pen[2].y()+Pen[2].height())) index=2;
    if((pe->x()>=Pen[3].x())&&(pe->x()<=Pen[3].x()+Pen[3].width())&&
       (pe->y()>=Pen[3].y())&&(pe->y()<=Pen[3].y()+Pen[3].height())) index=3;    //  Проверяем по какому карандашу кликнули
    if((pe->x()>=Pen[4].x())&&(pe->x()<=Pen[4].x()+Pen[4].width())&&
       (pe->y()>=Pen[4].y())&&(pe->y()<=Pen[4].y()+Pen[4].height())) index=4;
    if((pe->x()>=Pen[5].x())&&(pe->x()<=Pen[5].x()+Pen[5].width())&&
       (pe->y()>=Pen[5].y())&&(pe->y()<=Pen[5].y()+Pen[5].height())) index=5;
    if((pe->x()>=Pen[6].x())&&(pe->x()<=Pen[6].x()+Pen[6].width())&&
       (pe->y()>=Pen[6].y())&&(pe->y()<=Pen[6].y()+Pen[6].height())) index=6;
    if((pe->x()>=Pen[7].x())&&(pe->x()<=Pen[7].x()+Pen[7].width())&&
       (pe->y()>=Pen[7].y())&&(pe->y()<=Pen[7].y()+Pen[7].height())) index=7;

    old_x = Pen[index].x();
    old_y = Pen[index].y();
}

//------------------------------------- События при движении мышки ---------------------------------------

void Lev_4_Window::mouseMoveEvent(QMouseEvent *pe)
{
    Pen[index].raise();
    Pen[index].move(pe->x(), pe->y()-Pen[index].height());
}

//-------------------------------------- События при отпускании кнопки мыши ------------------------------

void Lev_4_Window::mouseReleaseEvent(QMouseEvent *pe)
{
    yes->setVolume(100);
    no->setVolume(100);

    if(index!=number)                                       // если выбранный карандаш не совпал с цветом мысли
    {
        Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
        no->play();
    } else
    {
        switch (number)
        {
        case 1: if((pe->x()>=Vnuchka[0].x()+Vnuchka[0].width()/4)&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width()-Vnuchka[0].width()/2)&&
                   (pe->y()>=Vnuchka[0].y()+Vnuchka[0].height()/7)&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()/2-Vnuchka[0].height()/10))
                {
                    yes->play();
                    ++number;
                    Vnuchka[0].hide();
                    Vnuchka[1].show();
                    Mysl_Object[1].hide();
                    Mysl_Object[2].show();
                    Pen[index].hide();
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        case 2: if((pe->x()>=Vnuchka[0].x())&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width())&&
                   (pe->y()>=Vnuchka[0].y())&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()/2-Vnuchka[0].height()/10))
                {
                    yes->play();
                    ++number;
                    Vnuchka[1].hide();
                    Vnuchka[2].show();
                    Mysl_Object[2].hide();
                    Mysl_Object[3].show();
                    Pen[index].hide();
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        case 3: if((pe->x()>=Vnuchka[0].x()+Vnuchka[0].width()/6)&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width()-Vnuchka[0].width()/2)&&
                   (pe->y()>=Vnuchka[0].y()+Vnuchka[0].height()/10)&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()/2-Vnuchka[0].height()/4))
                {
                    yes->play();
                    ++number;
                    Vnuchka[2].hide();
                    Vnuchka[3].show();
                    Mysl_Object[3].hide();
                    Mysl_Object[4].show();
                    Pen[index].hide();
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        case 4: if((pe->x()>=Vnuchka[0].x()+Vnuchka[0].width()/2)&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width()/2+Vnuchka[0].width()/6)&&
                   (pe->y()>=Vnuchka[0].y()+Vnuchka[0].height()/3)&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()/2+Vnuchka[0].height()/8))
                {
                    yes->play();
                    ++number;
                    Vnuchka[3].hide();
                    Vnuchka[4].show();
                    Mysl_Object[4].hide();
                    Mysl_Object[5].show();
                    Pen[index].hide();
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        case 5: if((pe->x()>=Vnuchka[0].x()+Vnuchka[0].width()/20)&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width()/4)&&
                   (pe->y()>=Vnuchka[0].y()+Vnuchka[0].height()/3)&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()/2+Vnuchka[0].height()/8))
                {
                    yes->play();
                    ++number;
                    Vnuchka[4].hide();
                    Vnuchka[5].show();
                    Mysl_Object[5].hide();
                    Mysl_Object[6].show();
                    Pen[index].hide();
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        case 6: if((pe->x()>=Vnuchka[0].x()+Vnuchka[0].width()/16)&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width()-Vnuchka[0].width()/4)&&
                   (pe->y()>=Vnuchka[0].y()+Vnuchka[0].height()/3)&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()-Vnuchka[0].height()/10))
                {
                    yes->play();
                    ++number;
                    Vnuchka[5].hide();
                    Vnuchka[6].show();
                    Mysl_Object[6].hide();
                    Mysl_Object[7].show();
                    Pen[index].hide();
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        case 7: if((pe->x()>=Vnuchka[0].x()+Vnuchka[0].width()/4)&&
                   (pe->x()<=Vnuchka[0].x()+Vnuchka[0].width()/2)&&
                   (pe->y()>=Vnuchka[0].y()+Vnuchka[0].height()-Vnuchka[0].height()/10)&&
                   (pe->y()<=Vnuchka[0].y()+Vnuchka[0].height()))
                {
                    yes->play();
                    Vnuchka[6].hide();
                    Vnuchka[7].show();
                    Mysl_Object[7].hide();
                    Mysl->hide();
                    Pen[index].hide();
                    movie->start();
                    ura->setVolume(100);
                    ura->play();
                    viktory->start(5000);
                } else
                {
                    Pen[index].move(old_x, old_y);                     // перемещаем карандаш на место
                    no->play();
                }
            break;
        }
    }
}

//--------------------------------------------- ПОБЕДА ------------------------------------------------

void Lev_4_Window::pobeda()
{
    level++;
    viktory->stop();
    timer_help->stop();
    delete [] Pen;
    delete [] Vnuchka;
    delete [] Mysl_Object;
    delete yes;
    delete no;
    delete ura;
    delete Background;
    delete viktory;
    delete Shariki;
    delete movie;
    delete Mysl;
    delete Holst;
    delete timer_help;
    delete Hand1;
    delete Masha;
    delete Subject_Area;
    delete Button_Return;
    return_to_mainwindow();
}

//--------------------------------------- Подсказка в игре ------------------------------------------------

void Lev_4_Window::help_game()
{
    static int hand_x1, hand_y1;            // счетчики
    int x, x1, y, y1;                       // начальные и конечные координаты руки

    x = Pen[1].x()-Hand1->width()/4+hand_x1;
    y = Pen[1].y()+Pen[1].height()/2+hand_y1;
    x1 = Vnuchka[0].x()+Vnuchka[0].width()/4;
    y1 = Vnuchka[0].y()+Vnuchka[0].height()/4;

    if(x==x1)
    {
        x=x1;
    } else
    {
        ++hand_x1;
    }
    if(y==y1)
    {
        y=y1;
    } else
    {
        ++hand_y1;
    }
    if((x==x1)&&(y==y1))
    {
        x=old_x1;
        y=old_y1;
        hand_x1=0;
        hand_y1=0;
    }

    Hand1->move(x, y);
}
