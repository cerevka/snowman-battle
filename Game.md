# Herní engine #

Pro realizaci detekce kolizí je realizováno zvláštním vláknem v tzv. framech. V každém framu se prochází seznamy všech hráčů a střel a detekují se u nich kolize. Tato metoda framu je realizována pomocí QObject timeru, který se volá každých 20 ms.

Takto vypadá metoda timerEvent, která je vlastním framem:

```

void Game::timerEvent (QTimerEvent * const event)
{

    bigGameMutex->lock();

    movePlayers();
    moveShots();
    generateWeaponPackages();

    emit frameEnded();

    // pokud se má hra pauznout zastavím vlákno
    if(paused){
        pauseCondition->wait(bigGameMutex);
        paused = false;
    }

    bigGameMutex->unlock();

    // pokud se má hra ukončit, ukončím event loop
    if(!gameRun){

        killTimer(event->timerId());
        this->exit(0);

    }

}

```