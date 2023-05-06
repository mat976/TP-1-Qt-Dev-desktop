#include "indexingclient.h"

#include <QTcpSocket>

IndexingClient::IndexingClient(QObject *parent) : QObject(parent), m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::connected, this, &IndexingClient::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &IndexingClient::onDisconnected);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(m_socket, &QTcpSocket::readyRead, this, &IndexingClient::onDataReceived);
}
void IndexingClient::setSocket(QTcpSocket* socket)
{
    m_socket = socket;
    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onDataReceived()));
}



void IndexingClient::setServerAddress(const QString &address)
{
    m_serverAddress = address;
}

void IndexingClient::setServerPort(int port)
{
    m_serverPort = port;
}

void IndexingClient::connectToServer()
{
    m_socket->connectToHost(m_serverAddress, m_serverPort);
}

void IndexingClient::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

void IndexingClient::sendSearchRequest(const QString &searchString, const QString &lastModified, const QString &created, const QString &maxSize, const QString &minSize, const QString &sizeRange, const QString &extensions, const QString &types)
{
    // TODO: implement search request
}

void IndexingClient::onConnected()
{
    emit connected();
}

void IndexingClient::onDisconnected()
{
    emit disconnected();
}

void IndexingClient::onError(QAbstractSocket::SocketError socketError)
{
    emit errorOccurred(m_socket->errorString());
}

void IndexingClient::onDataReceived()
{
    // TODO: implement data received handling
}
