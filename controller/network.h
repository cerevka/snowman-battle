#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include "../controller/networkinterface.h"
#include "../controller/client.h"
#include "../controller/server.h"

/**
 * Network zaobaluje sitove rozhrani dle navrhoveho vzoru Strategy. Na
 * vyber jsou zakladni dve moznosti - client a server, pricemz obe musi
 * byt potomky tridy NetworkInterface.
 */
class Network : public QObject
{  
    Q_OBJECT

public:
    /**
     * Vytvoreni sitoveho rozhrani jako server ci client.
     * @param strategy ukazatel na zvoleny zpusob prace se siti
     */
    explicit Network(NetworkInterface *strategy, QObject * const parent = 0){
        network = strategy;
    }

    /**
     * Odeslani dat v poli znaku.
     * @param pole znaku k odeslani
     */
    void send(char * message) const;

    /**
     * Prijmuti dat v poli znaku.
     * @return prijate pole znaku
     */
    char * recieve();


private:
    /**
     * Udrzuje odkaz na zvolenou strategii.
     */
    NetworkInterface * network;

};

#endif // NETWORK_H
