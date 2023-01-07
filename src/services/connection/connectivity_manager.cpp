#include "connectivity_manager.h"
#include <QTcpSocket>
#include <QSqlQuery>

ConnectivityManager::ConnectivityManager(const QSqlDatabase& database, QObject* parent)
        : QObject(parent), database(database) {
    // Move the ConnectivityManager to a new thread
    moveToThread(&thread);
    connect(&thread, SIGNAL(started()), this, SLOT(started()));
    thread.start();
}

bool ConnectivityManager::internetConnection() {
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

ConnectivityManager::~ConnectivityManager() {
    // Stop the timer and the thread
    killTimer(timerId);
    thread.quit();
    thread.wait();
}

void ConnectivityManager::timerEvent(QTimerEvent*) {
    // Open a connection to the database if it's not already open
    if (!database.isOpen())
        database.open();

    // Ping the database to keep the connection open
    database.exec("SELECT 1");
    qInfo() << "Ping database connection";
}

void ConnectivityManager::started() {
    timerId = startTimer(ONE_MINUTE);
}
