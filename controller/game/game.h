#ifndef GAME_H
#define GAME_H

#include "../../model/mapobject.h"
#include "../../model/player.h"
#include "../../model/shot.h"
#include "../../model/weaponpackage.h"
#include "../../model/shootableblock.h"
#include "../../model/unshootableblock.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QApplication>
#include <QTime>

#ifdef _DEBUG_

#include <QtDebug>

#endif

class GameFacade;

/**
 * Třída reprezentující hru samotnou, je to vlákno které obsluhuje pohyb objektů a kolizí mezi nimi
 */
class Game : public QThread
{

    Q_OBJECT

public:

    /**
     * Vytvoří novou hru
     * @param countOfPlayers počet hráču, kteří budou hrát hru
     * @param parent určuje rodičovský objekt
     */
    explicit Game(const int countOfPlayers, QObject * const parent = 0);

    /**
     * Uvolňuje prostředky alokované pro potřeby hry
     */
    virtual ~Game(void);

    /**
     * Ukončí smyčku(vlákno) detekce kolizí
     */
    void quitGame(void);

    /**
     * Metoda, která slouží pro vyhledání náhodných souřadnic, do kterých může být umísteň objekt
     * @param size velikost daného objektu v pixelech
     * @param object ukazatel na objekt, který se má umístit
     */
    void generateValidCoordinates(const double size, MapObject * const object);

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
     * Tato metoda se spouští každý frame a rpovádí deteci kolizí
     * @param event časovač, který spustil tuhle metodu
     */
    void timerEvent (QTimerEvent * const event);

    /**
     * Getr pro hlavní mutex
     * @return ukazatel mutex, který slouží pro uzamykání hlavního vlákna
     */
    QMutex * getBigGameMutex(void) const;

protected:

    /**
     * Metoda běhu vlákna, provede nezbytnou inicializaci a spustí smyčku událostí
     */
    virtual void run(void);

private:

    /**
     * Mutex uzamykající vykonou část hlavní smyčky
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

    static bool colideObjects(MapObject * const one, MapObject * const two);
    static bool colideRectangles(MapObject * const first, MapObject * const second);
    static bool colideShots(MapObject * const object, Shot * const shot);
    static bool colideAlgorythm(const double recX1, const double recY1, const double recX2, const double recY2, const double pointX, const double pointY);

    friend class GameFacade;
};

#endif // GAME_H
