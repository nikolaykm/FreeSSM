#include "MBsSWsListeners.h"

MBsSWsListeners::MBsSWsListeners()
{    
    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen(QHostAddress::Any, 12345))
    {
        qWarning((tr("FreeSSM MBsSWs Listeners Server. Unable to start the server: %1.").arg(tcpServer->errorString())).toLatin1());
    }
    else
    {
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptNewConnection()));
    }
}

MBsSWsListeners::~MBsSWsListeners()
{
    tcpServer->close();
    delete tcpServer;
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

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    _OpenSockets.push_back(clientConnection);
}

void MBsSWsListeners::publishData(const std::string& data)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_0);
    //out << (quint16)0;
    out << data.c_str();
    //out.device()->seek(0);
    //out << (quint16)(block.size() - sizeof(quint16));

    for (int i = 0; i < _OpenSockets.size(); i++)
    {
        _OpenSockets[i]->write(block);
    }
}
