#ifndef WEAPONPACKAGE_H
#define WEAPONPACKAGE_H

#include "mapobject.h"
#include "QBitArray"

/**
 * Výčtvový typ pro druh ležící zbraně
 */
enum WeaponType
{
    HANDGUN, MACHINEGUN, SHOTGUN
};

/**
 * Tato třída reprezentuje zbraň, která leží na hrací ploše a může být zvednuta hráčem
 */
class WeaponPackage : public MapObject
{

public:

    /**
     * Konstruktor vytvoří náhodnou zbraň na herní ploše (brokovnici nebo samopal)
     * @param parent hra, v rámci níž je zbraň vytvořena
     */
    explicit WeaponPackage(Game * const parent = 0);

    /**
     * Destruktor zajišťuje, aby mohlo být znovu použité ID této zbraně
     */
    ~WeaponPackage(void);

    /**
     * Implementace abstraktní metody předka
     * @param player hráč, který dostane tuto zbraň
     * @return vrací true (přes ležící zbraň lze přejít)
     */
    bool interactPlayer(Player * const player);

    /**
     * Implementace abstraktní metody předka
     * @param shot zde nevyužit
     * @return vrací true (ležící zbraň je přestřelitelná)
     */
    bool interactShot(Shot * const shot);

    /**
     * Getr pro id zbraně
     */
    int getWeaponPackageID(void) const;

    /**
     * Getr pro typ zbraně
     */
    WeaponType getType(void) const;

protected:

    /**
     * Velikost zbraně v pixelech
     */
    static double weaponPackageSize;

    /**
     * Toto pole udržuje záznamy o tom, která ID jsou pro zbraně použity
     */
    static QBitArray idArray;

    /**
     * Jednoznačné ID zbraně
     */
    int weaponPackageID;

    /**
     * Typ zbraně
     */
    WeaponType type;

};

#endif // WEAPONPACKAGE_H
