#ifndef CHATPANEL_H
#define CHATPANEL_H

#include <QWidget>
#include <QtGui>

class QLabel;
class QLineEdit;
class QPushButton;


/**
  * Trida reprezentujice chatovaci panel
  */
class ChatPanel : public QWidget
{
Q_OBJECT
public:

    /**
      * Vytvori chatovaci panel
      */
    explicit ChatPanel(QWidget *parent = 0);

    /**
      * Prida novou zpravu do chatovaciho okna
      * @param palyer autor zpravy
      * @param message text zpravy
      */
    void newMessage(QString *player, QString *message);

public slots:

    /**
      * Odeslani nove vytvorene zpravy
      */
    void sendMessage( void );

private:
    QGridLayout *layout;

    /**
      * Pocet zprav
      */
    int number;
    QLineEdit *messageEdit;
    QPushButton *sendButton;


};

#endif // CHATPANEL_H
