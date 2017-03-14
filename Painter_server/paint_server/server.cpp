#include "server.h"

server::server(int port)
{
    pserver_ = new QTcpServer(this);
    if(!pserver_->listen(QHostAddress::Any, port))
    {
        QMessageBox::critical(0, "Server error", "Start fail", pserver_->errorString());
        pserver_->close();
        return;
    }
    connect(pserver_, SIGNAL(newConnection()), this, SLOT(new_connection()));
}

void server::send_packet(packet pack, QTcpSocket* soc_sender = nullptr)
{
    QByteArray arr = pack.to_byte_array();
    //send to all with new online id
    for(auto& row : users_map_)
    {
        if(row.second != soc_sender && row.second != nullptr)
        {
            qDebug() << "SEND : " << pack.to_string() <<  " [ " << pack.shape_inf.rect_ << " ] " << " -> " << row.first;
            row.second->write(arr);
        }
    }
}

void server::new_connection()
{
    QTcpSocket *client = pserver_->nextPendingConnection();

    users_map_[clients_count] = client;
    ++clients_count;

    connect(client, SIGNAL(disconnected()), this, SLOT(slot_user_disconnected()));
    connect(client, SIGNAL(readyRead()), this, SLOT(read_client()));
    qDebug() << "Connected id : " << clients_count-1;
    emit signal_new_user(clients_count-1);
}

void server::read_client()
{
    QTcpSocket* curr_client = (QTcpSocket*)sender();
    QDataStream in(curr_client);
    in.setVersion(QDataStream::Qt_5_7);
    qint16 next_block_size = 0;

    for(;;) {
        if(!next_block_size){
            if(curr_client->bytesAvailable() < sizeof(qint16)) break;
            in >> next_block_size;
        }
        if(curr_client->bytesAvailable() < next_block_size) break;

        //read packet
        packet pack;
        int s_type;
        in>> pack.shape_inf.online_id >> s_type >> pack.shape_inf.rect_ >> pack.shape_inf.pen_
                >> pack.shape_inf.brush_  >> pack.shape_inf.text >> pack.shape_inf.pen_vec;
        pack.shape_type = (shape_t::type)s_type;
        qDebug() << "RECV : " << pack.to_string() <<  " [ " << pack.shape_inf.rect_ << " ] ";

        if(pack.shape_inf.online_id == -1)
        {
            //set new online id
            pack.shape_inf.online_id = online_shape_id_;
            ++online_shape_id_;
            send_packet(pack); //to all
        }
        else
            send_packet(pack, curr_client); //to all minus curr

    }
}
