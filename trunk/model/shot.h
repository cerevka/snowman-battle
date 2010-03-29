#ifndef SHOT_H
#define SHOT_H

#include <QObject>

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
    Shot(QObject * const parent, const double x, const double y, const double angle, const double speed);

    /**
     * Metoda pro pohyb o jeden frame
     */
    void move(void);

    /**
     * Getry pro souřadnice střely
     */
    double getX(void) const;
    double getY(void) const;

private:

    double x;
    double y;
    double angle;
    double speed;

};

#endif // SHOT_H
