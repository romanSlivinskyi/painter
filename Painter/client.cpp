#include "client.h"


client::client(const QString &hostName, quint16 port)
{
    server_ = new QTcpSocket(this);
    server_->connectToHost(hostName, port);

    connect(server_, SIGNAL(connected()), this, SLOT(slot_connected()));
    connect(server_, SIGNAL(readyRead()), this, SLOT(slot_read_server()));
    connect(server_, SIGNAL(error(QAbstractSocket::SocketError)),
            this,    SLOT(slot_error(QAbstractSocket::SocketError)));
}

void client::send_packet(packet pack)
{
    qDebug() << "SEND: " << pack.to_string() <<  " [ " << pack.shape_inf.rect_ << " ] ";
    QByteArray arr = pack.to_byte_array();
    server_->write(arr);
}

void client::slot_connected()
{
    qDebug("connected");
}

void client::slot_error(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err);
    QMessageBox::critical(0, "Connection error", "Can not connect to server", "OK");
    server_->close();
    return;
}

void client::slot_read_server()
{
    QTcpSocket* server = (QTcpSocket*)sender();
    QDataStream in(server);
    in.setVersion(QDataStream::Qt_5_7);
    qint16 next_block_size = 0;
    for(;;){
        if(!next_block_size){
            if(server->bytesAvailable() < sizeof(qint16)) break;
            in >> next_block_size;
        }
        if(server->bytesAvailable() < next_block_size) break;

        packet pack;
        int s_type;
        in >> pack.shape_inf.online_id >> s_type >> pack.shape_inf.rect_ >> pack.shape_inf.pen_
           >> pack.shape_inf.brush_ >> pack.shape_inf.text >> pack.shape_inf.pen_vec;
        pack.shape_type = (shape_t::type)s_type;

        qDebug() << "RECV: " << pack.to_string() <<  " [ " << pack.shape_inf.rect_ << " ] ";
        emit signal_new_paint_command(pack.shape_type, pack.shape_inf);
    }
}
void client::slot_send_paint_command(shape_t::type type, shape_info inf)
{
    packet pack {type, inf};
    send_packet(pack);
}

