#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    desktop_size();

    level = 1;

    mapwindow   = new MapWindow();

    Background  = new QLabel(this);
    setCentralWidget(Background);                                                   // QLabel назначаем центральным виджетом
    Background->setStyleSheet("border-image: url(:/res/repka-fon.jpg);");           // ставим фон
    Background->showFullScreen();

    Button_Start    = new QPushButton(this);
    Button_Exit     = new QPushButton(this);

    Button_Exit->setStyleSheet("border-image: url(:/res/prosrach.png);");           // Кнопка выход
    Button_Exit->setStyleSheet("border-image: url(:/res/exit2.png);");
    Button_Exit->resize(200,200);
    Button_Exit->move(desktop_width-300, desktop_height-300);

    Button_Start->setStyleSheet("border-image: url(:/res/prosrach.png);");          // Кнопка старт
    Button_Start->setStyleSheet("border-image: url(:/res/start.png);");
    Button_Start->resize(300,200);
    Button_Start->move(50, 50);

    connect(Button_Exit,    &QPushButton::clicked,      this,       &MainWindow::exit_to_game);             // обработка кнопки выход
    connect(Button_Start,   &QPushButton::clicked,      this,       &MainWindow::go_to_mapwindow);          // кнопка старт
    connect(mapwindow,      &MapWindow::number_level,   this,       &MainWindow::return_mainwindow);        // возврат на главный экран
    connect(this,           &MainWindow::number_level,  mapwindow,  &MapWindow::priem_level);               // посылаем номер текущего уровня
}

MainWindow::~MainWindow()
{
    delete Background;
    delete Button_Exit;
    delete Button_Start;
    delete mapwindow;
}

//---------------------------------------------------------------------------------------------------------------------

void MainWindow::exit_to_game()
{
    exit(0);
}


//______________________ присваиваем значения screen_widtch и screen_height __________________________

void MainWindow::desktop_size()
{
    QDesktopWidget *deskt_size = QApplication::desktop();
    desktop_width = deskt_size->width();                      // определяем разрешение экрана и запоминаем ширину и высоту
    desktop_height = deskt_size->height();
    delete deskt_size;
}

//---------------------------------------------------------------------------------------------------------------------

void MainWindow::go_to_mapwindow()
{
    emit number_level(level);
    this->hide();
    mapwindow->showFullScreen();
}

//---------------------------------------------------------------------------------------------------------------------
void MainWindow::return_mainwindow(int num)
{
    level = num;
    this->showFullScreen();
}
