#ifndef JOINGAME_H
#define JOINGAME_H

#include <QDialog>
#include <QtGui>

class QLabel;
class QPushButton;
class QLineEdit;

/**
  * Trida reprezentujici dialog pro pripojeni se k serveru
  */
class JoinGame : public QDialog
 {
     Q_OBJECT

 public:

    /**
      * Vytvori pripojovaci dialog
      * @param parent rodic dialogu
      */
    JoinGame(QWidget *parent=0);

    QLineEdit *nickname;
    QLineEdit *address;


 private:
     QLabel *nicknameLabel;
     QLabel *addressLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
 };

#endif // JOINGAME_H
