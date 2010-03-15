#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui>

class QAction;
class QMenu;

class Window : public QMainWindow
 {
     Q_OBJECT

 public:
     Window();

 private slots:
     void createGame( void );
     void joinGame( void );
     void settings( void );
     void about( void );
     void aboutQt( void );


 private:
     void createMenus();
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

 };


#endif // WINDOW_H
