
#include <QtCore>
#include <QtGui>
#include "view/window.h"

//#define _DEBUG_

#ifdef _DEBUG_

#include "controller/gamefacade.h"
#include "iostream"
#include "string"
using namespace std;

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
    debugConsole();
    #endif

    // TODO zde bude alokace proměnných pro vlastní program (např. hlavní okno programu)
    // ...


    //Vytvori hlavni okno
    Window mainWindow;
    mainWindow.show();

    // Spouštim Qt
    returnValue = app.exec();

    // TODO zde bude dealokace dynamicky alokovanýh proměných
    // ...

    return returnValue;

}
