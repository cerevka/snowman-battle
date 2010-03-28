#include "weaponpackage.h"

WeaponPackage::WeaponPackage(Game * const parent) :
        Immovable(parent)
{
}

bool WeaponPackage::interactPlayer(Player * const player)
{
    // TODO - doplnit kód pro zvednutí zbraně
    return true;
}

bool WeaponPackage::interactShot(Shot * const shot)
{
    return true;
}

WeaponType WeaponPackage::getType(void) const
{
    return type;
}
