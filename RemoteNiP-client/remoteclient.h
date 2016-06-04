#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QtNetwork>

namespace Ui {
class RemoteClient;
}

class RemoteClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemoteClient(QWidget *parent = 0);
    ~RemoteClient();

    typedef struct{
        QHostAddress hostAddress;
        QString hostName;
        bool connected;
    }QRCServer;

private:
    Ui::RemoteClient *ui;
    QUdpSocket *udpSocket;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    bool shiftIndicator=false;
    bool altIndicator=false;
    bool ctrlIndicator=false;

    QHostAddress    m_hostAddress;

private slots:
    void sendConnectionRequest();
    void newConnection();
    void deleteConnection();
    void incomingUdpData();
    void initialize();
    void newUi();
    void keyboardPressed();
    void keyboardReleased();
    void shiftButtonIndicator();
    void altButtonIndicator();
    void ctrlButtonIndicator();
};

#endif // REMOTECLIENT_H
