#ifndef GAME_H
#define GAME_H

#include "../model/mapobject.h"
#include "../model/player.h"
#include "../model/shot.h"
#include "../model/weaponpackage.h"
#include "../model/unshootableblock.h"
#include <QThread>
#include <QMutex>

#define _DEBUG_

#ifdef _DEBUG_

#include "iostream"
using namespace std;

#endif

class GameFacade;

/**
 * Třída reprezentující hru samotnou, je to vlákno které obsluhuje pohyb objektů a kolizí mezi nimi
 */
class Game : public QThread
{
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
     * Pomocná metoda, která zjistí jestli zadaný objekt koliduje s kterýmkoli jiným na herní ploše
     * @param object objekt, se kterým se mají počítat kolize
     * @return true, pokud koliduje s některým jiným objektem
     */
    bool colideAllObjects(MapObject * const object) const;

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


    QMutex * getBigGameMutex(void) const;

protected:

    /**
     * Hlavní výkonná smyčka hry (detekce kolizí a pohyb objektů)
     */
    virtual void run(void);

private:

    /**
     * Pokud je true, tak hlavní smyčka hry běží
     */
    bool gameRun;

    /**
     * Mutex uzamykající vykonou část hlavní smyčky
     */
    QMutex * bigGameMutex;

    /**
     * Tyto seznamy v sobě drží všechny objekty hry
     */
    QList<MapObject *> * allObjects;
    QList<Player *> * allPlayers;
    QList<Shot *> * allShots;

    /**
     * Pomocné metody používané hlavní smyčkou
     */
    void movePlayers(void);
    void moveShots(void);

    /**
     * Pomocné metody, které se používají k detekci kolizí
     */
    static bool colideObjects(MapObject * const one, MapObject * const two);
    static bool colideRectangles(MapObject * const first, MapObject * const second);
    static bool colideShots(MapObject * const object, Shot * const shot);
    static bool colideAlgorythm(const double recX1, const double recY1, const double recX2, const double recY2, const double pointX, const double pointY);

    friend class GameFacade;
};

#endif // GAME_H
