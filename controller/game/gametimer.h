#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>

/**
 * Třída reprezentující jednoduchý časovač, který lze zapauzovat
 * @author Ota Sandr
 */
class GameTimer : public QObject
{

    Q_OBJECT

public:

    /**
     * Konstruktor vytvoří nový časovač
     * @param interval udavá počet framů, po kterých bude vyemitován signál
     * @param parent objekt, kterému patří tento časovač
     */
    GameTimer(const int interval, QObject * const parent = 0);

    /**
     * Odstartuje časovač
     * @param actualTime aktuální čas ve chvíli odstartování
     */
    void start(const int actualTime);

    /**
     * Zjistí, zdali již uplanylu doba stanovená časovačem
     * @param actualTime aktuální čas
     */
    void update(const int actualTime);

signals:

    /**
     * Signál, který se emituje pokud vypršel časovač
     */
    void timeout(void);

private:

    /**
     * Čas, kdy časovač nastartoval
     */
    int startTime;

    /**
     * Počet framů, po kterých se emituje signál
     */
    int interval;

};

#endif // GAMETIMER_H
