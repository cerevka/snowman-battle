#include "shotgun.h"
#include "../controller/game/game.h"
#include "shot.h"
#include "player.h"

ShotGun::ShotGun(Player * const parent) :
        Weapon(parent)
{

    ammo = 3;

}

void ShotGun::shot(void)
{

    double x;
    double y;
    double angle;

    double speed = 1.5;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot;

    newShot = new Shot(owner, x, y, angle - 0.2, speed);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(owner, x, y, angle - 0.1, speed);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(owner, x, y, angle, speed);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(owner, x, y, angle + 0.1, speed);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(owner, x, y, angle + 0.2, speed);
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
