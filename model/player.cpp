#include "player.h"
#include "../controller/game.h"
#include "cstdlib"
#include "ctime"
using namespace std;

Player::Player(Game * const parent) :
        MapObject(parent)
{

    spawned = false;
    direction = NORTH;
    moving = false;

}

bool Player::interactPlayer(Player * const player)
{
    return false;
}

bool Player::interactShot(Shot * const shot)
{

    spawned = false;

    // Zabití hráče
    x1 = -1.0;
    y1 = -1.0;
    x2 = -1.0;
    y2 = -1.0;

    // TODO poslat informaci o zabití

    return false;

}

void Player::respawn(void)
{

    int size = 30; // TODO - doplnit skutečnou šířku a výšku hráče v pixelech

    // vygenerování nových souřednic
    do {

        x1 = rand() * time(NULL) * 1000; // TODO - Přidat modulo podle velikosti mapy
        x2 = x1 + size;
        y1 = rand() * time(NULL) * 1000;
        y2 = y1 + size;

    } while(parentGame->colideAllObjects(this)); // provádím generování souřadnic, dokud nanajdu vyhovující místo

    // vygenerování nového směru
    direction = NORTH;//(rand() * time(NULL)) % 4;

    moving = false;
    spawned = true;

    // TODO poslat informaci o spawnutí

}

void Player::tryMove(void)
{

    double stepSize = 0.5; // TODO - doplnit skutečnou velikost kroku

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

bool Player::isSpawned(void) const
{
    return spawned;
}
