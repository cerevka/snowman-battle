
#include "player.h"

#include "../controller/game/game.h"
#include "../controller/game/gametimer.h"
#include "handgun.h"
#include "machinegun.h"
#include "shotgun.h"
#include "shot.h"

Player::Player(Game * const parent, const int id) :
        MapObject(parent)
{

    playerID = id;
    active = true;
    spawned = false;
    direction = NORTH;
    moving = false;
    shoting = false;
    canShot = true;
    score = 0;

    respawnTimer = NULL;
    cooldownTimer = NULL;

    // Vytvoření inventáře se zbraněmi
    inventory[0] = new HandGun(this);
    inventory[1] = new MachineGun(this);
    inventory[2] = new ShotGun(this);
    actualWeapon = 0;

}

bool Player::interactShot(Shot * const shot)
{

    if(active){

        spawned = false;

        // Zabití hráče
        x1 = -100.0;
        y1 = -100.0;
        x2 = -100.0;
        y2 = -100.0;

        emit playerKilled(playerID);
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Player" << playerID << "killed";
        #endif

        shot->getOwner()->incrementScore();

        // startuji časovač pro respawnutí
        respawnTimer = new GameTimer(respawnTimeFrames, this);
        connect(respawnTimer, SIGNAL(timeout()), this, SLOT(respawn()));
        parentGame->addTimer(respawnTimer);

    }

    return false;

}

void Player::respawn(void)
{

    if(respawnTimer != NULL){
        parentGame->removeTimer(respawnTimer);
        delete respawnTimer;
    }

    // Vygenerování nových souřednic
    parentGame->generateValidCoordinates(playerSize, playerSize, this);

    // Vygenerování nového směru
    direction = (Directions)(qrand() % 4);

    // Resetování příznaků
    actualWeapon = 0;
    moving = false;
    shoting = false;
    spawned = true;

    emit playerSpawned(playerID, qRound(x1), qRound(y1), direction);
    #ifdef _DEBUG_GAME_ENGINE_
    qDebug() << "Game engine: Player" << playerID << "spawned at (" << x1 << "," << y1 << "),(" << x2 << "," << y2 << "); direction:" << direction;
    #endif

}

void Player::tryMove(void)
{

    int modificatorX = 0;
    int modificatorY = 0;

    // Zálohuji souřadnice
    x1Backup = x1;
    x2Backup = x2;
    y1Backup = y1;
    y2Backup = y2;

    // Směru nastavim modifikátory, aby se provedl správně výpočet
    switch (direction)
    {
    case NORTH:
        {
            modificatorY = -1;
            break;
        }
    case WEST:
        {
            modificatorX = -1;
            break;
        }
    case SOUTH:
        {
            modificatorY = 1;
            break;
        }
    case EAST:
        {
            modificatorX = 1;
            break;
        }
    }

    // Vlastní změna souřadnic
    x1 = x1 + (modificatorX * stepSize);
    x2 = x2 + (modificatorX * stepSize);
    y1 = y1 + (modificatorY * stepSize);
    y2 = y2 + (modificatorY * stepSize);

}

void Player::backMove(void)
{

    x1 = x1Backup;
    x2 = x2Backup;
    y1 = y1Backup;
    y2 = y2Backup;

}

void Player::shot(void)
{

    shoting = false;

    // Mohu vystřelit jen pokud neběží cooldown
    if(canShot){
        // Výjimka nastane, pokud je více než 256 střel
        try{
            inventory[actualWeapon]->shot();
            canShot = false;

            cooldownTimer = new GameTimer(cooldownTimeFrames, this);
            connect(cooldownTimer, SIGNAL(timeout()), this, SLOT(enableShooting()));
            parentGame->addTimer(cooldownTimer);

            emit playerShoted(playerID);
            #ifdef _DEBUG_GAME_ENGINE_
            qDebug() << "Game engine: Player" << playerID << "shoted";
            #endif

        } catch (QString & ex){
            // Tato výjimka se ignoruje (střely navíc se prostě nevytvoří)
            #ifdef _DEBUG_GAME_ENGINE_
            qDebug() << "Game engine: Exception - to many shots";
            #endif
        }

    }

}

void Player::changeWeapon(void)
{

    if(spawned){

        // Hledám v inventáři zbraň, která nemá nula zbývajících nábojů
        do {
            actualWeapon = (actualWeapon + 1) % 3;
        } while(inventory[actualWeapon]->getAmmo() == 0);

        emit weaponChanged(playerID, actualWeapon, inventory[actualWeapon]->getAmmo());
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Player" << playerID << "equiped weapon" << actualWeapon;
        #endif

    }

}

void Player::setActualWeapon(const int actualWeapon)
{

    this->actualWeapon = actualWeapon;

    emit weaponChanged(playerID, actualWeapon, inventory[actualWeapon]->getAmmo());
    #ifdef _DEBUG_GAME_ENGINE_
    qDebug() << "Game engine: Player" << playerID << "equiped weapon" << actualWeapon;
    #endif

}

void Player::incrementScore(void)
{

    score++;

    emit scoreIncremented(playerID);
    #ifdef _DEBUG_GAME_ENGINE_
    qDebug() << "Game engine: Player" << playerID << "incremented score";
    #endif

    if((score == parentGame->getScoreToWin()) && (parentGame->isGameRunning())){

        emit playerWon(playerID);
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Player" << playerID << "won";
        #endif

    }

}

void Player::setDirection(const Directions direction)
{

    // TODO promyslet synchronizaci tady!!!
    if(this->direction != direction){
        emit playerTurned(playerID, direction);
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Player" << playerID << "turned (New direction:" << direction << ")";
        #endif
    }

    this->direction = direction;
}


void Player::setActive(const bool active)
{

    this->active = active;

    if(active){
        emit playerActivated(playerID);
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Player" << playerID << "activated";
        #endif
    } else {
        emit playerDeactivated(playerID);
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Player" << playerID << "deactivated";
        #endif
    }

}

void Player::enableShooting(void)
{

    parentGame->removeTimer(cooldownTimer);
    delete cooldownTimer;

    canShot = true;

}
