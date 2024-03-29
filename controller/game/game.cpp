
#include "../../model/mapobject.h"
#include "../../model/player.h"
#include "../../model/shot.h"
#include "../../model/weaponpackage.h"
#include "../../model/shootableblock.h"
#include "../../model/unshootableblock.h"
#include "gametimer.h"

#include <QMutex>
#include <QWaitCondition>
#include <QTime>
#include <QTimerEvent>

#ifdef _DEBUG_GAME_ENGINE_

#include <QtDebug>

#endif

#include "game.h"

Game::Game(const int countOfPlayers, const int scoreToWin, QObject * const parent) :
        QThread(parent)
{

    this->moveToThread(this);

    bigGameMutex = new QMutex();
    pauseCondition = new QWaitCondition();

    allObjects = new QList<MapObject *>();
    allPlayers = new QList<Player *>();
    allShots = new QList<Shot *>();

    time = 0;

    // Zde vytvářím hráče pro hru
    for(int i = 0; i < countOfPlayers; i++){
        Player * const newPlayer = new Player(this, i);
        allPlayers->append(newPlayer);
        allObjects->append(newPlayer);
    }

    // Okraje mapy
    allObjects->append(new UnshootableBlock(this, -60, -60, 935, 0));
    allObjects->append(new UnshootableBlock(this, -60, 567, 935, 627));
    allObjects->append(new UnshootableBlock(this, -60, 0, 0, 576));
    allObjects->append(new UnshootableBlock(this, 875, 0, 935, 576));

    // Skály
    allObjects->append(new UnshootableBlock(this, 201, 118, 282, 235));
    allObjects->append(new UnshootableBlock(this, 724, 280, 799, 353));

    // Lesy
    allObjects->append(new UnshootableBlock(this, 361, 0, 443, 73));
    allObjects->append(new UnshootableBlock(this, 522, 40, 600, 114));
    allObjects->append(new UnshootableBlock(this, 81, 485, 162, 602));
//    allObjects->append(new UnshootableBlock(this, 242, 602, 322, 681));
//    allObjects->append(new UnshootableBlock(this, 401, 561, 482, 636));

    // Voda
    allObjects->append(new ShootableBlock(this, 98, 264, 142, 301));
    allObjects->append(new ShootableBlock(this, 59, 302, 182, 387));
    allObjects->append(new ShootableBlock(this, 95, 388, 182, 424));

    allObjects->append(new ShootableBlock(this, 343, 214, 415, 256));
    allObjects->append(new ShootableBlock(this, 343, 257, 506, 421));
    allObjects->append(new ShootableBlock(this, 507, 340, 530, 411));

    allObjects->append(new ShootableBlock(this, 590, 470, 648, 544));
    allObjects->append(new ShootableBlock(this, 624, 419, 734, 505));

    countOfWeapons = 0;

    this->scoreToWin = scoreToWin;
    paused = false;
    gameRun = true;

}

Game::~Game(void)
{

    gameRun = false;

    delete bigGameMutex;
    delete pauseCondition;

    delete allObjects;
    delete allPlayers;
    delete allShots;

}

void Game::run(void)
{

    // Inicializace náhodného generátoru čísel
    qsrand(QTime::currentTime().msec());

    // Naspawnování všech hráčů
    for(int i = 0; i < allPlayers->size(); i++){
        allPlayers->value(i)->respawn();
    }

    // Nastartuji časovač a spustím event loop
    startTimer(20);
    this->exec();

}

void Game::generateValidCoordinates(const double sizeX, const double sizeY, MapObject * const object)
{
    do {

        object->x1 = qAbs(qrand() % 875);
        object->x2 = object->x1 + sizeX;
        object->y1 = qAbs(qrand() % 567);
        object->y2 = object->y1 + sizeY;

    } while(colideAllObjects(object)); // provádím generování souřadnic, dokud nanajdu vyhovující místo
}

