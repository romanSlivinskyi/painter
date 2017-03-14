#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QTime>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include <vector>

enum class Packet { Name, Message };

class server : public QObject
{
    Q_OBJECT

public:
    server(int port) : port_(port)
    {
        pserver_ = new QTcpServer(this);
        if(!pserver_->listen(QHostAddress::Any, port_))
        {
            QMessageBox::critical(0, "Server error", "Start fail", pserver_->errorString());
            pserver_->close();
            return;
        }
        connect(pserver_, SIGNAL(newConnection()), this, SLOT(new_connection()));
    };

    void send_str(Packet packet, const QString& str, QTcpSocket *client = nullptr)
    {
        // << message size << str
        QByteArray arr;
        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out << qint16(0) << (int)packet << str;
        out.device()->seek(0);
        out << (qint16)(arr.size() - sizeof(qint16));

        if(client == nullptr)
            for(auto c: vclients_)
                c->write(arr);
        else
            client->write(arr);
    }

private:
    QTcpServer *pserver_;
    std::vector<QTcpSocket*> vclients_;
    int port_;

signals:
    void new_connection(QString name);
    void new_message(QString msg);

public slots:
    void new_connection()
    {
        QTcpSocket *client = pserver_->nextPendingConnection();
        vclients_.push_back(client);
        connect(client, SIGNAL(disconnected), client, SLOT(deleteLater()));
        connect(client, SIGNAL(readyRead()), this, SLOT(read_client()));
    }
    void read_client()
    {
        QTcpSocket* client = (QTcpSocket*)sender();
        QDataStream in(client);
        in.setVersion(QDataStream::Qt_5_7);

        qint16 next_block_size = 0;
        for(;;)
        {
            if(!next_block_size)
                if(client->bytesAvailable() < sizeof(qint16))
                    break;
            in >> next_block_size;

            if(client->bytesAvailable() < next_block_size)
                break;

            int packet;
            QString str;
            in >> packet >> str;

            switch ((Packet)packet)
            {
                case Packet::Name:
                {
                    emit new_connection(str);
                    send_str(Packet::Name, str); // to all
                    break;
                }
                case Packet::Message:
                {
                    emit new_message(str);
                    send_str(Packet::Message, str); // to all
                    break;
                }
                default:
                    break;
            }
        }
    }
    void send_message(QString str)
    {
        send_str(Packet::Message, str);
    }
};

#endif // SERVER_H






































