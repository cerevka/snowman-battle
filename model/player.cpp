#include "player.h"
#include "../controller/game/game.h"
#include "handgun.h"
#include "machinegun.h"
#include "shotgun.h"

double Player::playerSize = 30.0; // TODO - doplnit skutečnou šířku a výšku hráče v pixelech
double Player::stepSize = 0.5; // TODO - doplnit skutečnou velikost kroku

Player::Player(Game * const parent, const int id) :
        MapObject(parent)
{

    playerID = id;
    spawned = false;
    direction = NORTH;
    moving = false;
    shoting = false;

    // Vytvoření inventáře se zbraněmi
    inventory[0] = new HandGun(this);
    inventory[1] = new MachineGun(this);
    inventory[2] = new ShotGun(this);
    actualWeapon = 0;

}

bool Player::interactPlayer(Player * const player)
{
    return false;
}

bool Player::interactShot(Shot * const shot)
{

    spawned = false;

    // Zabití hráče
    x1 = -100.0;
    y1 = -100.0;
    x2 = -100.0;
    y2 = -100.0;

    // TODO poslat informaci o zabití
    #ifdef _DEBUG_
    qDebug() << "Game engine: Player" << playerID << "killed";
    #endif

    // startuji časovač pro respawnutí
    startTimer(5000);

    return false;

}

void Player::respawn(void)
{

    // Vygenerování nových souřednic
    parentGame->generateValidCoordinates(playerSize, this);

    // Vygenerování nového směru
    direction = (Directions)(qrand() % 4);

    // Resetování příznaků
    moving = false;
    shoting = false;
    spawned = true;

    // TODO poslat informaci o spawnutí
    #ifdef _DEBUG_
    qDebug() << "Game engine: Player" << playerID << "spawned at (" << x1 << "," << y1 << "),(" << x2 << "," << y2 << "); direction:" << direction;
    #endif

}

void Player::tryMove(void)
{

    int modificatorX = 0;
    int modificatorY = 0;

    // Zálohuji souřadnice
    x1Backup = x1;
    x2Backup = x2;
    y1Backup = y1;
    y2Backup = y2;

    // Směru nastavim modifikátory, aby se provedl správně výpočet
    switch (direction)
    {
    case NORTH:
        {
            modificatorY = -1;
            break;
        }
    case WEST:
        {
            modificatorX = -1;
            break;
        }
    case SOUTH:
        {
            modificatorY = 1;
            break;
        }
    case EAST:
        {
            modificatorX = 1;
            break;
        }
    }

    // Vlastní změna souřadnic
    x1 = x1 + (modificatorX * stepSize);
    x2 = x2 + (modificatorX * stepSize);
    y1 = y1 + (modificatorY * stepSize);
    y2 = y2 + (modificatorY * stepSize);

}

void Player::backMove(void)
{

    x1 = x1Backup;
    x2 = x2Backup;
    y1 = y1Backup;
    y2 = y2Backup;

}

void Player::shot(void)
{

    shoting = false;

    // Výjimka nastane, pokud je více než 256 střel
    try{
        inventory[actualWeapon]->shot();
    } catch (QString & ex){
        // Tato výjimka se ignoruje (střely navíc se prostě nevytvoří)
    }

}

void Player::changeWeapon(void)
{

    // Hledám v inventáři zbraň, která nemá nula zbývajících nábojů
    do {
        actualWeapon = (actualWeapon + 1) % 3;
    } while(inventory[actualWeapon]->getAmmo() == 0);

    // TODO - poslat signál o změně zbraně
    #ifdef _DEBUG_
    qDebug() << "Game engine: Player" << playerID << "equiped weapon" << actualWeapon;
    #endif

}

void Player::timerEvent(QTimerEvent * const event)
{
    killTimer(event->timerId());
    parentGame->getBigGameMutex()->lock();
    respawn();
    parentGame->getBigGameMutex()->unlock();

}

void Player::setActualWeapon(const int actualWeapon)
{

    this->actualWeapon = actualWeapon;

    // TODO - poslat signál o změně zbraně
    #ifdef _DEBUG_
    qDebug() << "Game engine: Player" << playerID << "equiped weapon" << actualWeapon;
    #endif

}

int Player::getID(void) const
{
    return playerID;
}

void Player::setDirection(const Directions direction)
{
    this->direction = direction;
}

Directions Player::getDirection(void) const
{
    return direction;
}

void Player::setMoving(const bool moving)
{
    this->moving = moving;
}

bool Player::isMoving(void) const
{
    return moving;
}

void Player::setShoting(const bool shoting)
{
    this->shoting = shoting;
}

bool Player::isShoting(void) const
{
    return shoting;
}

bool Player::isSpawned(void) const
{
    return spawned;
}

Weapon * const * Player::getInventory(void) const
{
    return inventory;
}

Game * Player::getParentGame(void) const
{
    return parentGame;
}