void Game::addShot(Shot * const shot)
{

    shot->moveToThread(this);
    shot->setParent(this);

    allShots->append(shot);

    emit shotCreated(shot->getShotID(), qRound(shot->getX()), qRound(shot->getY()));
    #ifdef _DEBUG_GAME_ENGINE_
    qDebug() << "Game engine: Shot" << shot->getShotID() << "created at" << shot->getX() << "," << shot->getY();
    #endif

}

void Game::removeWeaponPackage(WeaponPackage * const wPackage)
{

    allObjects->removeOne(wPackage);
    countOfWeapons--;

    emit wPackRemoved(wPackage->getWeaponPackageID());
    #ifdef _DEBUG_GAME_ENGINE_
    qDebug() << "Game engine: Weapon package" << wPackage->getWeaponPackageID() << "removed from" << wPackage->getX1() << "," << wPackage->getY1();
    #endif

}

void Game::timerEvent (QTimerEvent * const event)
{

    bigGameMutex->lock();

    // zvedám čas
    time++;

    // hlavní frame hry
    movePlayers();
    moveShots();
    generateWeaponPackages();

    // upravuji všechny časovače
    for(int i = 0; i < allTimers.size(); i++){
        allTimers.value(i)->update(time);
    }

    emit frameEnded();

    // pokud se má hra pauznout zastavím vlákno
    if(paused){

        emit gamePaused();

        pauseCondition->wait(bigGameMutex);
        paused = false;

        emit gameResumed();

    }

    bigGameMutex->unlock();

    // pokud se má hra ukončit, ukončím event loop
    if(!gameRun){

        killTimer(event->timerId());
        this->exit(0);

    }

}

void Game::movePlayers(void)
{

    // Projíždím seznam všech hráčů
    for(int i = 0; i < allPlayers->size(); i++){

        // Ukazatel na právě vybraného hráče (abych jej pořád nemusel vytahovat ze senamu)
        Player * actualPlayer = allPlayers->value(i);

        // Hráč mě zajímavá pouze pokud má nastavený příznak pohybu
        if(actualPlayer->isMoving()){

            // Je true, pokud se hráč může přesunout
            bool canMove = true;

            // Pokud je hráč mrtvý, tak jdu na dalšího
            if((actualPlayer->isSpawned() == false) || (actualPlayer->isActive() == false)){
                continue;
            }

            // Pohnu s hráčem
            actualPlayer->tryMove();

            // Prohledávám všechny objekty na mapě
            for(int j = 0; j < allObjects->size(); j++){

                // Ukazatel na právě vybraný objekt
                MapObject * actualObject = allObjects->value(j);

                // Pokud jsem vzal sám sebe, tak nedetekuji kolizi
                if(actualObject == actualPlayer){
                    continue;
                }

                // Pokud koliduji
                if(colideObjects(actualObject, actualPlayer)){
                    // Zavolám kolizní metodu
                    if(actualObject->interactPlayer(actualPlayer) == false){
                        // Pokud je objekt neprůchozí, pak rovnou vím, že se hráč nepohne
                        canMove = false;
                        break;
                    }
                }

            }

            // Pokud nestojí v cestě překážka, tak dám informaci o pohybu, jinak vrátím pohyb zpět
            if(canMove){
                emit playerMoved(actualPlayer->getID(), qRound(actualPlayer->getX1()), qRound(actualPlayer->getY1()));
                #ifdef _DEBUG_GAME_ENGINE_
                qDebug() << "Game engine: Player" << actualPlayer->getID() << "moved to" << actualPlayer->getX1() << "," << actualPlayer->getY1();
                #endif
            } else {
                actualPlayer->backMove();
            }
        }

        // Pokud mě hráč nastaven příznak střelby, tak vystřelí
        if(actualPlayer->isSpawned() && actualPlayer->isShoting()){
            actualPlayer->shot();
        }

    }
}

