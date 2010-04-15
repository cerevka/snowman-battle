#include "window.h"

Window::Window()
{

    //Tady se pridavaji dalsi komponenty hlavniho okna

    statusbar = new StatusBar();
    chatpanel = new ChatPanel();

    //Vytvori hraci plochu
    scenepanel = new ScenePanel();
    setCentralWidget(scenepanel);

    // predalokuje se pole jmen
    for (int i = 0; i < 6; ++i) {
        names.append(new QString ("Anonymous"));
    }


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

    //Nastavi pozadi plochy
    QString *str = new QString("background1.jpg");
    scenepanel->setBackground(*str);

    connectJoinDialog = NULL;

    //Vytvori akce
    createActions();

    //Vytvori menu
    createMenus();

    connect(Globals::packetParser, SIGNAL(gameStarted()), this, SLOT(createNewGame()));

    setWindowTitle(tr("Snowman Battle"));
    setFixedHeight(700);
    setFixedWidth(1150);
    //resize(1150, 700);

}

ScenePanel * Window::getScenePanel( void )
{
    return scenepanel;
}

ChatPanel * Window::getChatPanel( void )
{
    return chatpanel;
}

StatusBar * Window::getStatusBar( void )
{
    return statusbar;
}


void Window::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(createGameAct);
    gameMenu->addAction(joinGameAct);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAct);

    //toolMenu = menuBar()->addMenu(tr("&Settings"));
    //toolMenu->addAction(settingsAct);

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

    //settingsAct = new QAction(tr("&Settings"), this);
    //settingsAct->setShortcut(tr("F5"));
    //connect(settingsAct, SIGNAL(triggered()), this, SLOT(settings()));

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

        Globals::players = players;

        //TODO misto pro volani socketu
        names.replace(0, new QString(nickname));

        connectionDialog = new ConnectedDialog();

        QObject::connect(this, SIGNAL(clientNameAdded(int)), connectionDialog, SLOT(addPlayer(int)));

        Server * server = new Server(1234, players);

        qDebug() << "Ja jsem server a jmenuji se " << *names.at(0);


        connectionDialog->show();

        if(connectionDialog->exec())
        {
            qDebug() << "Jdu predstavovat " << players+1 << "hracu vcetne sebe.";

            // rozsirim mezi klienty jmena
            for (int i = 0; i < players+1; ++i) {
                Globals::packetCreator->assignName(i, names.at(i));
                qDebug() << "Rozeslal jsem jmeno" << *names.at(i) << " pro " << i;
            }


            Globals::packetCreator->startGame();
            Globals::isGameRunning = true;

            Globals::gameFacade->newGame(players + 1);
        }

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

        if(!nickname.compare("") || !address.compare(""))
        {
            QMessageBox::warning(this, tr("Join game"),
                                   tr("Please, insert all items."));
            return;
        }



        //TODO misto pro volani socketu
        Client * client = new Client(QHostAddress(address), 1234, nickname);

        connectJoinDialog = new ConnectJoinDialog();
        connectJoinDialog->show();
    }
}

//Nastaveni
void Window::settings()
{
}

//O aplikaci
void Window::about()
 {
     QMessageBox::about(this, tr("About application Snowman Battle"),
            tr("Action game, with snowmans"));
 }

//O QT
void Window::aboutQt(){}

void Window::addName(int id, QString * name)
{
    names.replace(id, name);
    emit clientNameAdded(id);
}

QString * Window::getName(int id)
{
    return names.at(id);
}

void Window::createNewGame()
{
    if(connectJoinDialog != NULL)
        connectJoinDialog->hide();

    Globals::isGameRunning = true;
    qDebug() << "new game";
    for (int i = 0; i < 6; ++i)
    {
        if(names.at(i)->compare("Anonymous"))
            statusbar->addPlayer(i);
    }
}

void Window::endGame(int id)
{
    EndGameDialog *end = new EndGameDialog();
    end->winner(id);
    end->show();

    if(end->exec())
    {
        scenepanel->deleteAllObjects();
    }
}




