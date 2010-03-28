#ifndef WEAPONPACKAGE_H
#define WEAPONPACKAGE_H

#include "immovable.h"

enum WeaponType
{
    HANDGUN, SHOTGUN, MACHINEGUN
};

class WeaponPackage : public Immovable
{

public:

    explicit WeaponPackage(Game * const parent = 0);

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

    WeaponType type;

};

#endif // WEAPONPACKAGE_H
