#include "window.h"

Window::Window()
{

    //Tady se pridavaji dalsi komponenty hlavniho okna


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

}

//Pripoji se ke hre
void Window::joinGame()
{

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




