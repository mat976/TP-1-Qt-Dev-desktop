#ifndef INDEXINGCLIENT_H
#define INDEXINGCLIENT_H

#include <QObject>
#include <QTcpSocket>

class IndexingClient : public QObject
{
    Q_OBJECT
public:
    explicit IndexingClient(QObject *parent = nullptr);
    void setServerAddress(const QString& address);
    void setServerPort(int port);
    void connectToServer();
    void disconnectFromServer();
    void sendSearchRequest(const QString& searchString, const QString& lastModified,
                            const QString& created, const QString& maxSize, const QString& minSize,
                            const QString& sizeRange, const QString& extensions, const QString& types);
    void setSocketDescriptor(qintptr handle);
    void setSocket(QTcpSocket* socket);
signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
    void searchResultReceived(const QList<QList<QVariant>>& result);

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onDataReceived();

private:
    QTcpSocket* m_socket;
    QString m_serverAddress;
    int m_serverPort;
};

#endif // INDEXINGCLIENT_H
