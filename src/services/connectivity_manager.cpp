#include "connectivity_manager.h"
#include <QTcpSocket>

bool ConnectivityManager::checkConnection() {
    QTcpSocket* sock = new QTcpSocket();
    sock->connectToHost("129.152.21.9", 5432);
    bool connected = sock->waitForConnected(2000);//ms

    if (!connected) {
        sock->abort();
        return false;
    }
    sock->close();
    return true;
}
