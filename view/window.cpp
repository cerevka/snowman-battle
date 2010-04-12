#include "window.h"
#include "view/dialogs/connecteddialog.h"

Window::Window()
{

    //Tady se pridavaji dalsi komponenty hlavniho okna

    //Vytvori hraci plochu
    scenepanel = new ScenePanel();
    setCentralWidget(scenepanel);

    statusbar = new StatusBar();
    chatpanel = new ChatPanel();

    QDockWidget *statusWidget = new QDockWidget(tr(""), this);
    statusWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    statusWidget->setFixedHeight(100);
    statusWidget->setWidget(statusbar);
    addDockWidget(Qt::BottomDockWidgetArea, statusWidget);

    QDockWidget *chatWidget = new QDockWidget(tr(""), this);
    chatWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
    chatWidget->setFixedWidth(250);
    chatWidget->setWidget(chatpanel);
    addDockWidget(Qt::RightDockWidgetArea, chatWidget);

    //////////////////Pro testovani/////////////

    /*QString *na = new QString("Balouch");
    QString *me = new QString("Tohle je zpravadfs fs dfdsf dsf dsf dsf d sf sd f dsf ds f dsf ds");
    chatpanel->newMessage(na, me);

    QString *pl = new QString("Balouch");
    statusbar->addPlayer(0, *pl);
    statusbar->changeScore(0, 10);

    QString *pl1 = new QString("Zabijak");
    statusbar->addPlayer(1, *pl1);

    QString *pl2 = new QString("Ajtak");
    statusbar->addPlayer(2, *pl2);

    QString *pl3 = new QString("Mad");
    statusbar->addPlayer(3, *pl3);

    QString *pl4 = new QString("Good");
    statusbar->addPlayer(4, *pl4);

    QString *pl5 = new QString("Blod");
    statusbar->addPlayer(5, *pl5);
*/
    QString *str = new QString("background1.jpg");
    scenepanel->setBackground(*str);
/*
    x1 = 265;
    y1 = 150;
    //snow1 = new PixmapItem("machine_gun.png", 30, 100, 30-80, 100-15);




    x = 200;
    y = 150;
    //snow = new PixmapItem("snowman_black.png", 150, 85, 150, 85);
    scenepanel->addNewPlayer(3, x, y, 0);
    scenepanel->addNewShot(0, 300, 300);
    scenepanel->addNewGun(0, 300, 250, 0, 0);
    //scenepanel->addNewGun(5, x1, y1, 0, 1);
    /////////////////Konec testovani////////////
*/
    //Vytvori akce
    createActions();

    //Vytvori menu
    createMenus();

    setWindowTitle(tr("Snowman Battle"));
    resize(1150, 700);

}

ScenePanel * Window::getScenePanel( void )
{
    return scenepanel;
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
        //int color = creategame.color->currentIndex();

        if(!nickname.compare(""))
        {
            QMessageBox::warning(this, tr("Create game"),
                                   tr("Please, insert your nickname."));
            return;
        }

        //TODO misto pro volani socketu
        Server * server = new Server(1234, players);
        Globals::network = new Network(server);
        QDialog *dia = new ConnectedDialog();
        dia->show();
        dia->exec();
        Globals::gameFacade->newGame(players + 1);
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
        //int port = joingame.port->text().toInt();
        //int color = joingame.color->currentIndex();

        if(!nickname.compare("") || !address.compare(""))
        {
            QMessageBox::warning(this, tr("Join game"),
                                   tr("Please, insert all items."));
            return;
        }



        //TODO misto pro volani socketu
        Client * client = new Client(QHostAddress(address), 1234);
        // zapouzdreni do Network
        Globals::network = new Network(client);

    }
}

//Nastaveni
void Window::settings()
{

    ///////////////////testovani//////////////////////////////////

    //scenepanel->changeGun(3, 1);

    /*
    scenepanel->changePlayerPosition(3, x--, y);
    scenepanel->removeGun(0);
    scenepanel->removeShot(0);
    scenepanel->changeGun(3, x%2);
    scenepanel->changePlayerDirection(3, x%4);
    scenepanel->setDirection(1, x%4);
    scenepanel->setPosition(2, x1--, y1--);
    scenepanel->setDirection(2, x%4);
    scenepanel->hidePlayer(3);
    if(x%4 == 0)
    {
        scenepanel->appearePlayer(3, x, y, x%3);
    }
    */

    scenepanel->changePlayerPosition(3, 180, 150);
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




