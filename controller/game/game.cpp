#include "game.h"

Game::Game(const int countOfPlayers, QObject * const parent) :
        QThread(parent)
{

    this->moveToThread(this);

    bigGameMutex = new QMutex();
    pauseCondition = new QWaitCondition();

    allObjects = new QList<MapObject *>();
    allPlayers = new QList<Player *>();
    allShots = new QList<Shot *>();

    // Zde vytvářím hráče pro hru
    for(int i = 0; i < countOfPlayers; i++){
        Player * const newPlayer = new Player(this, i);
        allPlayers->append(newPlayer);
        allObjects->append(newPlayer);
    }

    // Okraje mapy
    allObjects->append(new UnshootableBlock(this, -30, -30, 905, 0));
    allObjects->append(new UnshootableBlock(this, -30, 567, 905, 743));
    allObjects->append(new UnshootableBlock(this, -30, 0, 0, 713));
    allObjects->append(new UnshootableBlock(this, 875, 0, 905, 743));

    // Skály
    allObjects->append(new UnshootableBlock(this, 201, 118, 282, 235));
    allObjects->append(new UnshootableBlock(this, 724, 280, 799, 353));

    // Lesy
    allObjects->append(new UnshootableBlock(this, 361, 0, 443, 73));
    allObjects->append(new UnshootableBlock(this, 522, 40, 600, 114));
    allObjects->append(new UnshootableBlock(this, 81, 480, 162, 602));
    allObjects->append(new UnshootableBlock(this, 242, 602, 322, 681));
    allObjects->append(new UnshootableBlock(this, 401, 561, 482, 636));

    // Voda
    allObjects->append(new ShootableBlock(this, 98, 264, 142, 301));
    allObjects->append(new ShootableBlock(this, 59, 302, 182, 387));
    allObjects->append(new ShootableBlock(this, 95, 388, 182, 424));

    allObjects->append(new ShootableBlock(this, 343, 214, 415, 256));
    allObjects->append(new ShootableBlock(this, 343, 257, 506, 421));
    allObjects->append(new ShootableBlock(this, 507, 340, 542, 421));

    allObjects->append(new ShootableBlock(this, 577, 466, 648, 544));
    allObjects->append(new ShootableBlock(this, 624, 419, 734, 510));

    countOfWeapons = 0;

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

void Game::quitGame(void)
{
    gameRun = false;
}

void Game::generateValidCoordinates(const double size, MapObject * const object)
{
    do {

        object->x1 = qAbs(qrand() % 875);
        object->x2 = object->x1 + size;
        object->y1 = qAbs(qrand() % 713);
        object->y2 = object->y1 + size;

    } while(colideAllObjects(object)); // provádím generování souřadnic, dokud nanajdu vyhovující místo
}

void Game::addShot(Shot * const shot)
{

    shot->moveToThread(this);
    shot->setParent(this);

    allShots->append(shot);

    // TODO - poslat signál o vytvoření střely
    #ifdef _DEBUG_
    qDebug() << "Game engine: Shot" << shot->getShotID() << "created at" << shot->getX() << "," << shot->getY();
    #endif

}

void Game::removeWeaponPackage(WeaponPackage * const wPackage)
{

    allObjects->removeOne(wPackage);
    countOfWeapons--;

    // TODO - poslat signál o sebrání zbraně
    #ifdef _DEBUG_
    qDebug() << "Game engine: Weapon package" << wPackage->getWeaponPackageID() << "removed from" << wPackage->getX1() << "," << wPackage->getY1();
    #endif

}

void Game::timerEvent (QTimerEvent * const event)
{

    bigGameMutex->lock();

    movePlayers();
    moveShots();
    generateWeaponPackages();

    bigGameMutex->unlock();

    // pokud se má hra pauznout zastavím vlákno
    if(paused){
        pauseCondition->wait(bigGameMutex);
        paused = false;
    }

    // pokud se má hra ukončit, ukončím event loop
    if(!gameRun){

        killTimer(event->timerId());
        this->exit(0);

    }

}

QMutex * Game::getBigGameMutex(void) const
{
    return bigGameMutex;
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
                if(colideRectangles(actualObject, actualPlayer)){
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
                // TODO - poslat zprávu o pohybu hráče
                #ifdef _DEBUG_
                qDebug() << "Game engine: Player" << actualPlayer->getID() << "moved to" << actualPlayer->getX1() << "," << actualPlayer->getY1();
                #endif
            } else {
                actualPlayer->backMove();
            }
        }

        // Pokud mě hráč nastaven příznak střelby, tak vystřelí
        if(actualPlayer->isShoting()){
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
            // TODO - poslat informaci o pohybu střely
            #ifdef _DEBUG_
            qDebug() << "Game engine: Shot" << actualShot->getShotID() << "moved to" << actualShot->getX() << "," << actualShot->getY();
            #endif
        } else {
            allShots->removeAt(i);
            delete actualShot;
            // TODO - poslat informaci o rozpadnutí střely
            #ifdef _DEBUG_
            qDebug() << "Game engine: Shot" << actualShot->getShotID() << "destroyed";
            #endif
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

        // TODO - poslat signál o vytvoření ležící zbraně
        #ifdef _DEBUG_
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
        if (colideRectangles(allObjects->value(i), object)){
            output = true;
            break;
        }

    }

    return output;

}

inline bool Game::colideObjects(MapObject * const one, MapObject * const two)
{
    return colideRectangles(one, two) || colideRectangles(two, one);
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
