#ifndef CHATPANEL_H
#define CHATPANEL_H

#include <QWidget>
#include <QtGui>

class QLabel;

class ChatPanel : public QWidget
{
Q_OBJECT
public:
    explicit ChatPanel(QWidget *parent = 0);
    void newMessage(QString *player, QString *message);

private:
    QGridLayout *layout;
    int number;

};

#endif // CHATPANEL_H
