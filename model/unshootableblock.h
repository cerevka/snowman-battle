#ifndef UNSHOOTABLEBLOCK_H
#define UNSHOOTABLEBLOCK_H

#include "mapobject.h"

/**
 * Tato třída reprezentuje překážky, přes které nelze střelit (např. skála)
 */
class UnshootableBlock : public MapObject
{

public:

    /**
     * Vytvoří přestřelitelnou překážku na zadaných souřadnicích
     * @param parent hra v rámci níž je tato překážka vytvořena
     * @param x1 x-ová souřadnice levého horního rohu překážky
     * @param y1 y-ová souřadnice levého horního rohu překážky
     * @param x2 x-ová souřadnice pravého dolního rohu překážky
     * @param y2 y-ová souřadnice pravého dolního rohu překážky
     */
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
