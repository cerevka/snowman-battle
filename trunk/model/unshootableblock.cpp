#include "unshootableblock.h"

UnshootableBlock::UnshootableBlock(Game * const parent) :
        Immovable(parent)
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
