#include "chatpanel.h"
#include "globals.h"

ChatPanel::ChatPanel(QWidget *parent) :
    QWidget(parent)
{    
    messageEdit = new QLineEdit;
    sendButton = new QPushButton(tr("Send"));
    layout = new QGridLayout;

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(messageEdit);
    buttonLayout->addWidget(sendButton);

    layout->addLayout(buttonLayout, 1000, 0, Qt::AlignBottom);
    number = 0;
    setLayout(layout);

    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(this, SIGNAL(sendMessage(int, QString*)), Globals::packetCreator, SLOT(sendChatMessage(int, QString*)));
}

void ChatPanel::newMessage(QString *player, QString *message)
{
    QStringList list;
    list << "<" << *player << ">  " << *message;
    QString str = list.join("");

    QLabel *label = new QLabel(str);
    layout->addWidget(label, number++, 0, Qt::AlignTop);
}

void ChatPanel::sendMessage( void )
{
    QString mess = messageEdit->text();
    int id = Globals::network->getNetworkID();
    messageEdit->clear();

    emit sendMessage(id, &mess);
}
