#ifndef SHOT_H
#define SHOT_H

#include <QObject>

class Player;
class QBitArray;

/**
 * Třída reprezentující střelu letící na hrací ploše
 * @author Ota Sandr
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
     * Getr pro vlastníka střely
     * @return ukazatel na hráče, který tuto střelu vytvořil
     */
    inline Player * getOwner(void) const { return this->owner; }

    /**
     * Getr pro id střely
     * @return id této střely
     */
    inline int getShotID(void) const { return this->shotID; }

    /**
     * Getr pro x-ovou souřadnici střely
     * @return x-ová souřadnice střely
     */
    inline double getX(void) const { return this->x; }

    /**
     * Getr pro y-ovou souřadnici střely
     * @return y-ová souřadnice střely
     */
    inline double getY(void) const { return this->y; }

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
     * X-ová souřadnice střely
     */
    double x;

    /**
     * Y-ová souřadnice střely
     */
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
