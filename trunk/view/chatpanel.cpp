#include "chatpanel.h"

ChatPanel::ChatPanel(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout;
    number = 0;
    setLayout(layout);
}

void ChatPanel::newMessage(QString *player, QString *message)
{
    QStringList list;
    list << "<" << *player << ">  " << *message;
    QString str = list.join("");
    QLabel *label = new QLabel(str);
    layout->addWidget(label, number++, 0, Qt::AlignTop);
}
