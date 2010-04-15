#ifndef CONNECTJOINDIALOG_H
#define CONNECTJOINDIALOG_H

#include <QDialog>
#include <QtGui>

class QLabel;

/**
  * Dialog, ktery se zobrazuje u klientu, pokud se pripojuji na server a ceka se na dalsi klienty
  */
class ConnectJoinDialog : public QDialog
{
    Q_OBJECT

public:

    /**
      * Konstruktor, ktery vytvori dialog
      */
    ConnectJoinDialog(QWidget *parent=0);

private:
    QLabel *wait;
};

#endif // CONNECTJOINDIALOG_H
