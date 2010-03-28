#ifndef WEAPONPACKAGE_H
#define WEAPONPACKAGE_H

#include "mapobject.h"

/**
 * Výčtvový typ pro druh ležící zbraně
 */
enum WeaponType
{
    HANDGUN, SHOTGUN, MACHINEGUN
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
    explicit WeaponPackage(Game * const parent);

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

    WeaponType getType(void) const;

protected:

    /**
     * Typ zbraně
     */
    WeaponType type;

};

#endif // WEAPONPACKAGE_H
