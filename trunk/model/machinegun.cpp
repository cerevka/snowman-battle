
#include "machinegun.h"
#include "../controller/game/game.h"
#include "shot.h"
#include "player.h"

void MachineGun::shot(void)
{

    double x;
    double y;
    double angle;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot = new Shot(x, y, angle - spreadAngle, shotSpeed, owner);
    owner->getParentGame()->addShot(newShot);

    // Startuji časovač na další střely
    cooldownTimer = new GameTimer(cooldownBatchFrames, this);
    connect(cooldownTimer, SIGNAL(timeout()), this, SLOT(netxShotOfBatch()));
    owner->getParentGame()->addTimer(cooldownTimer);
    restShots--;

    ammo--;

    // Pokud došly náboje, tak vyměním zbraň
    if(ammo == 0){
        owner->changeWeapon();
    }

}

void MachineGun::netxShotOfBatch(void)
{

    owner->getParentGame()->removeTimer(cooldownTimer);
    delete cooldownTimer;

    // pokud už jsem vystřílel celou dávku nebo se hráč pohnul, tak zruším časovač
    if((restShots == 0) || (owner->isMoving())){

        restShots = batchOfShots;

    } else {

        // vytvoření další střely dávky
        double x;
        double y;
        double angle;

        findPointOfCreatingShots(x, y, angle);

        // podle pořadí střely určím odchylku
        if(restShots % 2){
            angle -= spreadAngle;
        } else {
            angle += spreadAngle;
        }

        try {
            Shot * newShot = new Shot(x, y, angle, shotSpeed, owner);
            owner->getParentGame()->addShot(newShot);

            // časovač další střely z dávky
            cooldownTimer = new GameTimer(cooldownBatchFrames, this);
            connect(cooldownTimer, SIGNAL(timeout()), this, SLOT(netxShotOfBatch()));
            owner->getParentGame()->addTimer(cooldownTimer);
            restShots--;

        } catch (QString & ex) {

            restShots = batchOfShots;
        }

    }

}
