#include "shootableblock.h"

ShootableBlock::ShootableBlock(Game * const parent, const double x1, const double y1, const double x2, const double y2) :
        MapObject(parent, x1, y1, x2, y2)
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
