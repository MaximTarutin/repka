#include "mapwindow.h"

MapWindow::MapWindow(QWidget *parent) : QMainWindow(parent)
{
    hinttimer       = new QTimer;
    hand_timer      = new QTimer;
    persona_timer   = new QTimer;
    victory_timer   = new QTimer;

    level2win   = new Lev_2_Window();
    level3win   = new Lev_3_Window();
    level4win   = new Lev_4_Window();                                                   // уровни игры
    level5win   = new Lev_5_Window();
    level6win   = new Lev_6_Window();
    level7win   = new Lev_7_Window();

    FLAG_VEGETABLES     = false;                                                        // объект еще не выбран мышкой
    FLAG_START_GAME     = false;                                                        // игра ещё не началась
    FLAG_WAV            = true;
    active_vegetables   = 8;                                                            // активный объект тыква
    Background  = new QLabel(this);
    setCentralWidget(Background);                                                       // QLabel назначаем центральным виджетом
    Background->setStyleSheet("border-image: url(:/res/dom-fon.jpg);");                 // ставим фон
    Background->showFullScreen();

    Button_Return   = new QPushButton(this);
    Button_Return->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Return->setStyleSheet("border-image: url(:/res/return.png);");               // Возврат на главный экран
    Button_Return->move(100,100);
    Button_Return->resize(100,100);

    Button_Next     = new QPushButton(this);                                            // Переход на следующий уровень
    Button_Next->setStyleSheet("border-image: url(:/res/prosrach.png);");
    Button_Next->setStyleSheet("border-image: url(:/res/next.png);");
    Button_Next->move(desktop_width-200, 100);
    Button_Next->resize(100,100);

    Button_Next->hide();

    playlist    = new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/res1/fon.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);                        // фоновая музыка играет бесконечно

    fon_sound   = new QMediaPlayer;
    fon_sound->setPlaylist(playlist);
    fon_sound->setVolume(30);
    fon_sound->play();

    yes = new QMediaPlayer;
    yes->setMedia(QUrl("qrc:/res1/yes.mp3"));
    yes->setVolume(0);
    yes->play();

    no  = new QMediaPlayer;
    no->setMedia(QUrl("qrc:/res1/nea.wav"));
    no->setVolume(0);
    no->play();

    Tada  = new QMediaPlayer;
    Tada->setMedia(QUrl("qrc:/res1/tada.wav"));
    Tada->setVolume(0);
    Tada->play();

    Repka_Wav   = new QMediaPlayer;
    Repka_Wav->setMedia(QUrl("qrc:/res1/repka.wav"));
    Repka_Wav->setVolume(0);
    Repka_Wav->play();

    Viktory = new QMediaPlayer;
    Viktory->setMedia(QUrl("qrc:/res1/viktory.wav"));
    Viktory->setVolume(0);
    Viktory->play();

    The_End = new Static_Object(":/res/theend.png", 0, 0, this);
    The_End->move(desktop_width/2, desktop_height/2);
    The_End->hide();

    Repka   = new Static_Object(":/res/repka.png", 0, 0, this);                     // выделяем память для игровых объектов
    Repka->move(100, desktop_height-360);
    Repka->hide();

    Dedka   = new Static_Object(":/res/dedka.png", 400, 400, this);
    Dedka->move(350,desktop_height-400);
    Dedka->hide();

    Babka   = new Static_Object(":/res/babka.png", 400, 400, this);
    Babka->move(600,desktop_height-400);
    Babka->hide();

    Vnuchka = new Static_Object(":/res/vnuchka.png", 400, 400, this);
    Vnuchka->move(830,desktop_height-400);
    Vnuchka->hide();

    Zuchka = new Static_Object(":/res/zuchka.png", 300, 300, this);
    Zuchka->move(1100,desktop_height-300);
    Zuchka->hide();

    Koshka = new Static_Object(":/res/koshka.png", 300, 300, this);
    Koshka->move(1300,desktop_height-300);
    Koshka->hide();

    Myshka = new Static_Object(":/res/myshka.png", 150, 150, this);
    Myshka->move(1480,desktop_height-180);
    Myshka->hide();

    Tomat   = new Static_Object(":/res/tomat.png", 200, 200, this);
    Tomat->move(desktop_width-400, 100);

    Gray_Tomat  = new Static_Object(":/res/tomat-gray.png", 200, 200, this);
    Gray_Tomat->move(300, desktop_height-260);

    Chesnok     = new Static_Object(":/res/chesnok.png", 200, 200, this);
    Chesnok->move(desktop_width-360, 100);

    Gray_Chesnok    = new Static_Object(":/res/chesnok-gray.png", 200, 200, this);
    Gray_Chesnok->move(desktop_width/15, desktop_height/2);

    Grusha          = new Static_Object(":/res/grusha.png", 200, 200, this);
    Grusha->move(desktop_width-360, 100);

    Gray_Grusha     = new Static_Object(":/res/grusha-gray.png", 200, 200, this);
    Gray_Grusha->move(desktop_width/2, desktop_height/2-30);

    Kartoshka       = new Static_Object(":/res/kartoshka.png", 200, 200, this);
    Kartoshka->move(desktop_width-360, 100);

    Gray_Kartoshka  = new Static_Object(":/res/kartoshka-gray.png", 200, 200, this);
    Gray_Kartoshka->move(desktop_width/2+300, desktop_height/2+60);

    Morkovka        = new Static_Object(":/res/morkovka.png", 300, 300, this);
    Morkovka->move(desktop_width-360, 100);

    Gray_Morkovka   = new Static_Object(":/res/morkovka-gray.png", 300, 300, this);
    Gray_Morkovka->move(desktop_width/2-400, desktop_height/2-80);

    Ogurec          = new Static_Object(":/res/ogurec.png", 200, 200, this);
    Ogurec->move(desktop_width-360, 110);

    Gray_Ogurec     = new Static_Object(":/res/ogurec-gray.png", 200, 200, this);
    Gray_Ogurec->move(desktop_width-200, desktop_height/2+100);

    Rediska         = new Static_Object(":/res/rediska.png", 200, 200, this);
    Rediska->move(desktop_width-360, 100);

    Gray_Rediska    = new Static_Object(":/res/rediska-gray.png", 200, 200, this);
    Gray_Rediska->move(desktop_width-400, desktop_height/2-40);

    Tykva           = new Static_Object(":/res/tykva.png", 400, 400, this);
    Tykva->move(desktop_width-420, 30);

    Gray_Tykva      = new Static_Object(":/res/tykva-gray.png", 400, 400, this);
    Gray_Tykva->move(desktop_width/2, desktop_height-400);

    Hand    = new Static_Object(":/res/ruka.png", 100, 100, this);
    Hand->move(Tykva->x()+Tykva->width()/2, Tykva->y()+Tykva->height()/2);

    hand_timer->start(3);


    connect(Button_Return,  &QPushButton::clicked,      this,   &MapWindow::return_to_mainwindow);          // возврат на главную страницу
    connect(hinttimer,      &QTimer::timeout,           this,   &MapWindow::hint);                          // действия при завершении таймера
    connect(hand_timer,     &QTimer::timeout,           this,   &MapWindow::help_level);                    // подсказка
    connect(Button_Next,    &QPushButton::clicked,      this,   &MapWindow::next_level);                    // кнопка дальше
    connect(level2win,      &Lev_2_Window::number_level,this,   &MapWindow::return_to_mapwindow);           // возврат на карту
    connect(level3win,      &Lev_3_Window::number_level,this,   &MapWindow::return_to_mapwindow);           //
    connect(level4win,      &Lev_4_Window::number_level,this,   &MapWindow::return_to_mapwindow);           //
    connect(level5win,      &Lev_5_Window::number_level,this,   &MapWindow::return_to_mapwindow);           //
    connect(level6win,      &Lev_6_Window::number_level,this,   &MapWindow::return_to_mapwindow);           //
    connect(level7win,      &Lev_7_Window::number_level,this,   &MapWindow::return_to_mapwindow);           //
    connect(persona_timer,  &QTimer::timeout,           this,   &MapWindow::persona_show);                  // показываем очередной персонаж
    connect(victory_timer,  &QTimer::timeout,           this,   &MapWindow::the_end_game);                  // конец игры, появляется надпись
}

