#ifndef CONNECTEDDIALOG_H
#define CONNECTEDDIALOG_H

#include <QDialog>
#include <QtGui>

class QLabel;
class QToolButton;

/**
  * Trida, ktera zobrazi hrace, kteri jsou pripojeni k serveru na zacatku hry
  */

class ConnectedDialog : public QDialog
{
    Q_OBJECT

public:

    /**
      * Vytvori dialog
      * @param parent rodic dialogu
      */
    ConnectedDialog(QWidget *parent=0);

    /**
      * Prida hrace na dialog
      * @param id id hrace
      * @param name jemno hrace
      */
    void addPlayer(int id, QString &name);

private:
    QGridLayout *layout;

    QLabel *name1;
    QToolButton *image1Button;
    QImage image1;

    QLabel *name2;
    QToolButton *image2Button;
    QImage image2;

    QLabel *name3;
    QToolButton *image3Button;
    QImage image3;

    QLabel *name4;
    QToolButton *image4Button;
    QImage image4;

    QLabel *name5;
    QToolButton *image5Button;
    QImage image5;

    QLabel *name6;
    QToolButton *image6Button;
    QImage image6;

    /**
      * Barvy jednotlivych hracu
      */
    QStringList colors;
};

#endif // CONNECTEDDIALOG_H