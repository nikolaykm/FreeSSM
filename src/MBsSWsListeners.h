#ifndef MBSSWSLISTENERS_H
#define MBSSWSLISTENERS_H

#include<QTcpServer>
#include <QTcpSocket>


class MBsSWsListeners : public QObject
{   
    Q_OBJECT

public:
    MBsSWsListeners();
    virtual ~MBsSWsListeners();

    void publishData(const std::string& data);

private slots:
    void acceptNewConnection();

private:
    QTcpServer *tcpServer;
    std::vector<QTcpSocket*> _OpenSockets;
};

#endif // MBSSWSLISTENERS_H