MapWindow::~MapWindow()
{
    delete Button_Next;
    delete Button_Return;
    delete Repka;
    delete Dedka;
    delete Babka;
    delete Vnuchka;
    delete Zuchka;
    delete Koshka;
    delete Myshka;
    delete Background;
    delete Gray_Chesnok;
    delete Gray_Grusha;
    delete Gray_Kartoshka;
    delete Gray_Morkovka;
    delete Gray_Ogurec;
    delete Gray_Rediska;
    delete Gray_Tykva;
    delete Gray_Tomat;
    delete Chesnok;
    delete Grusha;
    delete Kartoshka;
    delete Morkovka;
    delete Ogurec;
    delete Rediska;
    delete Tykva;
    delete Tomat;
    delete hinttimer;
    delete playlist;
    delete fon_sound;
    delete yes;
    delete no;
    delete Viktory;
    delete Repka_Wav;
    delete Hand;
    delete persona_timer;
    delete Tada;
    delete The_End;
    delete victory_timer;
}

//----------------------- возврат на главную страницу ----------------------------------

void MapWindow::return_to_mainwindow()
{
    emit number_level(level);
    this->hide();
}

//-------------------------- События при нажатии кнопки мышки --------------------------

void MapWindow::mousePressEvent(QMouseEvent *pe)
{
    switch(active_vegetables)
    {
    case 1: old_vegetables_x = Tomat->x();                                      // Запоминаем начальные координаты объекта
            old_vegetables_y = Tomat->y();
            Tomat->raise();                                                     // Выставляем объект поверх других
            check_flag_vegetables(Tomat, Gray_Tomat, pe);           break;      // Устанавливае состояние флага
    case 2: old_vegetables_x = Chesnok->x();
            old_vegetables_y = Chesnok->y();
            Chesnok->raise();
            check_flag_vegetables(Chesnok, Gray_Chesnok, pe);       break;
    case 3: old_vegetables_x = Grusha->x();
            old_vegetables_y = Grusha->y();
            Grusha->raise();
            check_flag_vegetables(Grusha, Gray_Grusha, pe);         break;
    case 4: old_vegetables_x = Kartoshka->x();
            old_vegetables_y = Kartoshka->y();
            Kartoshka->raise();
            check_flag_vegetables(Kartoshka, Gray_Kartoshka, pe);   break;
    case 5: old_vegetables_x = Morkovka->x();
            old_vegetables_y = Morkovka->y();
            Morkovka->raise();
            check_flag_vegetables(Morkovka, Gray_Morkovka, pe);     break;
    case 6: old_vegetables_x = Ogurec->x();
            old_vegetables_y = Ogurec->y();
            Ogurec->raise();
            check_flag_vegetables(Ogurec, Gray_Ogurec, pe);         break;
    case 7: old_vegetables_x = Rediska->x();
            old_vegetables_y = Rediska->y();
            Rediska->raise();
            check_flag_vegetables(Rediska, Gray_Rediska, pe);       break;
    case 8: old_vegetables_x = Tykva->x();
            old_vegetables_y = Tykva->y();
            Tykva->raise();
            check_flag_vegetables(Tykva, Gray_Tykva, pe);           break;
    }
}

