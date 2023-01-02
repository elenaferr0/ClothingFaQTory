

#ifndef CONNECTIVITY_MANAGER_H
#define CONNECTIVITY_MANAGER_H


#include <QObject>
#include <QTimer>
#include <QSqlDatabase>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Connection { class ConnectivityManager; }
QT_END_NAMESPACE

class ConnectivityManager : public QObject {
    Q_OBJECT
    public:
        ConnectivityManager(const QSqlDatabase& database, QObject* parent = nullptr);

        static bool internetConnection();

        ~ConnectivityManager();

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        QThread thread;
        QSqlDatabase database;
        int timerId;
        static const int ONE_MINUTE = 60 * 1000;
    private slots:

        void started();

};

#endif //CONNECTIVITY_MANAGER_H
