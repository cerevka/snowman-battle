#include "connectjoindialog.h"

ConnectJoinDialog::ConnectJoinDialog(QWidget *parent)
    : QDialog(parent)
{
    wait = new QLabel(tr("Waiting, for other players"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(wait);

    setLayout(layout);
    setFixedHeight(70);
    setFixedWidth(200);

}
