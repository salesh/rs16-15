#include "remoteclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteClient w;
    w.show();

    return a.exec();
}
