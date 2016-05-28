#include "remoteserver.h"
#include "ui_remoteserver.h"

RemoteServer::RemoteServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteServer) {
    ui->setupUi(this);

    tcpSocket = nullptr;
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(incomingUdpData()));

    /*
     * Default port 5600
     * DontShareAddress - only this service listens to this port
     * ReuseAddressHint - reuse even if it's used by other service
     */
    udpSocket->bind(QHostAddress::AnyIPv4, 5600, QUdpSocket::DontShareAddress
                     | QUdpSocket::ReuseAddressHint);
}

RemoteServer::~RemoteServer() {
    if(tcpSocket){
        tcpSocket->disconnectFromHost();
        tcpSocket->deleteLater();
    }

    delete ui;
}

/*
 * incoming data on udp can be connection request
 * or transmission request
 *
 */
void RemoteServer::incomingUdpData() {
    if(tcpSocket == nullptr)
        connectionRequest();
    else
        transmissionRequest();
}

void RemoteServer::connectionRequest() {
    QByteArray msg;
    QHostAddress addr;
    msg.resize(udpSocket->pendingDatagramSize());

    udpSocket->readDatagram(msg.data(), msg.size(), &addr);

    QString req = "NiP:Hello";
    QString br = "NiP:Broadcast";

    if(msg.indexOf(req) == 0) {
        tcpSocket = new QTcpSocket();

        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(deleteConnection()));

        /*
        * if socket is not ready for reconnection
        * this signal will be emitted
        */
        connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteConnection()));
        connect(tcpSocket, SIGNAL(connected()), this, SLOT(socketConnected()));
        tcpSocket->connectToHost(addr, 5600);
    } else if(msg.indexOf(br) == 0) {
        QByteArray ans = "NiP:Connected";
        if(!tcpSocket) {
            ans = "NiP:NotConnected";
        }
        udpSocket->writeDatagram(ans, addr, 5600);
    }
}

void RemoteServer::transmissionRequest() {
    // TODO recieve a message from client
}

void RemoteServer::deleteConnection() {
    if(tcpSocket == nullptr)
        return;

    tcpSocket->deleteLater();
    tcpSocket = nullptr;
}

void RemoteServer::socketConnected() {
    QMessageBox::information(this, tr("Connection"), tr("Socket connected!"));
}
