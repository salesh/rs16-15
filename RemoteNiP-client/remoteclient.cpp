#include "remoteclient.h"
#include "ui_remoteclient.h"

RemoteClient::RemoteClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteClient){
    ui->setupUi(this);

    m_emptyString = "";

    tcpSocket = NULL;

    tcpServer = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);
    connectionRequestTimer = new QTimer(this);

//  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(connectionRequestTimer, SIGNAL(timeout()), this, SLOT(sendConnectionRequest()));

}


RemoteClient::~RemoteClient(){
    delete ui;
}


void RemoteClient::on_searchButton_clicked(){
    initialize();
}

void RemoteClient::initialize(){
    tcpServer->close();
    tcpServer->listen(QHostAddress::LocalHost, 5600);

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                ui->chooseNetworkComboBox->addItem(ipAddress);
                break;
            }
        }



    udpSocket->close();
    connect(udpSocket, SIGNAL(readyRead()),this,SLOT(incomingUdpData()));
    udpSocket->bind(5600,QUdpSocket::DontShareAddress | QUdpSocket::ReuseAddressHint);
}

void RemoteClient::on_chooseNetworkButton_clicked(){
    m_hostAddress.setAddress(ui->chooseNetworkComboBox->currentText());
    sendConnectionRequest();
}

void RemoteClient::sendConnectionRequest(){
    QByteArray datagram = "NiP:Hello";

    udpSocket->writeDatagram(datagram, m_hostAddress, 5600);
}

 //No need for this yet(sync with server)

/*
void RemoteClient::newConnection(){
    if (!tcpSocket) {
        tcpSocket = tcpServer->nextPendingConnection();

        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(deleteConnection()));
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(incomingData()));

        abortConnectionRequest();

        networkTimeoutTimer->start();
    }
}

void RemoteClient::incomingUdpData(){
    QHostAddress hostAddress;
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());

    udpSocket->readDatagram(datagram.data(), datagram.size(), &hostAddress);

    const QString magicMessageConnected = "NiP:Connected";
    const QString magicMessageNotConnected = "NiP:NotConnected";
    const QString magicMessageServerConnecting = "NiP:Connecting";

    if (datagram == magicMessageConnected){
        addServer(hostAddress, true);
    }
    else if (datagram == magicMessageNotConnected){
        addServer(hostAddress, false);
    }
    else if (datagram == magicMessageServerConnecting){

    }
}

void RemoteClient::abortConnectionRequest(){
    connectionRequestTimer->stop();
}

void RemoteClient::addServer(QHostAddress hostAddress, bool connected){
    bool found = false;
    for (int i = 0; i < serverList.size(); i++){
        if (serverList.at(i).hostAddress == hostAddress) {
            found = true;
            serverList[i].connected = connected;
            break;
        }
    }
    if (!found){
        QRCServer qrcServer;
        qrcServer.hostAddress = hostAddress;
        qrcServer.hostName = hostAddress.toString();
        qrcServer.connected = connected;
        serverList.append(qrcServer);

        QHostInfo::lookupHost(hostAddress.toString(),
                               this, SLOT(saveResolvedHostName(QHostInfo)));
    }


//    for (int i = 0; i < serverList.size(); i++){
//        emit serverFound(serverList.at(i).hostAddress.toString(),
//                         serverList.at(i).hostName,
//                         serverList.at(i).connected);
//    }
}

void RemoteClient::clearServerList(){
    serverList.clear();
}


void RemoteClient::incomingData(){
    QByteArray data = tcpSocket->readAll();
   // int type = data.left(1).toInt();

    int payloadsize = data.mid(1,10).toInt();   //getting the size of the whole payload
                    data = data.mid(11);                        //removing obsolete data
                    while (data.size() != payloadsize) {        //wait for the missing data
                        tcpSocket->waitForReadyRead();
                        data.append(tcpSocket->readAll());
                    }

//    switch (type) {
//        case 1: incomingIcon(data);                         //process the data
//                break;
//        case 2: incomingAmarokData(data);
//                break;
//    }

}

void RemoteClient::deleteConnection(){
    tcpSocket->abort();
    tcpSocket->deleteLater();
    tcpSocket = NULL;

    networkTimeoutTimer->stop();
}

void RemoteClient::updateNetConfig(){
    if ((session == NULL) || (!session->isOpen()))
    {
        netConfigManager->updateConfigurations();
    }
}

*/
