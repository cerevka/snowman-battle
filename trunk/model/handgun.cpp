#include "handgun.h"
#include "../controller/game/game.h"
#include "shot.h"

HandGun::HandGun(Player * const parent) :
        Weapon(parent)
{
    this->refill();
}

void HandGun::shot(void)
{

    double x;
    double y;
    double angle;

    double speed = 5.0;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot = new Shot(x, y, angle, speed);

    owner->getParentGame()->addShot(newShot);

}

void HandGun::refill(void)
{

    ammo = 1;

}
