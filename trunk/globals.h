
#ifndef GLOBALS_H
#define GLOBALS_H

#include "cstdlib"

class Window;
class Network;
class PacketParser;
class PacketCreator;
class GameFacade;

#include <QObject>

#include "view/window.h"
#include "controller/network/network.h"
#include "controller/network/packetparser.h"
#include "controller/network/packetcreator.h"
#include "controller/game/gamefacade.h"


/**
 * Speciální třída, který v sobě udržuje ukazatele instance všech singletonových tříd
 */
class Globals : public QObject
{

    Q_OBJECT

public:

    explicit Globals(QObject * const parent = 0) :
            QObject(parent) {};

    /**
     * Instance hlavního okna
     */
    static Window * mainWindow;

    /**
     * Instance síťového rozhraní
     */
    static Network * network;

    /**
     * Parser na pakety
     */
    static PacketParser * packetParser;

    /**
     * Vytvářeč paketů
     */
    static PacketCreator * packetCreator;

    /**
     * Instance herní fasády
     */
    static GameFacade * gameFacade;

};


#endif // GLOBALS_H
