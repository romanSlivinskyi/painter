#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>


class client : public QObject
{
    Q_OBJECT

    enum class Packet { Name, Message };
public:
    client(const QString& hostName, quint16 port)
    {
         server_ = new QTcpSocket(this);
         server_->connectToHost(hostName, port);

         connect(server_, SIGNAL(connected()), this, SLOT(slot_connected()));
         connect(server_, SIGNAL(readyRead()), this, SLOT(read_server()));
         connect(server_, SIGNAL(error(QAbstractSocket::SocketError)), this,
                 SLOT(slot_error(QAbstractSocket::SocketError err)));
    }

    void send_str(Packet packet, const QString& str)
    {
        // << message size << str
        QByteArray arr;
        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out << qint16(0) << (int)packet << str;
        out.device()->seek(0);
        out << (qint16)(arr.size() - sizeof(qint16));

        server_->write(arr);
    }

private:
    QTcpSocket *server_;
    QString name = "Client 1";

signals:
    void new_connection(QString name);
    void new_message(QString msg);

public slots:
    void slot_connected()
    {
        send_str(Packet::Name, name);
    }
    void slot_error(QAbstractSocket::SocketError err)
    {
        QMessageBox::critical(0, "Client error", "Start fail", "Error with server");
        server_->close();
        return;
    }

    void read_server()
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
                    break;
                }
                case Packet::Message:
                {
                    emit new_message(str);
                    break;
                }
                default:
                    break;
            }
        }
    }
};

#endif // CLIENT_H
