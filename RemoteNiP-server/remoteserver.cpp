#include "remoteserver.h"
#include "ui_remoteserver.h"

RemoteServer::RemoteServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteServer) {
    ui->setupUi(this);

    _tcp_socket = nullptr;
    _udp_socket = new QUdpSocket(this);

    connect(_udp_socket, SIGNAL(readyRead()), this, SLOT(incoming_udp_data()));


    /*
     * Default port 5600
     * DontShareAddress - only this service listens to this port
     * ReuseAddressHint - reuse even if it's used by other service
     */
    _udp_socket->bind(5600, QUdpSocket::DontShareAddress
                     | QUdpSocket::ReuseAddressHint);
}

RemoteServer::~RemoteServer() {
    if(_tcp_socket){
        _tcp_socket->disconnectFromHost();
        _tcp_socket->deleteLater();
    }

    delete ui;
}

/*
 * incoming data on udp can be connection request
 * or transmission request
 *
 */
void RemoteServer::incoming_udp_data() {
    if(_tcp_socket == nullptr)
        connection_request();
    else
        transmission_request();
}

void RemoteServer::connection_request() {
    QByteArray msg;
    QByteArray ans;
    QHostAddress addr;

    msg.resize(_udp_socket->pendingDatagramSize());

    _udp_socket->readDatagram(msg.data(), msg.size(), &addr);

    QString req = "RNIP:REQ";

    if(msg.indexOf(req) == 0) {
        ans = "Connecting...";
        _udp_socket->writeDatagram(ans, addr, 5600);

        _tcp_socket = new QTcpSocket();

        connect(_tcp_socket, SIGNAL(disconnected()), this, SLOT(delete_connection()));

        /*
        * if socket is not ready for reconnection
        * this signal will be emitted
        */
        connect(_tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(delete_connection()));

        /*
        * FIX won't send connected() signal from local
        */
        connect(_tcp_socket, SIGNAL(connected()), this, SLOT(socket_connected()));

        _tcp_socket->connectToHost(addr, 5600);
    }
}

void RemoteServer::transmission_request() {
    // TODO recieve a message from client
}

void RemoteServer::delete_connection() {
    if(_tcp_socket == nullptr)
        return;

    _tcp_socket->deleteLater();
    _tcp_socket = nullptr;
}

void RemoteServer::socket_connected() {
    QMessageBox::information(this, tr("Connection"), tr("Socket connected!"));
}
