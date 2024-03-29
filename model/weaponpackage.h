#ifndef WEAPONPACKAGE_H
#define WEAPONPACKAGE_H

#include "mapobject.h"

class QBitArray;

/**
 * Výčtový typ pro druh ležící zbraně
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

    Q_OBJECT

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
    inline bool interactShot(Shot * const) { return true; }

    /**
     * Getr pro id zbraně
     * @return id zbraně
     */
    inline int getWeaponPackageID(void) const { return this->weaponPackageID; }

    /**
     * Getr pro typ zbraně
     * @return typ zbraně
     */
    inline WeaponType getType(void) const { return this->type; }

protected:

    /**
     * Šířka zbraně v pixelech
     */
    static double weaponPackageSizeX;

    /**
     * Výška zbraně v pixelech
     */
    static double weaponPackageSizeY;

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
