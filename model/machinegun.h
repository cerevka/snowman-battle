#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "weapon.h"

class GameTimer;

/**
 * Třída reprezentující samopal
 * @author Ota Sandr
 */
class MachineGun : public Weapon
{

    Q_OBJECT

public:

    /**
     * Konstruktor vytvoří danému hráči samopal
     * @param parent hráč, kterému zbraň patří
     */
    inline explicit MachineGun(Player * const parent) :
            Weapon(parent) {    this->ammo = 0;
                                this->restShots = batchOfShots;
                                this->cooldownTimer = NULL; }

    /**
     * Implementace abstraktní metody předka (výstřel zbraně)
     */
    void shot(void);

    /**
     * Implementace abstraktní metody předka (doplnění nábojů)
     */
    inline void refill(void) { this->ammo = this->maxAmmo; }

public slots:

    /**
     * Vystřelí další střelu dávky
     */
    void netxShotOfBatch(void);

private:

    /**
     * Maximální počet nábojů v samopalu
     */
    static int maxAmmo;

    /**
     * Rychlost střely ze samopalu
     */
    static double shotSpeed;

    /**
     * Úhel roztptylu střel
     */
    static double spreadAngle;

    /**
     * Počet střel v dávce
     */
    static int batchOfShots;

    /**
     * Prodleva mezi jednotlivými střelami dávky
     */
    static int cooldownBatchFrames;

    /**
     * Počet nábojů, které se mají v dané dávce ještě vystřelit
     */
    int restShots;

    /**
     * Časovač podlevy mezi jednotlivými střelami dávky
     */
    GameTimer * cooldownTimer;

};

#endif // MACHINEGUN_H
