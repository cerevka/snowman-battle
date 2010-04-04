#include "window.h"

Window::Window()
{

    //Tady se pridavaji dalsi komponenty hlavniho okna

    //Vytvori hraci plochu
    scenepanel = new ScenePanel();
    setCentralWidget(scenepanel);

    //////////////////Pro testovani/////////////
    QString *str = new QString("background1.jpg");
    scenepanel->setBackground(*str);

    x1 = 300;
    y1 = 150;
    snow1 = new PixmapItem("machine_gun.png", 30, 100, 30-80, 100-15);
    scenepanel->setNewGraficObj(*snow1, x1, y1, 0);

    x = 200;
    y = 150;
    snow = new PixmapItem("snowman_black.png", 150, 85, 150, 85);
    scenepanel->setNewGraficObj(*snow, x, y, 0);
    /////////////////Konec testovani////////////

    //Vytvori akce
    createActions();

    //Vytvori menu
    createMenus();

    setWindowTitle(tr("Snowman Battle"));
    resize(800, 500);

}

void Window::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(createGameAct);
    gameMenu->addAction(joinGameAct);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAct);

    toolMenu = menuBar()->addMenu(tr("&Settings"));
    toolMenu->addAction(settingsAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void Window::createActions()
{
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcut(tr("Alt+F4"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


    createGameAct = new QAction(tr("&Create game"), this);
    createGameAct->setShortcut(tr("F2"));
    connect(createGameAct, SIGNAL(triggered()), this, SLOT(createGame()));

    joinGameAct = new QAction(tr("&Join game"), this);
    joinGameAct->setShortcut(tr("F3"));
    connect(joinGameAct, SIGNAL(triggered()), this, SLOT(joinGame()));

    settingsAct = new QAction(tr("&Settings"), this);
    settingsAct->setShortcut(tr("F5"));
    connect(settingsAct, SIGNAL(triggered()), this, SLOT(settings()));

    aboutAct = new QAction(tr("&About application"), this);
    aboutAct->setShortcut(tr("F1"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("&About Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

//Zalozi hru
void Window::createGame()
{
    CreateGame creategame;

    //Zpracuje informace z create game dialigu
    if (creategame.exec()) {
        QString nickname = creategame.nickname->text();
        int players = creategame.players->currentIndex();
        int color = creategame.color->currentIndex();
    }
}

//Pripoji se ke hre
void Window::joinGame()
{
    JoinGame joingame;

    //Zpracuje informace z join game dialigu
    if (joingame.exec()) {
        QString nickname = joingame.nickname->text();
        QString address = joingame.address->text();
        int port = joingame.port->text().toInt();
        int color = joingame.color->currentIndex();
    }
}

//Nastaveni
void Window::settings()
{

    ///////////////////testovani//////////////////////////////////

    scenepanel->setPosition(*snow, x--, y--);
    scenepanel->setPosition(*snow1, x1--, y1--);
    scenepanel->setDirection(*snow, x%4);
    scenepanel->setDirection(*snow1, x%4);



    ///////////////////testovani/////////////////////////////////

}

//O aplikaci
void Window::about()
 {
     QMessageBox::about(this, tr("About application Snowman Battle"),
            tr("Action game, with snowmans"));
 }

//O QT
void Window::aboutQt(){}




