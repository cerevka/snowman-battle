#ifndef SHOT_H
#define SHOT_H

#include <QObject>
#include <QBitArray>

#include "player.h"

/**
 * Třída reprezentující střelu letící na hrací ploše
 */
class Shot : public QObject
{

    Q_OBJECT

public:

    /**
     * Konstruktor vytvoří střelu se zadanými parametry
     * @param parent ukazatel na hráče, který tuto střelu vytřelil
     * @param x x-ová souřadnice střely
     * @param y y-ová souřadnice střely
     * @param angle směr střely (zadaný v radiánech)
     * @param speed rychlost střely (jednotka pixel/frame)
     */
    Shot(const double x, const double y, const double angle, const double speed, Player * const parent);

    /**
     * Destruktor zajišťuje, aby mohlo být znovu použité ID této střely
     */
    ~Shot(void);

    /**
     * Metoda pro pohyb o jeden frame
     */
    void move(void);

    /**
     * Getr pro vlastníka
     */
    Player * getOwner(void) const;

    /**
     * Getr pro id střely
     */
    int getShotID(void) const;

    /**
     * Getry pro souřadnice střely
     */
    double getX(void) const;
    double getY(void) const;

private:

    /**
     * Toto pole udržuje záznamy o tom, která ID jsou pro střely použity
     */
    static QBitArray idArray;

    /**
     * Jednoznačné ID střely
     */
    int shotID;

    /**
     * Ukazatel na hráče, kterému patří střela
     */
    Player * owner;

    /**
     * Souřadnice střely
     */
    double x;
    double y;

    /**
     * Úhel, pod kterým střela letí
     */
    double angle;

    /**
     * Rychlost střely
     */
    double speed;

};

#endif // SHOT_H
