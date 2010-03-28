#ifndef UNSHOOTABLEBLOCK_H
#define UNSHOOTABLEBLOCK_H

#include "immovable.h"

class UnshootableBlock : public Immovable
{

public:

    explicit UnshootableBlock(Game * const parent = 0);

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