//-------------------------- События при движении мышки с нажатой клавишей ------------------

void MapWindow::mouseMoveEvent(QMouseEvent *pe)
{
    if(FLAG_VEGETABLES)
    {
        switch (active_vegetables)
        {
        case 1: move_vegetables(Tomat, pe);         break;
        case 2: move_vegetables(Chesnok, pe);       break;
        case 3: move_vegetables(Grusha, pe);        break;
        case 4: move_vegetables(Kartoshka, pe);     break;
        case 5: move_vegetables(Morkovka, pe);      break;
        case 6: move_vegetables(Ogurec, pe);        break;
        case 7: move_vegetables(Rediska, pe);       break;
        case 8: move_vegetables(Tykva, pe);         break;
        }
    }
}

//--------------------------- События при отпускании кнопки мышки --------------------------

void MapWindow::mouseReleaseEvent(QMouseEvent *pe)
{
    switch(active_vegetables)
    {
    case 1: check_flag_vegetables(Tomat, Gray_Tomat, pe);           break;      // устанавливае состояние флага
    case 2: check_flag_vegetables(Chesnok, Gray_Chesnok, pe);       break;
    case 3: check_flag_vegetables(Grusha, Gray_Grusha, pe);         break;
    case 4: check_flag_vegetables(Kartoshka, Gray_Kartoshka, pe);   break;
    case 5: check_flag_vegetables(Morkovka, Gray_Morkovka, pe);     break;
    case 6: check_flag_vegetables(Ogurec, Gray_Ogurec, pe);         break;
    case 7: check_flag_vegetables(Rediska, Gray_Rediska, pe);       break;
    case 8: check_flag_vegetables(Tykva, Gray_Tykva, pe);           break;
    }

}

