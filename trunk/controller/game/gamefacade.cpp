#include "gamefacade.h"

#include "game.h"
#include "../../model/player.h"

GameFacade::GameFacade(QObject * const parent) :
    QObject(parent)
{

    actualGame = NULL;

}

GameFacade::~GameFacade(void)
{

    if(actualGame != NULL){
        endGame();
    }

}

void GameFacade::newGame(const int countOfPlayers)
{

    // Vytvářm objekt hry
    actualGame = new Game(countOfPlayers);

    // Startuji vlákno
    actualGame->start();

}

void GameFacade::endGame(void)
{
    // Nastavím ukončení vlákna
    actualGame->quitGame();

    // Čekám na ukončení vlákna
    actualGame->wait();

    delete actualGame;
}

void GameFacade::pauseGame(void)
{

}

void GameFacade::startMoveNorth(const int playerID)
{

    Player * const player = getPlayerById(playerID);

    player->setDirection(NORTH);
    player->setMoving(true);

}

void GameFacade::startMoveWest(const int playerID)
{

    Player * const player = getPlayerById(playerID);

    player->setDirection(WEST);
    player->setMoving(true);

}

void GameFacade::startMoveSouth(const int playerID)
{

    Player * const player = getPlayerById(playerID);

    player->setDirection(SOUTH);
    player->setMoving(true);

}

void GameFacade::startMoveEast(const int playerID)
{

    Player * const player = getPlayerById(playerID);

    player->setDirection(EAST);
    player->setMoving(true);

}

void GameFacade::stopMove(const int playerID)
{
    getPlayerById(playerID)->setMoving(false);
}

void GameFacade::shot(const int playerID)
{
    getPlayerById(playerID)->setShoting(true);
}

void GameFacade::changeWeapon(const int playerID)
{
    getPlayerById(playerID)->changeWeapon();
}

Player * GameFacade::getPlayerById(const int playerID) const
{
    return actualGame->allPlayers->value(playerID);
}
