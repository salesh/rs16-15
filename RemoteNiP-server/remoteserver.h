#ifndef REMOTESERVER_H
#define REMOTESERVER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMessageBox>

namespace Ui {
class RemoteServer;
}

class RemoteServer : public QMainWindow {
    Q_OBJECT

public:
    explicit RemoteServer(QWidget *parent = 0);
    ~RemoteServer();

private:
    Ui::RemoteServer *ui;
    QUdpSocket *udpSocket;  // for establishing communication
    QTcpSocket *tcpSocket;  // for communication

    void connectionRequest();
    void transmissionRequest();

private slots:
    void incomingUdpData();
    void deleteConnection();
    void socketConnected();
};

#endif // REMOTESERVER_H
