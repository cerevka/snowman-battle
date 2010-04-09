#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QDialog>
#include <QtGui>

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;

class CreateGame : public QDialog
 {
     Q_OBJECT

 public:
     CreateGame(QWidget *parent=0);
     QLineEdit *nickname;
     QComboBox *players;
     //QComboBox *color;


 private:
     QLabel *nicknameLabel;
     QLabel *playersLabel;
     //QLabel *colorLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
 };

#endif // CREATEGAME_H