//---------------------------- Проверка состояния флага -----------------------------------

void MapWindow::check_flag_vegetables(Static_Object *vegetables, Static_Object *vegetables_yes, QMouseEvent *pe)
{
    if(FLAG_VEGETABLES == false)
    {
        if((pe->x() > vegetables->x())&&(pe->x() < vegetables->x()+vegetables->width())&&
           (pe->y() > vegetables->y())&&(pe->y() < vegetables->y()+vegetables->height()))
        {
            FLAG_VEGETABLES = true;                                 // если true, то перемещаем объект вместе с курсором мышки
            FLAG_START_GAME = true;                                 // убираем подсказку
            vegetables->move(pe->x()-vegetables->width()/2,
                             pe->y()-vegetables->height()/2);
        }
    } else
    {
        if((pe->x() > vegetables_yes->x())&&(pe->x() < vegetables_yes->x()+vegetables_yes->width())&&
           (pe->y() > vegetables_yes->y())&&(pe->y() < vegetables_yes->y()+vegetables_yes->height()))
        {
            FLAG_VEGETABLES = false;
            vegetables->move(vegetables_yes->x(), vegetables_yes->y());                 // поставили объект на место
            yes->setVolume(100);
            yes->play();
            active_vegetables--;
            delete vegetables_yes;
            if(active_vegetables==0) Victory();
        } else
        {
            FLAG_VEGETABLES = false;                                                    // иначе возвращаем на место
            vegetables->move(old_vegetables_x, old_vegetables_y);
            no->setVolume(100);
            no->play();
        }
    }
}

//------------------------------------ Перемещение объекта ------------------------------------

void MapWindow::move_vegetables(Static_Object *vegetables, QMouseEvent *pe)
{
    vegetables->move(pe->x()-vegetables->width()/2,
                     pe->y()-vegetables->height()/2);
}

//------------------------------ Победа 1 уровня (все овощи на месте)--------------------------

void MapWindow::Victory()
{
 hinttimer->start(1);
 Button_Next->show();
 level = 2;

}

//------------------------------------ События по таймеру, овощи разлетаются ------------------------------------

void MapWindow::hint()
{
    static int i,k;
    extern int desktop_width;
    extern int desktop_height;
    i++;
    Morkovka->move(Morkovka->x()+3, Morkovka->y()+1);
    Chesnok->move(Chesnok->x()-2, Chesnok->y()+3);
    Tykva->move(Tykva->x()-5, Tykva->y());
    Grusha->move(Grusha->x()+3, Grusha->y()-2);
    Kartoshka->move(Kartoshka->x()+2, Kartoshka->y()-5);
    Rediska->move(Rediska->x(), Rediska->y()+3);
    Ogurec->move(Ogurec->x()-4, Ogurec->y()-3);
    Tomat->move(Tomat->x()-3, Tomat->y()-6);
    if(i==1)
    {
        Viktory->setVolume(100);
        Viktory->play();
    }
    if(i==315)
    {
        Repka_Wav->setVolume(100);
        Repka_Wav->play();
    }
    if(i>315)
    {
        k++;
        Repka->move(80, desktop_height-200-k);
        Repka->resize_obj(Repka->width()+2, Repka->height()+2);
        Repka->show();

    }
    if((Morkovka->x()>desktop_width)&&(Chesnok->x()<-400)&&
       (Tykva->x()<-400)&&(Grusha->x()>desktop_width)&&
       (Kartoshka->x()>desktop_width)&&(Ogurec->x()<-400)&&
       (Morkovka->y()>desktop_height+10)&&(Chesnok->y()>desktop_height)&&
       (Grusha->y()<-400)&&(Kartoshka->y()<-400)&&(Rediska->y()>desktop_height)&&
       (Ogurec->y()<-400))
    {
        hinttimer->stop();
        delete Chesnok;
        delete Grusha;
        delete Kartoshka;
        delete Morkovka;
        delete Ogurec;
        delete Rediska;
        delete Tykva;
        delete Tomat;
        delete hinttimer;
        delete yes;
        delete no;
    }

}

