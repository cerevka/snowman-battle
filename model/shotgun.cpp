
#include "shotgun.h"
#include "../controller/game/game.h"
#include "shot.h"
#include "player.h"

void ShotGun::shot(void)
{

    double x;
    double y;
    double angle;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot;

    newShot = new Shot(x, y, angle - 2*spreadAngle, shotSpeed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle - spreadAngle, shotSpeed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle, shotSpeed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle + spreadAngle, shotSpeed, owner);
    owner->getParentGame()->addShot(newShot);

    newShot = new Shot(x, y, angle + 2*spreadAngle, shotSpeed, owner);
    owner->getParentGame()->addShot(newShot);

    ammo--;

    if(ammo == 0){
        owner->changeWeapon();
    }

}
