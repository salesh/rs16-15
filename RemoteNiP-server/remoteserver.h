#ifndef REMOTESERVER_H
#define REMOTESERVER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QStyle>
#include <QDesktopWidget>

namespace Ui {
class RemoteServer;
}

class RemoteServer : public QMainWindow {
    Q_OBJECT

public:
    explicit RemoteServer(QWidget *parent = 0);
    ~RemoteServer();

    void initializeTrayIcon();

private:
    Ui::RemoteServer *ui;
    QUdpSocket *udpSocket;  // for establishing communication
    QTcpSocket *tcpSocket;  // for communication

    QSystemTrayIcon *trayIcon;

    void connectionRequest();
    void transmissionRequest();
    void setIcon(QString name);

private slots:  
    void incomingUdpData();
    void deleteConnection();
    void socketConnected();
};

#endif // REMOTESERVER_H