//------------------------------------------- Подсказка в 1 уровне (рука) ---------------------------------

void MapWindow::help_level()
{
    static int hand_x;          // счетчик
    static int hand_y;
    int x, x1;                  // начальные и конечные координаты
    int y, y1;

    x  = hand_x+Tykva->x()+Tykva->width()/2;
    x1 = Gray_Tykva->x()+Gray_Tykva->width()/2;
    y  = Tykva->y()+Tykva->height()/2;
    y1 = Gray_Tykva->y()+Gray_Tykva->height()/2;

    if(x!=x1)
    {
        hand_x--;
    }

    if(hand_y!=y1)
    {
        hand_y++;
    }
    if((x==x1)&&(hand_y==y1))
    {
        hand_x = 0;
        hand_y = y;
        Hand->move(x, y);
    }

    if(!FLAG_START_GAME)
    {
        Hand->move(x,hand_y);
    } else
    {
        hand_timer->stop();
        delete Hand;
        delete hand_timer;
    }

}

//----------------------------------------- принимаем номер уровня ------------------------------

void MapWindow::priem_level(int lev)
{
    level = lev;
}

//------------------------------------- переход на следующий уровень ----------------------------

void MapWindow::next_level()
{
    switch(level)
    {
    case 2: this->hide(); level2win->showFullScreen(); break;
    case 3: this->hide(); level3win->showFullScreen(); break;
    case 4: this->hide(); level4win->showFullScreen(); break;
    case 5: this->hide(); level5win->showFullScreen(); break;
    case 6: this->hide(); level6win->showFullScreen(); break;
    case 7: this->hide(); level7win->showFullScreen(); break;
    }
}

//------------------------------------------ возврат на карту ------------------------------------

void MapWindow::return_to_mapwindow(int num)
{
    level = num;
    this->showFullScreen();
    persona_timer->start(10);
}

//------------------------------- появление очередного персонажа ---------------------------------

void MapWindow::persona_show()
{
    static int k;
    k=k+10;
    if(k>=400)
    {
        k = 0;
        persona_timer->stop();
        FLAG_WAV = true;
        return;
    }
    if(FLAG_WAV)
    {
        Repka_Wav->setVolume(100);
        Repka_Wav->play();
    }
    FLAG_WAV = false;
    switch (level)
    {
    case 3: Dedka->resize_obj(k,k); Dedka->show(); break;
    case 4: Babka->resize_obj(k,k); Babka->show(); break;
    case 5: Vnuchka->resize_obj(k,k); Vnuchka->show(); break;
    case 6: Zuchka->resize_obj(k-100,k-100); Zuchka->show(); break;
    case 7: Koshka->resize_obj(k-100,k-100); Koshka->show(); break;
    case 8: Myshka->resize_obj(k-200,k-200); Myshka->show(); victory_timer->start(3000);Tada->setVolume(100);
            Tada->play(); break;
    }
}

//-------------------------------- Конец игры, появляется надпись -------------------------------------

void MapWindow::the_end_game()
{

    The_End->resize_obj(800,400);
    The_End->move(desktop_width/2-300, desktop_height/4-200);
    The_End->show();
    Button_Next->hide();
}

