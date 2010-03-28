#include "shotgun.h"

ShotGun::ShotGun(Player * const parent) :
        Weapon(parent)
{

    this->refill();

}

void ShotGun::shot(void)
{

    // TODO - doplnit výstřel zbraně

    ammo--;

}

void ShotGun::refill(void)
{

    ammo = 4;

}
