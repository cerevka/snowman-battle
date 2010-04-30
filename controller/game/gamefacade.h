#ifndef GAMEFACADE_H
#define GAMEFACADE_H

#include <QObject>

class Game;
class Player;

/**
 * Fasáda, která vytváří rozhraní pro komunikaci s herní logikou
 * @author Ota Sandr
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
     * Slot pro zahájení pohybu směrem nahoru
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void startMoveNorth(const int playerID);

    /**
     * Slot pro zahájení pohybu směrem vlevo
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void startMoveWest(const int playerID);

    /**
     * Slot pro zahájení pohybu směrem dolů
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void startMoveSouth(const int playerID);

    /**
     * Slot pro zahájení pohybu směrem vpravo
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void startMoveEast(const int playerID);

    /**
     * Slot pro přerušení pohybu
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void stopMove(const int playerID);

    /**
     * Slot pro střelbu
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void shot(const int playerID);

    /**
     * Slot pro změnu zbraně
     * @param playerID id hráče, který tuto akci má vykonat
     */
    void changeWeapon(const int playerID);

    /**
     * Slot pro aktivování hráče
     * @param playerID id hráče, jenž se má aktivovat
     */
    void activatePlayer(const int playerID);

    /**
     * Sloty pro deaktivování hráče
     * @param playerID id hráče, jenž se má deaktivovat
     */
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
     * Pomocná metoda určená k tomu, aby pospojovala signály a sloty
     */
    void connectAll(void);

    /**
     * Jednoduchá metoda, kterou tato třída používá, aby se v ní tolik neopakoval kód
     * @param playerID id hráče, který se má vyhledat
     * @return ukazatel na hráče, který byl vyhledán podle id
     */
    Player * getPlayerById(const int playerID) const;

};

#endif // GAMEFACADE_H
