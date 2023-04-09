#include "lev_3_window.h"

Lev_3_Window::Lev_3_Window(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));

    FLAG_PRODUKT = false;                                                               // предмет не выбран
    FLAG_KOLOBOK = false;                                                               // тесто не готово
    FLAG_MOVE_KOLOBOK_X = false;                                                        // колобок полетит изначально вправо
    FLAG_MOVE_KOLOBOK_Y = false;                                                        // колобок полетит изначально вниз

    level = 3;                                                                          // номер уровня
    index = 0;                                                                          // индекс 1 предмета (тазик)

    timer_help  = new QTimer;                                                           // таймер подсказки
    timer_help_kolobok = new QTimer;                                                    // таймер подсказки: колобок в печь
    timer_show_kolobok = new QTimer;                                                    // таймер появления колобка
    timer_move_kolobok = new QTimer;

    Background = new QLabel(this);
    setCentralWidget(Background);                                                       // QLabel назначаем центральным виджетом
    Background->setStyleSheet("border-image: url(:/res3/level_3.jpg);");                // ставим фон
    Background->showFullScreen();

    Button_Return = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);
    Button_Return->raise();

    Stol = new Static_Object(":/res3/stol.png", 450, 450, this);
    Stol->move(desktop_width/2-Stol->width()/2, desktop_height-Stol->height()+50);
    Stol->raise();

    Babka = new Static_Object(":/res3/babka.png", 450, 450, this);
    Babka->move(desktop_width-Babka->width(), desktop_height-Babka->height());
    Babka->raise();
    Mysl = new Static_Object(":/res2/mysl.png", 300, 300, this);
    Mysl->move(Babka->x()+Babka->width()/3, Babka->y()-Babka->height()/2-50);

    Produkt     = new Static_Object[8];
    Produkt[0].pic_obj(":/res3/tazik-01.png");
    Produkt[0].resize_obj(150,150);
    Produkt[0].move(5, desktop_height-270);
    Produkt[1].pic_obj(":/res3/milk.png");
    Produkt[1].resize_obj(100,100);
    Produkt[2].pic_obj(":/res3/muka.png");                  // Инициализируем массив продуктов
    Produkt[2].resize_obj(100,100);
    Produkt[3].pic_obj(":/res3/egs.png");
    Produkt[3].resize_obj(100,100);
    Produkt[4].pic_obj(":/res3/oil.png");
    Produkt[4].resize_obj(100,100);
    Produkt[5].pic_obj(":/res3/sol.png");
    Produkt[5].resize_obj(80,80);
    Produkt[6].pic_obj(":/res3/venchik.png");
    Produkt[6].resize_obj(100,100);
    Produkt[7].pic_obj(":/res3/kolobok.png");
    Produkt[7].resize_obj(0,0);

    Tazik   = new Static_Object[5];
    Tazik[0].pic_obj(":/res3/tazik-02.png");
    Tazik[1].pic_obj(":/res3/tazik-03.png");
    Tazik[2].pic_obj(":/res3/tazik-04.png");                // Массив содержимого тазика
    Tazik[3].pic_obj(":/res3/tazik-05.png");
    Tazik[4].pic_obj(":/res3/tazik-06.png");

    Produkt_Babka   = new Static_Object[8];
    Produkt_Babka[0].pic_obj(":/res3/tazik-01.png");
    Produkt_Babka[0].resize_obj(150,150);
    Produkt_Babka[0].move(Mysl->x()+Mysl->width()/4, Mysl->y()+Mysl->height()/8);
    Produkt_Babka[1].pic_obj(":/res3/milk.png");
    Produkt_Babka[1].resize_obj(100,100);
    Produkt_Babka[2].pic_obj(":/res3/muka.png");
    Produkt_Babka[2].resize_obj(100,300);
    Produkt_Babka[3].pic_obj(":/res3/egs.png");             // Массив продуктов о которых думает бабка
    Produkt_Babka[3].resize_obj(100,100);
    Produkt_Babka[4].pic_obj(":/res3/oil.png");
    Produkt_Babka[4].resize_obj(100,100);
    Produkt_Babka[5].pic_obj(":/res3/sol.png");
    Produkt_Babka[5].resize_obj(60,60);
    Produkt_Babka[6].pic_obj(":/res3/venchik.png");
    Produkt_Babka[6].resize_obj(100,100);
    Produkt_Babka[7].pic_obj(":/res3/pechka.png");
    Produkt_Babka[7].resize_obj(100,100);

    for(int i=0; i<8; ++i)
    {
        Produkt[i].setParent(this);
        Produkt_Babka[i].setParent(this);                   // инициализация объектов
        Produkt_Babka[i].hide();
    }

    for(int i=0; i<5; ++i)
    {
        Tazik[i].setParent(this);
        Tazik[i].resize_obj(150,150);
        Tazik[i].hide();
    }

    Produkt_Babka[0].show();
    Hand    = new Static_Object(":/res/ruka.png", 100, 100, this);          // подсказка - рука

    yes = new QMediaPlayer;
    yes->setMedia(QUrl("qrc:/res1/yes.mp3"));
    yes->setVolume(0);
    yes->play();

    no  = new QMediaPlayer;
    no->setMedia(QUrl("qrc:/res1/nea.wav"));
    no->setVolume(0);
    no->play();

    stuk    = new QMediaPlayer;
    stuk->setMedia(QUrl("qrc:/res1/tuk.mp3"));
    stuk->setVolume(0);
    stuk->play();

    shows   = new QMediaPlayer;
    shows->setMedia(QUrl("qrc:/res1/show.mp3"));
    shows->setVolume(0);
    shows->play();

    old_x = Produkt[0].x();                            // Начальные координаты корзины
    old_y = Produkt[0].y();

    init();                                             // инициализация предметов на поле

    timer_help->start(3);

    connect(Button_Return,  &QPushButton::clicked,  this,   &Lev_3_Window::return_to_mainwindow);       // Возврат на карту
    connect(timer_help,     &QTimer::timeout,       this,   &Lev_3_Window::help_game);                  // подсказка
    connect(timer_help_kolobok, &QTimer::timeout,   this,   &Lev_3_Window::help_game_kolobok);          // подсказка тесто в печку
    connect(timer_show_kolobok, &QTimer::timeout,   this,   &Lev_3_Window::show_kolobok);               // показать колобка
    connect(timer_move_kolobok, &QTimer::timeout,   this,   &Lev_3_Window::move_kolobok);               // движение колобка
}

