#ifndef GLOBALS_H
#define GLOBALS_H

// Speciální hlavičkový soubor, který v sobě udržuje ukazatele instance všech singletonových tříd

class Window;
class Server;
class Client;
class PacketParser;
class GameFacade;

/**
 * Instance hlavního okna
 */
Window * mainWindow;

// TODO tady možná místo Server a Client dáme NetworkInterface

/**
 * Instance serveru
 */
Server * server;

/**
 * Instance klienta
 */
Client * client;

/**
 * Parser na pakety
 */
PacketParser * packetParser;

/**
 * Instance herní fasády
 */
GameFacade * gameFacade;

#endif // GLOBALS_H
