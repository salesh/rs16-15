#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include <QMainWindow>

namespace Ui {
class RemoteClient;
}

class RemoteClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemoteClient(QWidget *parent = 0);
    ~RemoteClient();

private:
    Ui::RemoteClient *ui;
};

#endif // REMOTECLIENT_H