Lev_3_Window::~Lev_3_Window()
{
    delete Background;
    delete Button_Return;
    delete [] Produkt;
    delete [] Produkt_Babka;
    delete [] Tazik;
    delete timer_help;
    delete timer_help_kolobok;
    delete timer_show_kolobok;
    delete timer_move_kolobok;
    delete yes;
    delete no;
    delete stuk;
    delete shows;
    delete Hand;
    delete Mysl;
    delete Stol;
    delete Babka;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Lev_3_Window::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k = rand()%b+a;
    return k;
}

//-------------------------- возвращение на главный экран -----------------------------------

void Lev_3_Window::return_to_mainwindow()
{
    emit number_level(level);                               // передаем сигнал с номером уровня
    this->hide();
}

//------------------------------- инициализация объектов -------------------------------------

void Lev_3_Window::init()
{
    int x[7], y[7], arr[7];
    int i=1, k;

    while(i<7)                                          // пока не установлены координаты всех продуктов выполняем цикл
    {
        k = rnd(1,6);                                   // берем случайное число

        for(int j=i; j>=1; --j)                         // для j от i пока не станет равным 1
        {
            if(arr[j] == k) break;                      // если j-е число массива равно k, то прерываем цикл
            else if(j==1)                               // иначе, если совпадений нет, то
            {
                arr[i] = k;                             // присваиваем j-му числу массива значение k

                switch (k)                              // определяем координаты для случайного числа k
                {
                case 1: x[i] = desktop_width/20; y[i] = desktop_height/4; break;
                case 2: x[i] = desktop_width/3;  y[i] = desktop_height/2; break;
                case 3: x[i] = desktop_width/2+desktop_width/4; y[i] = desktop_height/2-desktop_height/40; break;
                case 4: x[i] = desktop_width/5; y[i] = desktop_height/2+desktop_height/6; break;
                case 5: x[i] = desktop_width/2+desktop_width/8; y[i] = desktop_height/2+desktop_height/20; break;
                case 6: x[i] = desktop_width/2; y[i] = desktop_height/2+desktop_height/4+desktop_height/12; break;
                }

                    Produkt[i].move(x[i], y[i]);       // размещаем объект со случайными координатами
                    ++i;
                }
            }
    }
}

