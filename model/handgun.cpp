
#include "handgun.h"
#include "../controller/game/game.h"
#include "shot.h"
#include "player.h"

void HandGun::shot(void)
{

    double x;
    double y;
    double angle;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot = new Shot(x, y, angle, shotSpeed, owner);

    owner->getParentGame()->addShot(newShot);

}

