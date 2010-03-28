#include "game.h"

Game::Game(QObject * const  parent) :
        QThread(parent)
{

    allObjects = new QList<MapObject *>();
    allPlayers = new QList<Player *>();
    allShots = new QList<Shot *>();

    gameRun = true;

}

Game::~Game(void)
{

    gameRun = false;

    delete allObjects;
    delete allPlayers;
    delete allShots;

}

void Game::run(void)
{

    // Naspawnování všech hráčů
    for(int i = 0; allPlayers->size(); i++){
        allPlayers->value(i)->respawn();
    }

    // Dokud proměnná gameRun je true, tak provádím hlavní smyčku programu
    while(gameRun){

        movePlayers();
        moveShots();

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
        if (colideObjects(object, allObjects->value(i))){
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

}

void Game::removeWeaponPackage(WeaponPackage * const wPackage)
{

    allObjects->removeOne(wPackage);

    // TODO - poslat signál o sebrání zbraně

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
                MapObject * actualObect = allObjects->value(j);

                // Pokud jsem vzal sám sebe, tak nedetekuji kolizi
                if(actualObect == actualPlayer){
                    continue;
                }

                // Pokud koliduji
                if(colideObjects(actualObect, actualPlayer)){
                    // Zavolám kolizní metodu
                    if(actualObect->interactPlayer(actualPlayer) == false){
                        // Pokud je objekt neprůchozí, pak rovnou vím, že se hráč nepohne
                        canMove = false;
                        break;
                    }
                }

            }

            // Pokud nestojí v cestě překážka, tak dám informaci o pohybu, jinak vrátím pohyb zpět
            if(canMove){
                // TODO - poslat zprávu o pohybu hráče
            } else {
                actualPlayer->backMove();
            }

            // Pokud mě hráč nastaven příznak střelby, tak vystřelí
            if(actualPlayer->isShoting()){
                actualPlayer->shot();
            }

        }

    }
}

void Game::moveShots(void)
{

    // Projíždím seznam střel
    for(int i = 0; i < allShots->size(); i++){

        // TODO pohyb střely ...

        // Prohledám všechny objekty
        for(int j = 0; j < allObjects->size(); j++){

            // Pokud koliduji
            if(colideObjects(allObjects->value(j), allShots->value(i))){
                // zavolám kolizní metodu
                allObjects->value(j)->interactShot(allShots->value(i));
            }

        }

    }

}

bool Game::colideObjects(MapObject * const first, MapObject * const second)
{
    return colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX1(), second->getY1())
            || colideAlgorythm(first->getX1(), first->getY1(), first->getX2(), first->getY2(), second->getX2(), second->getY2());
}

bool Game::colideObjects(MapObject * const object, Shot * const shot)
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
