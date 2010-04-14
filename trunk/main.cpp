
#include <QtCore>
#include <QtGui>

#include "globals.h"
#include "cstdlib"

Window * Globals::mainWindow = NULL;
Network * Globals::network = NULL;
PacketParser * Globals::packetParser = NULL;
PacketCreator * Globals::packetCreator = NULL;
GameFacade * Globals::gameFacade = NULL;
bool Globals::isGameRunning = false;
int Globals::players = 0;

class ScenePanel;

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

/**
 * Pomocná funkce, pro připojení slotů a signálů
 */
void connectAll(void)
{

    QObject::connect(Globals::packetParser, SIGNAL(norhtKeyPressed(int)), Globals::gameFacade, SLOT(startMoveNorth(int)));
    QObject::connect(Globals::packetParser, SIGNAL(westKeyPressed(int)), Globals::gameFacade, SLOT(startMoveWest(int)));
    QObject::connect(Globals::packetParser, SIGNAL(southKeyPressed(int)), Globals::gameFacade, SLOT(startMoveSouth(int)));
    QObject::connect(Globals::packetParser, SIGNAL(eastKeyPressed(int)), Globals::gameFacade, SLOT(startMoveEast(int)));
    QObject::connect(Globals::packetParser, SIGNAL(shotKeyPressed(int)), Globals::gameFacade, SLOT(shot(int)));
    QObject::connect(Globals::packetParser, SIGNAL(changeKeyPressed(int)), Globals::gameFacade, SLOT(changeWeapon(int)));
    QObject::connect(Globals::packetParser, SIGNAL(moveKeyReleased(int)), Globals::gameFacade, SLOT(stopMove(int)));

    ScenePanel * panel = Globals::mainWindow->getScenePanel();

    QObject::connect(Globals::packetParser, SIGNAL(playerSpawned(int,int,int,int)), panel, SLOT(addNewPlayer(int,int,int,int)));
    QObject::connect(Globals::packetParser, SIGNAL(weaponPackSpawned(int,int,int,int)), panel, SLOT(addNewGun(int,int,int,int)));
    QObject::connect(Globals::packetParser, SIGNAL(playerKilled(int)), panel, SLOT(hidePlayer(int)));
    QObject::connect(Globals::packetParser, SIGNAL(weaponPackDespawned(int)), panel, SLOT(removeGun(int)));
    QObject::connect(Globals::packetParser, SIGNAL(weaponChanged(int,int,int)), panel, SLOT(changeGun(int,int, int)));
    QObject::connect(Globals::packetParser, SIGNAL(shotCreated(int,int,int)), panel, SLOT(addNewShot(int,int,int)));
    QObject::connect(Globals::packetParser, SIGNAL(playerMoved(int,int,int)), panel, SLOT(changePlayerPosition(int,int,int)));
    QObject::connect(Globals::packetParser, SIGNAL(shotMoved(int,int,int)), panel, SLOT(changeShotPosition(int,int,int)));
    QObject::connect(Globals::packetParser, SIGNAL(shotDestroyed(int)), panel, SLOT(removeShot(int)));
    QObject::connect(Globals::packetParser, SIGNAL(playerDeactivated(int)), panel, SLOT(playerDeactivated(int)));
    QObject::connect(Globals::packetParser, SIGNAL(playerActivated(int)), panel, SLOT(appearePlayer(int)));

    ChatPanel * chatpanel = Globals::mainWindow->getChatPanel();
    QObject::connect(Globals::packetParser, SIGNAL(chatMessageRecieved(int,QString*)), chatpanel, SLOT(newMessage(int,QString*)));

    StatusBar * statusbar = Globals::mainWindow->getStatusBar();
    QObject::connect(Globals::packetParser, SIGNAL(playersScoreIncremented(int)), statusbar, SLOT(changeScore(int)));
//    QObject::connect(panel, SIGNAL(changeAmmo(int,int)), statusbar, SLOT(changeRound(int,int)));

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

    Globals::packetParser = new PacketParser();
    Globals::packetCreator = new PacketCreator();
    Globals::gameFacade = new GameFacade();

    //Vytvori hlavni okno
    Globals::mainWindow = new Window();
    Globals::mainWindow->show();

    // Spojím sokety a sloty
    connectAll();

    // Spouštim Qt
    returnValue = app.exec();

    // TODO zde bude dealokace dynamicky alokovanýh proměných
    // ...

    delete Globals::mainWindow;
    delete Globals::packetParser;
    delete Globals::packetCreator;
    delete Globals::gameFacade;

    return returnValue;

}
