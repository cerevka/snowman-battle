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

     ScenePanel * getScenePanel( void );
     ChatPanel * getChatPanel( void );
     StatusBar * getStatusBar( void );

     void addName(int id, QString * name);
     QString * getName(int id);

 private slots:

     /**
       * Signal, ktery informuje o zalozeni hry
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

     //// Tohle je pro testovani////
     int x, x1;
     int y, y1;
     PixmapItem *snow;
     PixmapItem *snow1;
     ConnectedDialog *connectionDialog;

     QList<QString*> names;

 signals:
     void clientNameAdded(int id);

 };


#endif // WINDOW_H
