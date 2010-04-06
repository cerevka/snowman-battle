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

public slots:

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
     * Pauzne (nebo odpauzne) aktuální hru
     */
    void pauseGame(void);

    /**
     * Sloty pro zahájení pohybu danným směrem
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void startMoveNorth(const int playerID);
    void startMoveWest(const int playerID);
    void startMoveSouth(const int playerID);
    void startMoveEast(const int playerID);

    /**
     * Sloty pro přerušení pohybu, střelbu a změnu zbraně
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void stopMove(const int playerID);
    void shot(const int playerID);
    void changeWeapon(const int playerID);

    /**
     * Sloty pro aktivování a deaktivování hráče
     * @param playerID id hráče, jenž se má aktivovat nebo deaktivovat
     */
    void activatePlayer(const int playerID);
    void deactivatePlayer(const int playerID);

private:

    /**
     * Ukazatel na právě spuštěnou hru
     */
    Game * actualGame;

    /**
     * Je true pokud pod fasádou běží hra
     */
    bool isGameActive;

    /**
     * Jednoduchá metoda, kterou tato tída používá, aby se v ní tolik neopakoval kód
     * @param playerID id hráče, který se má vyhledat
     * @return ukazatel na hráče, který byl vyhledán podle id
     */
    Player * getPlayerById(const int playerID) const;

};

#endif // GAMEFACADE_H
