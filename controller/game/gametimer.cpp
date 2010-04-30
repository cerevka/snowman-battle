
#include "gametimer.h"

GameTimer::GameTimer(const int interval, QObject * const parent) :
    QObject(parent)
{

    this->interval = interval;
    this->startTime = 0;

}

void GameTimer::start(const int actualTime)
{

    this->startTime = actualTime;

}

void GameTimer::update(const int actualTime)
{

    // TODO trochu by to chtělo ještě vylepšit (kvůli přetečení)
    if(qAbs(startTime - actualTime) > interval){
        emit timeout();
    }

}
