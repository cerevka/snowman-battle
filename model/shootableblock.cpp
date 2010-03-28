#include "shootableblock.h"

ShootableBlock::ShootableBlock(Game * const parent) :
        Immovable(parent)
{
}

bool ShootableBlock::interactPlayer(Player * const player)
{
    return false;
}

bool ShootableBlock::interactShot(Shot * const shot)
{
    return true;
}
