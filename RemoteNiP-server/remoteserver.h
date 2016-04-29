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
    QUdpSocket *_udp_socket;  // for establishing communication
    QTcpSocket *_tcp_socket;  // for communication

    void connection_request();
    void transmission_request();

private slots:
    void incoming_udp_data();
    void delete_connection();
    void socket_connected();
};

#endif // REMOTESERVER_H
