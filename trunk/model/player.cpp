#include "player.h"

Player::Player(QObject * parent) :
        MapObject(parent)
{
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
