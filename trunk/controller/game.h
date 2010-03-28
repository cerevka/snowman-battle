#ifndef GAME_H
#define GAME_H

#include "../model/mapobject.h"
#include "../model/player.h"
#include "../model/shot.h"
#include "../model/weaponpackage.h"
#include <QThread>

class Game : public QThread
{
public:

    /**
     * Vytvoří novou hru
     * @param parent určuje rodičovský objekt
     */
    explicit Game(QObject * const parent = 0);

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

protected:

    /**
     * Hlavní výkonná smyčka hry (detekce kolizí a pohyb objektů)
     */
    virtual void run(void);

private:

    bool gameRun;

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
    static bool colideObjects(MapObject * const first, MapObject * const second);
    static bool colideObjects(MapObject * const object, Shot * const shot);
    static bool colideAlgorythm(const double recX1, const double recY1, const double recX2, const double recY2, const double pointX, const double pointY);

};

#endif // GAME_H
