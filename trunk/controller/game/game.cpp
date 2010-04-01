#include "game.h"

Game::Game(const int countOfPlayers, QObject * const parent) :
        QThread(parent)
{

    bigGameMutex = new QMutex();

    allObjects = new QList<MapObject *>();
    allPlayers = new QList<Player *>();
    allShots = new QList<Shot *>();

    // Zde vytvářím hráče pro hru
    for(int i = 0; i < countOfPlayers; i++){
        Player * const newPlayer = new Player(this, i);
        allPlayers->append(newPlayer);
        allObjects->append(newPlayer);
    }

    // TODO - zde bude definice mapy
    allObjects->append(new UnshootableBlock(this, 0, 0, 500, 30));
    allObjects->append(new UnshootableBlock(this, 0, 470, 500, 500));
    allObjects->append(new UnshootableBlock(this, 0, 30, 30, 470));
    allObjects->append(new UnshootableBlock(this, 470, 30, 500, 470));

    gameRun = true;

}

Game::~Game(void)
{

    gameRun = false;

    delete bigGameMutex;

    delete allObjects;
    delete allPlayers;
    delete allShots;

}

void Game::run(void)
{

    // Naspawnování všech hráčů
    for(int i = 0; i < allPlayers->size(); i++){
        allPlayers->value(i)->respawn();
    }

    // Dokud proměnná gameRun je true, tak provádím hlavní smyčku programu
    while(gameRun){

        bigGameMutex->lock();

        movePlayers();
        moveShots();

        bigGameMutex->unlock();

        QThread::msleep(100);

    }

}

void Game::quitGame(void)
{
    gameRun = false;
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

void Game::addShot(Shot * const shot)
{

    allShots->append(shot);

    // TODO - poslat signál o vytvoření střely
    #ifdef _DEBUG_
    cout << "Game engine: Shot " << allShots->size() - 1 << " created at " << shot->getX() << ", " << shot->getY() << endl;
    #endif

}

void Game::removeWeaponPackage(WeaponPackage * const wPackage)
{

    allObjects->removeOne(wPackage);

    // TODO - poslat signál o sebrání zbraně

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
            if(actualPlayer->isSpawned() == false){
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
                cout << "Game engine: Player " << actualPlayer->getID() << " moved to " << actualPlayer->getX1() << ", " << actualPlayer->getY1() << endl;
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
            cout << "Game engine: Shot " << i << " moved to " << actualShot->getX() << ", " << actualShot->getY() << endl;
            #endif
        } else {
            allShots->removeAt(i);
            delete actualShot; // TODO - pořešit ID střel
            // TODO - poslat informaci o rozpadnutí střely
            #ifdef _DEBUG_
            cout << "Game engine: Shot " << i << " destroyed" << endl;
            #endif
            i--;
        }

    }

}

bool Game::colideObjects(MapObject * const one, MapObject * const two)
{
    return colideRectangles(one, two) || colideRectangles(two, one);
}

bool Game::colideRectangles(MapObject * const first, MapObject * const second)
{
    return     colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX1(), second->getY1())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX2(), second->getY2())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX2(), second->getY1())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX1(), second->getY2());
}

bool Game::colideShots(MapObject * const object, Shot * const shot)
{
    return colideAlgorythm(object->getX1(), object->getY1(), object->getX2(), object->getY2(), shot->getX(), shot->getY());
}

bool Game::colideAlgorythm(const double recX1, const double recY1, const double recX2, const double recY2, const double pointX, const double pointY)
{

    if(pointX >= recX1 && pointX <= recX2 && pointY >= recY1 && pointY <= recY2){
        return true;
    } else {
        return false;
    }

}
