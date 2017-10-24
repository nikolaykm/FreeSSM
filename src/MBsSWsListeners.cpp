#include "MBsSWsListeners.h"

MBsSWsListeners::MBsSWsListeners()
{    
    _tcpServer = new QTcpServer(this);

    if (!_tcpServer->listen(QHostAddress::Any, 12345))
    {
        qWarning((tr("FreeSSM MBsSWs Listeners Server. Unable to start the server: %1.").arg(_tcpServer->errorString())).toLatin1());
    }
    else
    {
        connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(acceptNewConnection()));
    }

    _OpenSocket = NULL;
}

MBsSWsListeners::~MBsSWsListeners()
{
    _tcpServer->close();
    delete _tcpServer;
}

void MBsSWsListeners::acceptNewConnection()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << "Nice. You are connected. Now wait...";
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QTcpSocket *clientConnection = _tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    connect(clientConnection, SIGNAL(disconnected()),
            this, SLOT(clientDisconnected()));

    _OpenSocketMutex.lock();
    _OpenSocket = clientConnection;
    _OpenSocketMutex.unlock();
}

void MBsSWsListeners::publishData(const std::string& data)
{
    _OpenSocketMutex.lock();
    if (_OpenSocket != NULL)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        //out.setVersion(QDataStream::Qt_4_0);
        //out << (quint16)0;
        out << data.c_str();
        //out.device()->seek(0);
        //out << (quint16)(block.size() - sizeof(quint16));

        _OpenSocket->write(block);
    }
    _OpenSocketMutex.unlock();
}

void MBsSWsListeners::clientDisconnected()
{
    _OpenSocketMutex.lock();
    delete _OpenSocket;
    _OpenSocket = NULL;
    _OpenSocketMutex.unlock();    
}
