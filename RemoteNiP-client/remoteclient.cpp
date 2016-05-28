#include "remoteclient.h"
#include "ui_remoteclient.h"

RemoteClient::RemoteClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteClient){
    ui->setupUi(this);

    tcpSocket = nullptr;

    tcpServer = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(ui->chooseNetworkButton, SIGNAL(clicked()), this, SLOT(sendConnectionRequest()));
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(initialize()));
}

RemoteClient::~RemoteClient(){
    delete ui;
    tcpServer->close();
    tcpServer->deleteLater();
    udpSocket->abort();
    udpSocket->deleteLater();
}

void RemoteClient::initialize(){
    ui->chooseNetworkComboBox->clear();
    tcpServer->close();
    tcpServer->listen(QHostAddress::AnyIPv4, 5600);

    QByteArray datagram = "NiP:Broadcast";

    udpSocket->close();

    udpSocket->bind(QHostAddress::AnyIPv4, 5600, QUdpSocket::DontShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(incomingUdpData()));
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 5600);
}

// send connection request to selected address
void RemoteClient::sendConnectionRequest(){
    m_hostAddress.setAddress((ui->chooseNetworkComboBox->currentText()));

    QByteArray datagram = "NiP:Hello";

    tcpServer->close();
    tcpServer->listen(QHostAddress::AnyIPv4, 5600);
    udpSocket->writeDatagram(datagram, m_hostAddress, 5600);
}

// if there is new pending connection request, establish connection
void RemoteClient::newConnection(){
    if (!tcpSocket) {
        tcpSocket = tcpServer->nextPendingConnection();

        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(deleteConnection()));
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(incomingData()));
    }
}



void RemoteClient::incomingUdpData(){
    QHostAddress hostAddress;
    QByteArray datagram;

    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size(), &hostAddress);

    QString available = "NiP:NotConnected";
    QString bussy = "NiP:Connected";

    if(datagram.indexOf(available) == 0) {
        // if positive broadcast reply add address to combobox
        ui->chooseNetworkComboBox->addItem(hostAddress.toString());
    } else if(datagram.indexOf(bussy) == 0){

    }
}

void RemoteClient::incomingData(){
    // TODO send a message to server
}

void RemoteClient::deleteConnection(){
    tcpSocket->abort();
    tcpSocket->deleteLater();
    tcpSocket = nullptr;
}



