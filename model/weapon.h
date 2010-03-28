#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>

class Player;

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

};

#endif // WEAPON_H
