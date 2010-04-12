#include "machinegun.h"
#include "../controller/game/game.h"
#include "shot.h"
#include "player.h"

MachineGun::MachineGun(Player * const parent) :
        Weapon(parent)
{

    ammo = 0;
    restShots = 5;

}

void MachineGun::shot(void)
{

    double x;
    double y;
    double angle;
    double speed = 6.0;

    findPointOfCreatingShots(x, y, angle);

    Shot * newShot = new Shot(x, y, angle - 0.05, speed);
    owner->getParentGame()->addShot(newShot);

    // Startuji časovač na další střely
    startTimer(100);
    restShots--;

    ammo--;

    // Pokud došly náboje, tak vyměním zbraň
    if(ammo == 0){
        owner->changeWeapon();
    }

}

void MachineGun::refill(void)
{

    ammo = 5;

}

void MachineGun::timerEvent(QTimerEvent * const event)
{

    // TODO - dořešit cooldown

    // pokud už jsem vystřílel celou dávku nebo se hráč pohnul, tak zruším časovač
    if((restShots == 0) || (owner->isMoving())){

        killTimer(event->timerId());
        restShots = 5;

    } else {

        // vytvoření další střely dávky
        double x;
        double y;
        double angle;
        double speed = 1.2;

        findPointOfCreatingShots(x, y, angle);

        // podle pořadí střely určím odchylku
        if(restShots % 2){
            angle += 0.05;
        } else {
            angle -= 0.05;
        }

        owner->getParentGame()->getBigGameMutex()->lock();

        try {
            Shot * newShot = new Shot(x, y, angle, speed);
            owner->getParentGame()->addShot(newShot);
            restShots--;
        } catch (QString & ex) {
            // Pokud už nelez vytvářet střely, tak vypnu časovač
            killTimer(event->timerId());
            restShots = 5;
        }

        owner->getParentGame()->getBigGameMutex()->unlock();

    }

}
