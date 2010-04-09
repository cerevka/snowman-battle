#ifndef JOINGAME_H
#define JOINGAME_H

#include <QDialog>
#include <QtGui>

class QLabel;
class QPushButton;
class QLineEdit;

class JoinGame : public QDialog
 {
     Q_OBJECT

 public:
     JoinGame(QWidget *parent=0);
     QLineEdit *nickname;
     QLineEdit *address;
     //QLineEdit *port;
     //QComboBox *color;


 private:
     QLabel *nicknameLabel;
     QLabel *addressLabel;
     //QLabel *portLabel;
     //QLabel *colorLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
 };

#endif // JOINGAME_H
