#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QApplication>

class Player;
class Shot;
class Game;

/**
 * Toto je abstraktní třída, která reprezentuje objekt na herní ploše
 */
class MapObject : public QObject
{

    Q_OBJECT

public:

    /**
     * Vytvoří objekt na mapě na konkrétních souřadnicích
     * @param parent hra v rámci níž je tento objekt vytvořen
     * @param x1 x-ová souřadnice levého horního rohu objektu
     * @param y1 y-ová souřadnice levého horního rohu objektu
     * @param x2 x-ová souřadnice pravého dolního rohu objektu
     * @param y2 y-ová souřadnice pravého dolního rohu objektu
     */
    MapObject(Game * const parent, const double x1 = -100.0, const double y1 = -100.0, const double x2 = -100.0, const double y2 = -100.0);

    /**
     * Metoda popisující jak se objekt zachová, když na něj vběhne hráč
     * @param player hráč, který chce na místo objektu vejít
     * @return vrací true, pokud hráč na místo objektu může vstoupit
     */
    virtual bool interactPlayer(Player * const player) = 0;

    /**
     * Metoda popisující jak se objekt zachová, když do něj vletí střela
     * @param shot střela, která vniká do objektů
     * @return vrací true, pokud přes objekt může střela letět
     */
    virtual bool interactShot(Shot * const shot) = 0;

    /**
     * Getry pro jednotlivé souřadnice
     */
    double getX1(void) const;
    double getY1(void) const;
    double getX2(void) const;
    double getY2(void) const;

protected:

    /**
     * Ukazatel na hru, ke které tento objekt patří
     */
    Game * parentGame;

    /**
     * Souřadnice pro levý horní roh
     */
    double x1;
    double y1;

    /**
     * Souřadnice pravý dolní roh
     */
    double x2;
    double y2;

    friend class Game;

};

#endif // MAPOBJECT_H
