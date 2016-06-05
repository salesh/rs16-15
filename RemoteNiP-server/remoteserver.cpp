#include "remoteserver.h"
#include "ui_remoteserver.h"
#include "GlobalFakeKey.h"

RemoteServer::RemoteServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteServer) {
    ui->setupUi(this);

    trayIcon = nullptr;

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

void RemoteServer::initializeTrayIcon() {
    QMenu *menu = new QMenu(this);
    menu->addAction(tr("&Exit"), qApp, SLOT(quit()));
    if(trayIcon == nullptr) {
        trayIcon = new QSystemTrayIcon(this);
        setIcon("black");
        trayIcon->setVisible(true);
    }
    trayIcon->setContextMenu(menu);
    trayIcon->show();

}

void RemoteServer::setIcon(QString name) {
    trayIcon->setIcon(QIcon(":/" + name));
}

/*
 * incoming data on udp can be connection request
 * or transmission request
 *
 */
void RemoteServer::incomingUdpData() {
    if(tcpSocket == nullptr)
        connectionRequest();
    else {
        incomingMouse();
    }
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
    QByteArray datagram = tcpSocket->readAll();

    QDataStream streamIn(&datagram, QIODevice::ReadOnly);
    quint8 mode1;

    streamIn >> mode1;

    switch(mode1) {
    case 1:
        incomingKey(datagram);
        break;
    default:
        ;
    }
}

void RemoteServer::deleteConnection() {
    if(tcpSocket == nullptr)
        return;

    tcpSocket->deleteLater();
    tcpSocket = nullptr;
    setIcon("black");
}

void RemoteServer::socketConnected() {
    setIcon("green");
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(transmissionRequest()));
}

void RemoteServer::incomingKey(QByteArray data) {
    quint8 mode1;
    quint32 key, modifiers;
    bool keyPressed;

    QDataStream streamIn(&data, QIODevice::ReadOnly);
    streamIn >> mode1;
    streamIn >> key;
    streamIn >> modifiers;
    streamIn >> keyPressed;

    GlobalFakeKey fakeKey;
    fakeKey.sendModifiers((Qt::KeyboardModifier)modifiers, keyPressed);
    fakeKey.sendKey((Qt::Key)key, keyPressed);
}

void RemoteServer::incomingMouse() {
    QByteArray datagram;
    QHostAddress addr;
    datagram.resize(udpSocket->pendingDatagramSize());

    udpSocket->readDatagram(datagram.data(), datagram.size(), &addr);

    if(addr != tcpSocket->peerAddress())
        return;

    QDataStream streamIn(&datagram, QIODevice::ReadOnly);
    quint8 mode1;
    quint8 mode2;

    streamIn >> mode1;
    streamIn >> mode2;

    if(mode1 == 2 && mode2 == 0) {
        mouseMove(datagram);
    } else if( mode1 ==2 && mode2 == 1) {
        mouseClick(datagram);
    }

}

void RemoteServer::mouseMove(QByteArray data) {
    QDataStream streamIn(&data, QIODevice::ReadOnly);
    quint8 mode1;
    quint8 mode2;
    QPointF delta;

    streamIn >> mode1;
    streamIn >> mode2;
    streamIn >> delta;

    double x = delta.x();
    double y = delta.y();

    if(QCursor::pos() != QPoint(qRound(cursorPos.x()), qRound(cursorPos.y())))
        cursorPos = QCursor::pos();

    cursorPos.setX(cursorPos.x() + x);
    cursorPos.setY(cursorPos.y() + y);

    QCursor::setPos(QPoint(qRound(cursorPos.x()),qRound(cursorPos.y())));
}

void RemoteServer::mouseClick(QByteArray data) {
    QDataStream streamIn(&data, QIODevice::ReadOnly);

    quint8 mode1;
    quint8 mode2;
    quint8 key;
    bool keyPressed;

    streamIn >> mode1;
    streamIn >> mode2;
    streamIn >> key;
    streamIn >> keyPressed;

    Qt::MouseButton mouseButton = Qt::NoButton;

    if(key == 1)
        mouseButton = Qt::LeftButton;
    else if(key == 2)
        mouseButton = Qt::RightButton;

    GlobalFakeKey fakeKey;
    fakeKey.sendButton(mouseButton, keyPressed);

}
