#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "weapon.h"

/**
 * Třída reprezentující samopal
 */
class MachineGun : public Weapon
{

public:

    explicit MachineGun(Player * const parent);

    void shot(void);

    void refill(void);

    /**
     * Tato metoda slouží k tomu, aby ze samopalu správně vystřelily další střely
     * @param event časovač, který spustil tuto metodu
     */
    void timerEvent (QTimerEvent * const event);

private:

    int restShots;

};

#endif // MACHINEGUN_H
