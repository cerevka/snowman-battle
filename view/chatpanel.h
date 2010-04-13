#ifndef CHATPANEL_H
#define CHATPANEL_H

#include <QWidget>
#include <QtGui>

class QLineEdit;
class QPushButton;
class QTextEdit;


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

public slots:

    /**
      * Prida novou zpravu do chatovaciho okna
      * @param palyer autor zpravy
      * @param message text zpravy
      */
    void newMessage(int id, QString *message);

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
    QTextEdit *chatMess;
    QPushButton *sendButton;

signals:

    /**
      * Signal pro odeslani zpravy
      * @param id id hrace
      * @param message odesilana zprava
      */
    void sendMessage(int id, QString *message);

};

#endif // CHATPANEL_H
