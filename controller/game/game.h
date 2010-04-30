#ifndef GAME_H
#define GAME_H

#include <QThread>

#include "gametimer.h"

class MapObject;
class Player;
class Shot;
class WeaponPackage;
class GameFacade;
//class GameTimer;
class QMutex;
class QWaitCondition;

/**
 * Třída reprezentující hru samotnou, je to vlákno, které obsluhuje pohyb objektů a kolizí mezi nimi
 * @author Ota Sandr
 */
class Game : public QThread
{

    Q_OBJECT

public:

    /**
     * Vytvoří novou hru o zadaném počtu hráčů a se zadaným výherním skórem
     * @param countOfPlayers počet hráču, kteří budou hrát hru
     * @param scoreToWin skóre, kterého je potřeba dosáhnout, aby hráč vyhrál
     * @param parent určuje rodičovský objekt
     */
    Game(const int countOfPlayers, const int scoreToWin, QObject * const parent = 0);

    /**
     * Uvolňuje prostředky alokované pro potřeby hry
     */
    virtual ~Game(void);

    /**
     * Ukončí smyčku(vlákno) detekce kolizí
     */
    inline void quitGame(void) { this->gameRun = false; }

    /**
     * Metoda, která slouží pro vyhledání náhodných souřadnic, do kterých může být umísteň objekt
     * @param size velikost daného objektu v pixelech
     * @param object ukazatel na objekt, který se má umístit
     */
    void generateValidCoordinates(const double sizeX, const double sizeY, MapObject * const object);

    /**
     * Přidá střelu do seznamu střel(bude s ní pohybovat)
     * @param shot ukazatel na střelu, která bude do seznamu přidána
     */
    void addShot(Shot * const shot);

    /**
     * Odebere zbraň ze seznamu objektů (poté co jí hráč vezme)
     * @param wPackage zbraň, jenž bude odebrána
     */
    void removeWeaponPackage(WeaponPackage * const wPackage);

    /**
     * Tato metoda se spouští každý frame a provádí deteci kolizí
     * @param event časovač, který spustil tuhle metodu
     */
    void timerEvent (QTimerEvent * const event);

    /**
     * Getr sloužící ke zjištění zde toto má nastavenou řídící proměnou
     * @return true, pokud hra běží
     */
    inline bool isGameRunning(void) const { return this->gameRun; }

    /**
     * Getr pro skóre potřebné na výhru
     * @return vrací, kolik je potřeba pro výhru zabít soupeřů
     */
    inline int getScoreToWin(void) const { return this->scoreToWin; }

    /**
     * Getr pro hlavní mutex
     * @return ukazatel mutex, který slouží pro uzamykání hlavního vlákna
     */
    inline QMutex * getBigGameMutex(void) const { return this->bigGameMutex; }

    /**
     * Tato metoda přidá daný časovač do seznamu časovačů a zajistí jeho aktivovaní za daný časový úsek
     * @param timer časovač, který má být přidán do seznamu
     */
    inline void addTimer(GameTimer * const timer) { this->allTimers.append(timer);
                                                    timer->start(this->time);}

    /**
     * Tato metoda odebere daný časovač ze seznamu časovačů
     * @param timer časovač, který má být odebrán ze seznamu
     */
    inline void removeTimer(GameTimer * const timer) { this->allTimers.removeOne(timer); }

signals:

    /**
     * Signál ukončení herního frame
     */
    void frameEnded(void);

    /***************************************************/

    /**
     * Signál vytvoření střely na herní ploše
     * @param shotID id vytvořené střely
     * @param x x-ová souřadnice střely
     * @param y y-ová souřadnice střely
     */
    void shotCreated(int shotID, int x, int y);

    /**
     * Signál přesunu střely
     * @param shotID id střely, která má změnit umístění
     * @param x nová x-ová souřadnice střely
     * @param y nová y-ová souřadnice střely
     */
    void shotMoved(int shotID, int x, int y);

    /**
     * Signál zničení střely
     * @param shotID id střely, která je zničena
     */
    void shotDestroyed(int shotID);

    /**
     * Signál vytvoření zbraňového balíčku na herní ploše
     * @param wPackID id vytvořené zbraně
     * @param x x-ová souřadnice zbraně
     * @param y y-ová souřadnice zbraně
     * @param type typ vytvořené zbraně
     */
    void wPackCreated(int wPackID, int x, int y, int type);

    /**
     * Signál zmizení zbraňového balíčku z herní plochy
     * @param wPackID id zbraně, která má zmizet
     */
    void wPackRemoved(int wPackID);