//---------------------------------- События при нажатии кнопки мышки ------------------------------------

void Lev_3_Window::mousePressEvent(QMouseEvent *pe)
{
    if(!FLAG_KOLOBOK)           // если тесто еще не готово
    {
        if((pe->x()>Produkt[index].x())&&(pe->x()<Produkt[index].x()+Produkt[index].width())&&
           (pe->y()>Produkt[index].y())&&(pe->y()<Produkt[index].y()+Produkt[index].height()))
        {
            old_x = Produkt[index].x();            // Запоминаем координаты, где находился предмет,
            old_y = Produkt[index].y();            // который мы взяли
            FLAG_PRODUKT = true;                    // запоминаем, что предмет выбран
            Hand->hide();                           // скрываем подсказку
            timer_help->stop();
        }
    } else
    {
        if((pe->x()>Tazik[4].x())&&(pe->x()<Tazik[4].x()+Tazik[4].width())&&             // если тесто готово
           (pe->y()>Tazik[4].y())&&(pe->y()<Tazik[4].y()+Tazik[4].height()))
        {
            timer_help_kolobok->stop();
            Hand->hide();
            old_x = Tazik[4].x();                  // принцип тот же, что и со всеми предметами
            old_y = Tazik[4].y();
            FLAG_PRODUKT = true;
        }
    }

}

//------------------------------------ События при движении мышки ----------------------------------------

void Lev_3_Window::mouseMoveEvent(QMouseEvent *pe)
{
    if(!FLAG_KOLOBOK)                   // если тесто не готово, то перемещаем продукты
    {
        if(FLAG_PRODUKT)
        {
            Produkt[index].move(pe->x()-Produkt[index].width()/2, pe->y()-Produkt[index].height()/2);  // курсор по центру предмета
            Produkt[index].raise();                                                                      // предмет на передний план
        }
    }   else
    {
        if(FLAG_PRODUKT)            // если тесто готово, то перемещаем тазик с тестом в печь
        {
            Tazik[4].move(pe->x()-Tazik[4].width()/2, pe->y()-Tazik[4].height()/2);
            Tazik[4].raise();
        }
    }
}

//------------------------------------ События при отпускании кнопки мышки -------------------------------

