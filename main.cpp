


#include <QtCore>
#include <QtGui>
#include "view/window.h"
//#include "controller/network/server.h"
#include "controller/network/packetparser.h"
#include "controller/game/gamefacade.h"
#include "globals.h"

#ifdef _DEBUG_

#include "iostream"
#include "string"
using namespace std;

/**
 * Jednoduchá funkce používaná pro debugování, příjmá příkazy z konzole a předává je hře
 */
void debugConsole(void)
{

    bool run = true;
    string input;

    GameFacade * const facade = new GameFacade();
    facade->newGame(2);

    do{

        cout << "debug command >> " << endl;
        cin >> input;

        if(!strcmp(input.c_str(), "moveN")){
            facade->startMoveNorth(0);
        } else if (!strcmp(input.c_str(), "moveS")){
            facade->startMoveSouth(0);
        } else if (!strcmp(input.c_str(), "moveE")){
            facade->startMoveEast(0);
        } else if (!strcmp(input.c_str(), "moveW")){
            facade->startMoveWest(0);
        } else if(!strcmp(input.c_str(), "stop")){
            facade->stopMove(0);
        } else if(!strcmp(input.c_str(), "shot")){
            facade->shot(0);
        } else if(!strcmp(input.c_str(), "change")){
            facade->changeWeapon(0);
        } else {
            cout << "Exiting debug console" << endl;
            run = false;
        }

    } while (run);

}



#endif



void connectAll(void)
{

    QObject::connect(packetParser, SIGNAL(norhtKeyPressed(int)), gameFacade, SLOT(startMoveNorth(int)));
    QObject::connect(packetParser, SIGNAL(westKeyPressed(int)), gameFacade, SLOT(startMoveWest(int)));
    QObject::connect(packetParser, SIGNAL(southKeyPressed(int)), gameFacade, SLOT(startMoveSouth(int)));
    QObject::connect(packetParser, SIGNAL(eastKeyPressed(int)), gameFacade, SLOT(startMoveEast(int)));
    QObject::connect(packetParser, SIGNAL(shotKeyPressed(int)), gameFacade, SLOT(shot(int)));
    QObject::connect(packetParser, SIGNAL(changeKeyPressed(int)), gameFacade, SLOT(changeWeapon(int)));
    QObject::connect(packetParser, SIGNAL(moveKeyReleased(int)), gameFacade, SLOT(stopMove(int)));



}


/**
 * Funkce main = vstupní bod programu
 * @param argc počet parametrů příkazové řádky (předává se pro Qt)
 * @param argv pole parametrů příkazové řádky (předává se pro Qt)
 * @return navratová hodnota programu
 */
int main(int argc, char * argv[])
{

    int returnValue = 0;

    // Inicializace Qt
    QApplication app(argc, argv);

    // Inicializace českého překladu
    QTranslator translator;
    translator.load("snowman-battle_cs.qm");
    app.installTranslator(&translator);

    #ifdef _DEBUG_
//    debugConsole();
    #endif

    // TODO zde bude alokace proměnných pro vlastní program (např. hlavní okno programu)
    // ...

    //Vytvori hlavni okno
    mainWindow = new Window();
    mainWindow->show();

    packetParser = new PacketParser();
    gameFacade = new GameFacade();

    // Spojím sokety a sloty
    connectAll();

    // Spouštim Qt
    returnValue = app.exec();

    // TODO zde bude dealokace dynamicky alokovanýh proměných
    // ...

    delete mainWindow;
    delete packetParser;
    delete gameFacade;

    return returnValue;

}
