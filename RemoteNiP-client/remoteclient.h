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

public slots:
    void abortBroadcasting();
    void abortConnectionRequest();
    void clearServerList();

    QString hostName() const{
        return m_hostname;
    }

    int port() const{
        return m_port;
    }

    QHostAddress hostAddress() const{
        return m_hostAddress;
    }

    int networkTimeout() const{
        return m_networkTimeout;
    }

    QString getEmptyString() const{
        return m_emptyString;
    }

public slots:
    void setHostname(QString arg)
    {
        if (m_hostname != arg) {
            m_hostname = arg;
            emit hostnameChanged(arg);
        }

        QHostAddress hostAddress;
        if (!m_hostname.isEmpty())
            hostAddress.setAddress(m_hostname);
        else
            hostAddress = QHostAddress::Broadcast;

        setHostAddress(hostAddress);
    }

    void setHostAddress(QHostAddress arg)
    {
        if (m_hostAddress != arg) {
            m_hostAddress = arg;

            m_hostname = m_hostAddress.toString();
            emit hostAddressChanged(arg);
            emit hostnameChanged(m_hostname);
        }
    }

    void setPort(int arg)
    {
        if (m_port != arg) {
            m_port = arg;
            emit portChanged(arg);
        }
    }

    void setNetworkTimeout(int arg)
    {
        if (m_networkTimeout != arg) {
            m_networkTimeout = arg;
            emit networkTimeoutChanged(arg);
        }
    }

signals:
    void hostnameChanged(QString arg);
    void hostAddressChanged(QHostAddress arg);
    void portChanged(int arg);
    void connected();
    void disconnected();
    void broadcastingStarted();
    void connectingStarted();
    void serverConnecting();
    void networkTimeoutChanged(int arg);
    void emptyStringChanged(QString arg);
    void serversCleared();
    void serverFound(QString address, QString hostName, bool connected);


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
    int             m_port;
    QHostAddress    m_hostAddress;
    int             m_networkTimeout;
    QString         m_emptyString;

private slots:
    void sendConnectionRequest();
    void sendBroadcast();
    void newConnection();
    void deleteConnection();
    void incomingData();
    void incomingUdpData();
    void updateNetConfig();
    void initialize();
    void on_searchButton_clicked();
};

#endif // REMOTECLIENT_H
