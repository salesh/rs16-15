#include "remoteclient.h"
#include "ui_remoteclient.h"

RemoteClient::RemoteClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteClient)
{
    ui->setupUi(this);
}

RemoteClient::~RemoteClient()
{
    delete ui;
}
