#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "weapon.h"

/**
 * Třída reprezentující samopal
 */
class MachineGun : public Weapon
{

public:

    /**
     * Konstruktor vytvoří danému hráči samopal
     * @param parent hráč, kterému zbraň patří
     */
    explicit MachineGun(Player * const parent);

    /**
     * Implementace abstraktní metody předka (výstřel zbraně)
     */
    void shot(void);

    /**
     * Implementace abstraktní metody předka (doplnění nábojů)
     */
    void refill(void);

    /**
     * Tato metoda slouží k tomu, aby ze samopalu správně vystřelily další střely
     * @param event časovač, který spustil tuto metodu
     */
    void timerEvent (QTimerEvent * const event);

private:

    /**
     * Počet nábojů, které se mají v dané dávce ještě vystřelit
     */
    int restShots;

};

#endif // MACHINEGUN_H