void Lev_3_Window::mouseReleaseEvent(QMouseEvent *pe)
{
    if(!FLAG_KOLOBOK)           // если тесто не готово, добавляем ингридиенты
    {
        if((pe->x()>Stol->x())&&(pe->x()<Stol->x()+Stol->width())&&                 // поставили ли предмет на стол
           (pe->y()>Stol->y())&&(pe->y()<Stol->y()+Stol->height()/4)&&FLAG_PRODUKT)
        {
            yes->setVolume(100);
            yes->play();

            if(index==0)                                                            // если поставили корзину увеличим ее немного
            {
                Produkt[0].move(Stol->x()+Stol->width()/2-Produkt[0].width()/2, Stol->y());
            }

            ++index;                                                                // индекс следующего продмета

            if(index>=7)
            {
                index=7;
                FLAG_KOLOBOK=true;                                                  // тесто готово
                timer_help_kolobok->start(3);                                       // запускаем подсказку тесто в печь
            }

            FLAG_PRODUKT=false;
            old_x = Produkt[index].x();                                            // начальные координаты нового предмета
            old_y = Produkt[index].y();
            Produkt_Babka[index-1].hide();
            if(index>=2) Produkt[index-1].hide();
            if(index==2)
            {
                Produkt_Babka[index].move(Mysl->x()+Mysl->width()/4, Mysl->y()+Mysl->height()/20);  // обновляем мысли бабки - мука
            } else
            {
                Produkt_Babka[index].move(Mysl->x()+Mysl->width()/4, Mysl->y()+Mysl->height()/4);  // обновляем мысли бабки - остальные
            }
            Produkt_Babka[index].show();
            switch(index)                                                                           //   меняем содержимое тазика
            {
            case 2: Produkt[0].hide(); Tazik[0].move(Stol->x()+Stol->width()/2-Tazik[0].width()/2, Stol->y()); Tazik[0].show(); break;
            case 3: Tazik[0].hide(); Tazik[1].move(Stol->x()+Stol->width()/2-Tazik[1].width()/2, Stol->y()); Tazik[1].show(); break;
            case 4: Tazik[1].hide(); Tazik[2].move(Stol->x()+Stol->width()/2-Tazik[2].width()/2, Stol->y()); Tazik[2].show(); break;
            case 5: Tazik[2].hide(); Tazik[3].move(Stol->x()+Stol->width()/2-Tazik[3].width()/2, Stol->y()); Tazik[3].show(); break;
            case 6: Tazik[2].hide(); Tazik[3].move(Stol->x()+Stol->width()/2-Tazik[3].width()/2, Stol->y()); Tazik[3].show(); break;
            case 7: Tazik[3].hide(); Tazik[4].move(Stol->x()+Stol->width()/2-Tazik[4].width()/2, Stol->y()); Tazik[4].show(); break;
            }

        } else
        {
            no->setVolume(100);
            no->play();
            Produkt[index].move(old_x, old_y);
            FLAG_PRODUKT=false;
        }
    } else      // если тесто готово, перемещаем его на печь, чтобы появился колобок
    {
        if((pe->x()<desktop_width/4)&&(pe->y()<desktop_height/2+desktop_height/10)&&(pe->y()>desktop_height/10))
        {
            Tazik[4].hide();                           // Скрываем тазик и показываем колобка
            Produkt[7].show();
            Mysl->hide();
            Produkt_Babka[7].hide();
            FLAG_KOLOBOK = true;
            shows->setVolume(100);
            shows->play();
            stuk->setVolume(100);
            timer_show_kolobok->start(9);
        }
    }
}

//----------------------------------------- подсказка в начале уровня -------------------------------------

void Lev_3_Window::help_game()
{
    static int hand_x;          // счетчики координат
    static int hand_y;
    int x, x1;                  // начальные и конечные координаты руки
    int y, y1;
    int old_xm, old_ym;         // начальное положение тазика

    x = Produkt[0].x()+Produkt[0].width()/2-Hand->width()/2+hand_x;
    y = Produkt[0].y()+Produkt[0].height()/2+hand_y;
    old_xm = Produkt[0].x()+Produkt[0].width()/2;
    old_ym = Produkt[0].y()+Produkt[0].height()/2;
    x1 = Stol->x()+Stol->width()/2;
    y1 = Stol->y()+Stol->height()/4;

    if(x==x1)
    {
        x=x1;
    } else
    {
        ++hand_x;
    }

    if(y==y1)
    {
        y=y1;
    } else
    {
        --hand_y;
    }

    if((x==x1)&&(y==y1))
    {
        x = old_xm;
        y = old_ym;
        hand_x=0;
        hand_y=0;
    }
    Hand->move(x,y);
}

//----------------------------------------- подсказка - тесто в печь -------------------------------------

