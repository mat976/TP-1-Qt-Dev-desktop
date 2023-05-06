#include "server.h"

#include <QTcpSocket>
#include "indexingclient.h"

void Server::start(int port) {
    if (!listen(QHostAddress::Any, port)) {
        qWarning() << "Unable to start server: " << errorString();
    } else {
        qDebug() << "Server started on port " << port;
    }
}

void Server::incomingConnection(qintptr handle) {
    IndexingClient* client = new IndexingClient(this);
    QTcpSocket* socket = new QTcpSocket(client);
    socket->setSocketDescriptor(handle);
    client->setSocket(socket);
    qDebug() << "New client connected";
}


