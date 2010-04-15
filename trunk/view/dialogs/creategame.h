#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QDialog>
#include <QtGui>

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;

/**
  * Trida reprezentujici dialog pro zalozeni serveru
  */
class CreateGame : public QDialog
 {
     Q_OBJECT

 public:

    /**
      * Vytvori dialog
      * @param parent rodic dialogu
      */
    CreateGame(QWidget *parent=0);

    QLineEdit *nickname;
    QComboBox *players;


 private:
     QLabel *nicknameLabel;
     QLabel *playersLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
 };

#endif // CREATEGAME_H