void Lev_3_Window::help_game_kolobok()
{
    static int hand_x1, hand_y1;            // счетчики
    int x, x1, y, y1;                       // начальные и конечные координаты руки
    int old_x1, old_y1;

    x = Stol->x()+Stol->width()/2+hand_x1;
    y = Stol->y()+Stol->height()/20+hand_y1;
    x1 = desktop_width/8;
    y1 = desktop_height/2;
    old_x1 = Stol->x()+Stol->width()/2;
    old_y1 = Stol->y()+Stol->height()/20;

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
        --hand_y1;
    }

    if((x==x1)&&(y==y1))
    {
        x = old_x1;
        y = old_y1;
        hand_x1=0;
        hand_y1=0;
    }
    Hand->move(x,y);
    Hand->show();
}

//------------------------------------- Показываем колобка на столе -----------------------------------

void Lev_3_Window::show_kolobok()
{
    static int size_kolobok, i;

    Produkt[7].resize_obj(size_kolobok,size_kolobok);
    Produkt[7].move(old_x,old_y);
    ++size_kolobok;
    ++i;
    if(size_kolobok>=100) size_kolobok = 100;
    if(i>=300)
    {
        timer_show_kolobok->stop();
        kol_x = Produkt[7].x();
        kol_y = Produkt[7].y();
        timer_move_kolobok->start(2);
    }
}

//------------------------------------------- Движение колобка ----------------------------------------

void Lev_3_Window::move_kolobok()
{
    static int index;
    ++index;

    if(index > 5000)
    {
        level++;
        delete Background;
        delete Button_Return;
        delete [] Produkt;
        delete [] Produkt_Babka;
        delete [] Tazik;
        delete timer_help;
        delete timer_help_kolobok;
        delete timer_show_kolobok;
        delete timer_move_kolobok;
        delete yes;
        delete no;
        delete stuk;
        delete shows;
        delete Hand;
        delete Mysl;
        delete Stol;
        delete Babka;
        return_to_mainwindow();

    }

    if(!FLAG_MOVE_KOLOBOK_X && !FLAG_MOVE_KOLOBOK_Y)
    {
        kol_x = kol_x+2;
        kol_y = kol_y+2;
        if(kol_x>desktop_width)
        {
            FLAG_MOVE_KOLOBOK_X=true;
            stuk->play();
        }
        if(kol_y>desktop_height)
        {
            FLAG_MOVE_KOLOBOK_Y=true;
            stuk->play();
        }
    }

    if(FLAG_MOVE_KOLOBOK_X && FLAG_MOVE_KOLOBOK_Y)
    {
        kol_x = kol_x-2;
        kol_y = kol_y-2;
        if(kol_x<0)
        {
            FLAG_MOVE_KOLOBOK_X=false;
            stuk->play();
        }
        if(kol_y<0)
        {
            FLAG_MOVE_KOLOBOK_Y=false;
            stuk->play();
        }
    }
    if(!FLAG_MOVE_KOLOBOK_X && FLAG_MOVE_KOLOBOK_Y)
    {
        kol_x = kol_x+2;
        kol_y = kol_y-2;
        if(kol_x>desktop_width)
        {
            FLAG_MOVE_KOLOBOK_X=true;
            stuk->play();
        }
        if(kol_y<0)
        {
            FLAG_MOVE_KOLOBOK_Y=false;
            stuk->play();
        }
    }
    if(FLAG_MOVE_KOLOBOK_X && !FLAG_MOVE_KOLOBOK_Y)
    {
        kol_x = kol_x-2;
        kol_y = kol_y+2;
        if(kol_x<0)
        {
            FLAG_MOVE_KOLOBOK_X=false;
            stuk->play();
        }
        if(kol_y>desktop_height)
        {
            FLAG_MOVE_KOLOBOK_Y=true;
            stuk->play();
        }
    }
    Produkt[7].move(kol_x, kol_y);
}
