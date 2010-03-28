#include "unshootableblock.h"

UnshootableBlock::UnshootableBlock(Game * const parent, const double x1, const double y1, const double x2, const double y2) :
        MapObject(parent, x1, y1, x2, y2)
{
}

bool UnshootableBlock::interactPlayer(Player * const player)
{
    return false;
}

bool UnshootableBlock::interactShot(Shot * const shot)
{
    return false;
}
