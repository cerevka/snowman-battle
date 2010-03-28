#include "weapon.h"

Weapon::Weapon(Player * const parent) :
    QObject((QObject *)parent)
{
    ammo = 1;
    owner = parent;
}

int Weapon::getAmmo(void) const
{
    return ammo;
}

