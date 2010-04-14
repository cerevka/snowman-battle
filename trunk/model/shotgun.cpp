#include "shotgun.h"
#include "../controller/game/game.h"
#include "shot.h"
#include "player.h"

ShotGun::ShotGun(Player * const parent) :
        Weapon(parent)
{

    ammo = 0;

}

void ShotGun::shot(void)
{

    double x;
    double y;
    double angle;

    double speed = 14.0;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot;

    newShot = new Shot(x, y, angle - 0.2, speed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle - 0.1, speed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle, speed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle + 0.1, speed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle + 0.2, speed, owner);
    owner->getParentGame()->addShot(newShot);

    ammo--;

    if(ammo == 0){
        owner->changeWeapon();
    }

}

void ShotGun::refill(void)
{

    ammo = 4;

}