    /**
     * Signál přesunu hráče
     * @param playerID id hráče, který má změnit umístění
     * @param x nová x-ová souřadnice hráče
     * @param y nová y-ová souřadnice hráče
     */
    void playerMoved(int playerID, int x, int y);

    /***************************************************/

    /**
     * Signál zapauzování hry
     */
    void gamePaused(void);

    /**
     * Signál pokračování hry
     */
    void gameResumed(void);

protected:

    /**
     * Metoda běhu vlákna, provede nezbytnou inicializaci a spustí smyčku událostí
     */
    virtual void run(void);

private:

    /**
     * Mutex uzamykající výkonou část hlavní smyčky
     */
    QMutex * bigGameMutex;

    /**
     * Tento seznam v sobě drží všechny objekty hry
     */
    QList<MapObject *> * allObjects;

    /**
     * Tento seznam v sobě drží všechny hráče
     */
    QList<Player *> * allPlayers;

    /**
     * Tento seznam v sobě drží všechny letící střely
     */
    QList<Shot *> * allShots;

    /**
     * Tento seznam v sobě drží všechny časovače
     */
    QList<GameTimer *> allTimers;

    /**
     * Tato proměnná roste při každém frame a používá se kvůli pauzování časovačů
     */
    int time;

    /**
     * Skóre, jaké je potřeba k výhře
     */
    int scoreToWin;

    /**
     * Pokud je true, tak hlavní smyčka hry běží
     */
    bool gameRun;

    /**
     * Tato proměnná je true, pokud se má hra zapauzovat
     */
    bool paused;

    /**
     * WaitCondition, pomocí které je realizována pauza hry
     */
    QWaitCondition * pauseCondition;

    /**
     * Počet zbraní, které jsou na ploše
     */
    int countOfWeapons;

    /**
     * Pomocná metoda, která zjistí jestli zadaný objekt koliduje s kterýmkoli jiným na herní ploše
     * @param object objekt, se kterým se mají počítat kolize
     * @return true, pokud koliduje s některým jiným objektem
     */
    bool colideAllObjects(MapObject * const object) const;

    /***************************************************/

    /* Pomocné metody používané hlavní smyčkou */

    /**
     * Tato metoda projede seznam hráčů a zkusí s nimi pohnout a detekuje kolize
     */
    void movePlayers(void);

    /**
     * Tato metoda projede seznam letících střel, pohne s nimi a spočítá kolize
     */
    void moveShots(void);

    /**
     * Tato metoda slouží pro generování zbraní ležících na ploše
     */
    void generateWeaponPackages(void);

    /***************************************************/

    /* Pomocné metody, které se používají k detekci kolizí */

    /**
     * Tato metoda zjistí, jestli se 2 objekty navzájem překrývájí (jakýmkoliv způsobem)
     * @param first první objekt
     * @param second druhý objekt
     * @return vrací true, pokud se objekty překrývají
     */
    static bool colideObjects(MapObject * const one, MapObject * const two);

    /**
     * Metoda, která zjistí, zdali první obdélníkový objekt leží vodorovně přes druhý (tvoří jakoby kříž)
     * @param first první obdélníkový objekt
     * @param second druhý obdélníkový objekt
     * @return vrací true, pokud první objekt leží vodorovně přes druhý
     */
    static bool colideOverlap(MapObject * const first, MapObject * const second);

    /**
     * Metoda zjištující jestli některý z vrcholů druhého objektu leží uvnitř prvního objektu
     * @param first první obdélníkový objekt
     * @param second druhý obdélníkový objekt
     * @return true pokud je jakýkoliv z vrcholů druhého objektu leží uvnitř prvního objektu
     */
    static bool colideRectangles(MapObject * const first, MapObject * const second);

    /**
     * Metoda, která zjistí, jestli střela vnikla do daného objektu
     * @param object obdélníkový objekt
     * @param shot střela, u které se zjišťuje, zda vnikla do objektu
     * @return vrací true, pokud střela vnikla do objektu
     */
    static bool colideShots(MapObject * const object, Shot * const shot);

    /**
     * Metoda zjišťující jestli zadaný bod leží uvnitř obdélníka
     * @param recX1 x-ová souřadnice levého horního rohu odbélníka
     * @param recY1 y-ová souřadnice levého horního rohu odbélníka
     * @param recX2 x-ová souřadnice pravého spodního rohu odbélníka
     * @param recY2 y-ová souřadnice pravého spodního rohu odbélníka
     * @param pointX x-ová souřadnice bodu
     * @param pointY y-ová souřadnice bodu
     * @return
     */
    static bool colideAlgorythm(const double recX1, const double recY1, const double recX2, const double recY2, const double pointX, const double pointY);

    friend class GameFacade;
};

#endif // GAME_H
