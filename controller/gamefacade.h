#ifndef GAMEFACADE_H
#define GAMEFACADE_H

#include <QObject>

class Game;
class Player;

/**
 * Fasáda, která vytváří rozhraní pro komunikaci s herní logikou
 */
class GameFacade : public QObject
{

Q_OBJECT

public:

    /**
     * Vytvoření fasády, která zastřešuje vnitřní logiku hry
     * @param parent určuje rodičovský objekt
     */
    explicit GameFacade(QObject * const parent = 0);

    /**
     * Destruktor ukončí aktuálně běžící hru
     */
    virtual ~GameFacade(void);

    /**
     * Vytvoří novou hru se zadaným počtem hráčů
     * @param countOfPlayers počet hráčů, kteří budou hrát
     */
    void newGame(const int countOfPlayers);

    /**
     * Ukončí aktuální hru
     */
    void endGame(void);

    /**
     * Pauzne aktuální hru
     */
    void pauseGame(void);

    /**
     * Metody pro zahájení pohybu danným směrem
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void startMoveNorth(const int playerID);
    void startMoveWest(const int playerID);
    void startMoveSouth(const int playerID);
    void startMoveEast(const int playerID);

    /**
     * Metody pro přerušení pohybu, střelbu a změnu zbraně
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void stopMove(const int playerID);
    void shot(const int playerID);
    void changeWeapon(const int playerID);

private:

    Game * actualGame;

    Player * getPlayerById(const int playerID) const;

};

#endif // GAMEFACADE_H
