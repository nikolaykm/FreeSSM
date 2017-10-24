#ifndef MBSSWSLISTENERS_H
#define MBSSWSLISTENERS_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>


class MBsSWsListeners : public QObject
{   
    Q_OBJECT

public:
    MBsSWsListeners();
    virtual ~MBsSWsListeners();

    void publishData(const std::string& data);

private slots:
    void acceptNewConnection();
    void clientDisconnected();

private:
    QTcpServer* _tcpServer;
    QTcpSocket* _OpenSocket;
    QMutex _OpenSocketMutex;
};

#endif // MBSSWSLISTENERS_H
