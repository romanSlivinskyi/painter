#include "client.h"


client::client(const QString &hostName,const QString& name, quint16 port)
    : name_(name)
{
    server_ = new QTcpSocket(this);
    server_->connectToHost(hostName, port);

    connect(server_, SIGNAL(connected()), this, SLOT(slot_connected()));
    connect(server_, SIGNAL(readyRead()), this, SLOT(slot_read_server()));
    connect(server_, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(slot_error(QAbstractSocket::SocketError err)));


    //
    //
//    dialog_data_["Main :chat"].push_back({"Main :chat","Hello main chat"});
//    dialog_data_["Roman"].push_back({"Roman","ello Roman"});
//    dialog_data_["Scott"].push_back({"Scott","hello Scott"});
}

void client::send_packet(packet pack)
{
    // << message size << packet << destination << str
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << qint16(0)
        << pack.from
        << pack.to
        << (int)pack.type
        << pack.data;
    out.device()->seek(0);
    out << (qint16)(arr.size() - sizeof(qint16));
    qDebug() << "write";
    server_->write(arr);
}

QString client::get_name() const
{
    return name_;
}

void client::slot_connected()
{
    packet pack
    {
        0, name_, "all", packet_type::name, name_
    };
    send_packet(pack);
}

void client::slot_error(QAbstractSocket::SocketError err)
{
    QMessageBox::critical(0, "Client error", "Start fail", "Error with server");
    server_->close();
    return;
}

void client::slot_read_server()
{
    QTcpSocket* server = (QTcpSocket*)sender();
    QDataStream in(server);
    in.setVersion(QDataStream::Qt_5_7);
    qint16 next_block_size = 0;
    for(;;)
    {
        if(!next_block_size)
        {
            if(server->bytesAvailable() < sizeof(qint16))
                break;
            in >> next_block_size;
        }
        if(server->bytesAvailable() < next_block_size)
            break;

        packet pack;
        int type;
        in >> pack.from >> pack.to >> type >> pack.data;
        pack.type = (packet_type)type;

        switch (pack.type)
        {
            case packet_type::name:
            {
                vec_names_.push_back(pack.data); qDebug() << "READ NAME!!!" << pack.data;
                emit signal_new_user_online(pack.data);
                break;
            }
            case packet_type::message:
            {
                dialog_data_[pack.from].push_back({ pack.from, pack.data });
                emit signal_new_message(pack.from, pack.data);
                break;
            }
            default:
                break;
            }
    }
}

void client::slot_send_message(QString to, QString data)
{
    packet pack
    {
        0, name_, to, packet_type::message, data
    };
    qDebug() << name_ << " - " << to << " - " << (int)packet_type::message << " - "  << data;

    //add to local info
    dialog_data_[to].push_back({ name_, data });

    send_packet(pack);

    //
    //
//    emit signal_new_user_online("Harry");
//    emit signal_new_message("Harry", "Hello");
//    emit signal_new_message("Roman", "Hello");
}
