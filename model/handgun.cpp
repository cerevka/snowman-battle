#include "handgun.h"

HandGun::HandGun(Player * const parent) :
        Weapon(parent)
{
    this->refill();
}

void HandGun::shot(void)
{

    // TODO - doplnit výstřel pistole

}

void HandGun::refill(void)
{

    ammo = 1;

}
