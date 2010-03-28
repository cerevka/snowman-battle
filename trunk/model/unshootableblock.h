#ifndef UNSHOOTABLEBLOCK_H
#define UNSHOOTABLEBLOCK_H

#include "mapobject.h"

class UnshootableBlock : public MapObject
{

public:

    UnshootableBlock(Game * const parent, const double x1, const double y1, const double x2, const double y2);

    /**
     * Implementace abstraktní metody předka
     * @param player zde nevyužit
     * @return vrací false (překážku nelze přejít)
     */
    bool interactPlayer(Player * const player);

    /**
     * Implementace abstraktní metody předka
     * @param shot zde nevyužit
     * @return vrací false (překážka není přestřelitelná)
     */
    bool interactShot(Shot * const shot);

};

#endif // UNSHOOTABLEBLOCK_H
