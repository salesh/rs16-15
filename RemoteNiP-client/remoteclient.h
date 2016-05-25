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
    QNetworkSession *session;
    QNetworkConfigurationManager *netConfigManager;
    QTimer     *netConfigTimer;
    QTimer     *networkTimeoutTimer;
    QTimer     *broadcastTimer;
    QTimer     *connectionRequestTimer;

    QList<QRCServer> serverList;

    void addServer(QHostAddress hostAddress,bool connected);

    QString         m_hostname;
    QHostAddress    m_hostAddress;
    int             m_networkTimeout;
    QString         m_emptyString;

private slots:
    void sendConnectionRequest();
// no need for this yet
//    void newConnection();
//    void deleteConnection();
//    void incomingData();
//    void incomingUdpData();
//    void updateNetConfig();
    void initialize();
    void on_searchButton_clicked();
    void on_chooseNetworkButton_clicked();
};

#endif // REMOTECLIENT_H
