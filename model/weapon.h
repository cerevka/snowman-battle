#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>

class Player;

/**
 * Třída reprezentující zbraň, kterou nese hráč
 */
class Weapon : public QObject
{

    Q_OBJECT

public:

    /**
     * Konstruktor vytvoří zbraň, která drží zadaný hrač
     * @param parent hráč, který má tuto zbraň
     */
    explicit Weapon(Player * const parent);

    /**
     * Tato metoda "naprosto nečekaně" provede to, že daná zbraň vystřelí
     */
    virtual void shot(void) = 0;

    /**
     * Tato metoda doplní zbrani její náboje na plný počet
     */
    virtual void refill(void) = 0;

    /**
     * Getr pro počet zbývajících nábojů
     * @return zbývající počet nábojů
     */
    int getAmmo(void) const;

protected:

    /**
     * Počet zbývajících nábojů ve zbrani
     */
    int ammo;

    /**
     * Hráč, který má tuto zbraň
     */
    Player * owner;

    /**
     * Pomocná metoda, která na základě parametrů hráče, zjistí, ve kterém bodu se objeví střela(y)
     * @param x na místo, kam ukazuje tento ukazatel, se zapíše x-ové souřadnice bodu
     * @param y na místo, kam ukazuje tento ukazatel, se zapíše y-ové souřadnice bodu
     * @param angle na místo, kam ukazuje tento ukazatel, se zapíše úhel, pod kterým bude střela leťet
     */
    void findPointOfCreatingShots(double & x, double & y, double & angle);

};

#endif // WEAPON_H
