#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer {
public:
    void start(int port);
protected:
    void incomingConnection(qintptr handle) override;
};

#endif // SERVER_H
