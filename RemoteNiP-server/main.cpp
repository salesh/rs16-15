#include "remoteserver.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    RemoteServer w;
    w.initializeTrayIcon();

    return a.exec();
}
