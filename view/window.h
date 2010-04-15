#ifndef WINDOW_H
#define WINDOW_H

#include "../globals.h"
#include <QMainWindow>
#include <QtGui>
#include "dialogs/creategame.h"
#include "dialogs/joingame.h"
#include "scenepanel.h"
#include "statusbar.h"
#include "chatpanel.h"
#include "controller/network/server.h"
#include "controller/network/client.h"
#include "controller/network/network.h"
#include "view/dialogs/connecteddialog.h"
#include "view/dialogs/connectjoindialog.h"
#include "view/dialogs/endgamedialog.h"


class QAction;
class QMenu;

/**
  * Trida reprezentujici hlavni okno programu
  */
class Window : public QMainWindow
 {
     Q_OBJECT

 public:
    /**
      * Vytvori hlavni okno programu
      */
     Window();

     /**
       * Preda referenci na ScenePanel
       */
     ScenePanel * getScenePanel( void );

     /**
       * Preda referenci na ChatPanel
       */
     ChatPanel * getChatPanel( void );

     /**
       * Preda referenci na StatusBar
       */
     StatusBar * getStatusBar( void );

     /**
       * Prida jemeno hrace do listu
       * @param id id hrace
       * @param name jmeno hrace
       */
     void addName(int id, QString * name);

     /**
       * Preda jmeno, ktere je na pozici id
       * @param id id hrace
       */
     QString * getName(int id);

 public slots:
     /**
       * Zobrazi ukoncovaci dialog a postara se o uklizeni vytvorenych onjektu
       * @param id jemeno vitezneho hrace
       */
     void endGame(int id);

 private slots:

     /**
       * Slot, ktery informuje o zalozeni hry
       */
     void createNewGame();

     /**
       * Zobrazi createGame dialog a zpracuje zadane informace
       */
     void createGame( void );

     /**
       * Zobraci joinGame dialog a zpracuje zadane informace
       */
     void joinGame( void );

     /**
       * Zobraci settings dialog a zpracuje zadane informace
       */
     void settings( void );

     /**
       * Zobrazi informace i aplokaci Snowmane battle
       */
     void about( void );

     /**
       * Zobrazi informace o Qt
       */
     void aboutQt( void );


 private:

     /**
       * Vytvori menu aplikace
       */
     void createMenus();

     /**
       * Vytvori akce, ktere vzniknou po vybrani polozky menu
       */
     void createActions();


     QMenu *gameMenu;
     QMenu *toolMenu;
     QMenu *helpMenu;
     QAction *createGameAct;
     QAction *joinGameAct;
     QAction *settingsAct;
     QAction *exitAct;
     QAction *aboutAct;
     QAction *aboutQtAct;

     ScenePanel *scenepanel;
     StatusBar *statusbar;
     ChatPanel *chatpanel;

     ConnectedDialog *connectionDialog;
     ConnectJoinDialog *connectJoinDialog;

     /**
       * List jmen hracu
       */
     QList<QString*> names;

 signals:

     /**
       * Signal rozesle zpravu o pridani jmeno no listu names
       * @param id id hrace
       */
     void clientNameAdded(int id);

 };


#endif // WINDOW_H
