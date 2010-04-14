#include "gamefacade.h"

#include "game.h"
#include "../../model/player.h"
#include "globals.h"

GameFacade::GameFacade(QObject * const parent) :
    QObject(parent)
{

    actualGame = NULL;
    isGameActive = false;

}

GameFacade::~GameFacade(void)
{

    if(isGameActive){
        endGame();
    }

}

void GameFacade::newGame(const int countOfPlayers)
{

    if(!isGameActive){

        // Vytvářím objekt hry
        actualGame = new Game(countOfPlayers);

        // Spojím signály a sloty
        connectAll();

        // Startuji vlákno
        actualGame->start();

        isGameActive = true;

    }

}

void GameFacade::endGame(void)
{

    if(isGameActive){

        // Nastavím ukončení vlákna
        actualGame->quitGame();

        // Čekám na ukončení vlákna
        actualGame->wait();

        delete actualGame;

        isGameActive = false;
    }

}

void GameFacade::pauseGame(void)
{

    if(isGameActive){

        if(actualGame->paused){
            actualGame->pauseCondition->wakeAll();
        } else {
            actualGame->paused = true;
        }

    }

}

void GameFacade::startMoveNorth(const int playerID)
{

    if(isGameActive){
        Player * const player = getPlayerById(playerID);

        player->setDirection(NORTH);
        player->setMoving(true);
    }

}

void GameFacade::startMoveWest(const int playerID)
{

    if(isGameActive){
        Player * const player = getPlayerById(playerID);

        player->setDirection(WEST);
        player->setMoving(true);
    }

}

void GameFacade::startMoveSouth(const int playerID)
{

    if(isGameActive){
        Player * const player = getPlayerById(playerID);

        player->setDirection(SOUTH);
        player->setMoving(true);
    }

}

void GameFacade::startMoveEast(const int playerID)
{

    if(isGameActive){
        Player * const player = getPlayerById(playerID);

        player->setDirection(EAST);
        player->setMoving(true);
    }

}

void GameFacade::stopMove(const int playerID)
{
    if(isGameActive){
        getPlayerById(playerID)->setMoving(false);
    }
}

void GameFacade::shot(const int playerID)
{
    if(isGameActive){
        getPlayerById(playerID)->setShoting(true);
    }
}

void GameFacade::changeWeapon(const int playerID)
{
    if(isGameActive){
        getPlayerById(playerID)->changeWeapon();
    }
}

void GameFacade::activatePlayer(const int playerID)
{
    if(isGameActive){
        getPlayerById(playerID)->setActive(true);
    }
}

void GameFacade::deactivatePlayer(const int playerID)
{
    if(isGameActive){
        getPlayerById(playerID)->setActive(false);
    }
}

void GameFacade::connectAll(void)
{

    connect(actualGame, SIGNAL(frameEnded()), Globals::packetCreator, SLOT(sendGameEnginePacket()));

    connect(actualGame, SIGNAL(shotCreated(int,int,int)), Globals::packetCreator, SLOT(createShot(int,int,int)));
    connect(actualGame, SIGNAL(shotMoved(int,int,int)), Globals::packetCreator, SLOT(moveShot(int,int,int)));
    connect(actualGame, SIGNAL(shotDestroyed(int)), Globals::packetCreator, SLOT(destroyShot(int)));

    connect(actualGame, SIGNAL(playerMoved(int,int,int)), Globals::packetCreator, SLOT(movePlayer(int,int,int)));

    connect(actualGame, SIGNAL(wPackCreated(int,int,int,int)), Globals::packetCreator, SLOT(spawnWeaponPack(int,int,int,int)));
    connect(actualGame, SIGNAL(wPackRemoved(int)), Globals::packetCreator, SLOT(despawnWeaponPack(int)));

    for(int i = 0; i < actualGame->allPlayers->size(); i++){

        Player * actualPlayer = actualGame->allPlayers->value(i);

        connect(actualPlayer, SIGNAL(playerSpawned(int,int,int,int)), Globals::packetCreator, SLOT(spawnPlayer(int,int,int,int)));
        connect(actualPlayer, SIGNAL(playerKilled(int)), Globals::packetCreator, SLOT(killPlayer(int)));
        connect(actualPlayer, SIGNAL(playerShoted(int)), Globals::packetCreator, SLOT(playerShots(int)));
        connect(actualPlayer, SIGNAL(weaponChanged(int,int,int)), Globals::packetCreator, SLOT(changeWeapon(int,int,int)));
        connect(actualPlayer, SIGNAL(scoreIncremented(int)), Globals::packetCreator, SLOT(incrementScore(int)));

        connect(actualPlayer, SIGNAL(playerActivated(int)), Globals::packetCreator, SLOT(activatePlayer(int)));
        connect(actualPlayer, SIGNAL(playerDeactivated(int)), Globals::packetCreator, SLOT(deactivatePlayer(int)));
    }

}

Player * GameFacade::getPlayerById(const int playerID) const
{
    return actualGame->allPlayers->value(playerID);
}
