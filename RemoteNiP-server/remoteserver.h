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
    QPointF cursorPos;
    QSystemTrayIcon *trayIcon;

    void connectionRequest();
    void setIcon(QString name);
    void incomingKey(QByteArray data);
    void incomingMouse();
    void mouseMove(QByteArray data);
    void mouseClick(QByteArray data);

private slots:
    void transmissionRequest();
    void incomingUdpData();
    void deleteConnection();
    void socketConnected();
};

#endif // REMOTESERVER_H