void Game::moveShots(void)
{

    // Projíždím seznam střel
    for(int i = 0; i < allShots->size(); i++){

        // Ukazatel na právě vybranou střelu (abych ji pořád nemusel vytahovat ze senamu)
        Shot * actualShot = allShots->value(i);

        // Je true, pokud se střela může pohnout
        bool canMove = true;

        // Pohnu střelou
        actualShot->move();

        // Prohledám všechny objekty
        for(int j = 0; j < allObjects->size(); j++){

            // Ukazatel na právě vybraný objekt
            MapObject * actualObject = allObjects->value(j);

            // Pokud koliduji
            if(colideShots(actualObject, actualShot)){
                // Zavolám kolizní metodu
                if(actualObject->interactShot(actualShot) == false){
                    // Pokud je objekt neprůstřelný, pak rovnou vím, že se střela rozpadne
                    canMove = false;
                    break;
                }
            }

        }

        // Pokud nestojí v cestě překážka, tak dám informaci o pohybu, jinak smažu střelu
        if(canMove){
            emit shotMoved(actualShot->getShotID(), qRound(actualShot->getX()), qRound(actualShot->getY()));
            #ifdef _DEBUG_GAME_ENGINE_
            qDebug() << "Game engine: Shot" << actualShot->getShotID() << "moved to" << actualShot->getX() << "," << actualShot->getY();
            #endif
        } else {
            allShots->removeAt(i);
            emit shotDestroyed(actualShot->getShotID());
            #ifdef _DEBUG_GAME_ENGINE_
            qDebug() << "Game engine: Shot" << actualShot->getShotID() << "destroyed";
            #endif
            delete actualShot;
            i--;
        }

    }

}

void Game::generateWeaponPackages(void)
{

    // Pokud není na ploše žádná zbraň, můžu ji s určitou pravděpodobností vytvořit
    if((countOfWeapons < 3) && ((qrand()%1000) < 5)){

        countOfWeapons++;

        WeaponPackage * const newPack = new WeaponPackage(this);
        allObjects->append(newPack);

        emit wPackCreated(newPack->getWeaponPackageID(), newPack->getX1(), newPack->getY1(), newPack->getType());
        #ifdef _DEBUG_GAME_ENGINE_
        qDebug() << "Game engine: Weapon pack" << newPack->getWeaponPackageID() << "created at" << newPack->getX1() << "," << newPack->getY1() << "; Type:" << newPack->getType();
        #endif

    }

}

bool Game::colideAllObjects(MapObject * const object) const
{

    bool output = false;

    // Prohledávám všechny objekty na herní ploše
    for(int i = 0; i < allObjects->size(); i++){

        // Pokud jsem vzal totožný objekt, tak netestuji kolize
        if(object == allObjects->value(i)){
            continue;
        }

        // Pokud objekt koliduje, ukončím metodu s tím, že existuje objekt, který koliduje
        if (colideObjects(allObjects->value(i), object)){
            output = true;
            break;
        }

    }

    return output;

}

inline bool Game::colideObjects(MapObject * const first, MapObject * const second)
{
    return colideRectangles(first, second) || colideRectangles(second, first) || colideOverlap(first, second) || colideOverlap(first, second);
}

inline bool Game::colideOverlap(MapObject * const first, MapObject * const second)
{
    return (first->getX1() > second->getX1() && first->getX2() < second->getX2() && second->getY1() > first->getY1() && second->getY2() < second->getY1());
}

inline bool Game::colideRectangles(MapObject * const first, MapObject * const second)
{
    return     colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX1(), second->getY1())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX2(), second->getY2())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX2(), second->getY1())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX1(), second->getY2());
}

inline bool Game::colideShots(MapObject * const object, Shot * const shot)
{
    return colideAlgorythm(object->getX1(), object->getY1(), object->getX2(), object->getY2(), shot->getX(), shot->getY());
}

inline bool Game::colideAlgorythm(const double recX1, const double recY1, const double recX2, const double recY2, const double pointX, const double pointY)
{

    if(pointX >= recX1 && pointX <= recX2 && pointY >= recY1 && pointY <= recY2){
        return true;
    } else {
        return false;
    }

}
