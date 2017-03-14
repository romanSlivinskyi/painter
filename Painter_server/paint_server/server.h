#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include <vector>
#include <map>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <QRectF>

struct shape_info
{
    int     online_id { -1 } ;
    QRectF  rect_     { QRectF(0,0,0,0) };
    QPen    pen_      { Qt::transparent };
    QBrush  brush_    { Qt::transparent };

    //....BAD
    QString text { "" };
    QVector<QRectF> pen_vec;
    //.......

    friend bool operator==(const shape_info& lhs, const shape_info& rhs)
    {
        return
        lhs.rect_  == rhs.rect_ &&
        lhs.pen_   == rhs.pen_ &&
        lhs.brush_ == rhs.brush_;
    }
};

class shape_t
{
    public: enum class type{none = 0, line, rect, ellipse, pen, text};
};

struct packet
{
    //.............................
    shape_t::type shape_type;
    shape_info    shape_inf;
    //.............................
    QByteArray to_byte_array() const
    {
        QByteArray arr;
        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out << qint16(0)
            << shape_inf.online_id
            << (int)shape_type
            << shape_inf.rect_
            << shape_inf.pen_
            << shape_inf.brush_
            << shape_inf.text
            << shape_inf.pen_vec;
        out.device()->seek(0);
        out << (qint16)(arr.size() - sizeof(qint16));
        return arr;
    }
    QString to_string() const
    {
         return QString("[ id : "+QString::number(shape_inf.online_id)+" type : "+QString::number((int)shape_type)+" ]");
    }
};

class server : public QObject
{
    Q_OBJECT
public:
    server(int port);
    void send_packet(packet pack, QTcpSocket* soc_sender);

public:
    std::map<int, QTcpSocket*> users_map_;
    //std::vector<int> offline_users_;
    QTcpServer*                pserver_;
    int                        clients_count   { 0 };
    int                        online_shape_id_ { 0 };

public slots:
    void new_connection();
    void slot_user_disconnected()
    {
        QTcpSocket* curr_client = (QTcpSocket*)sender();
        for(auto& row : users_map_)
        {
            if(row.second == curr_client)
            {
                users_map_[row.first] = nullptr;
                emit signal_user_disconnected(row.first);
            }
        }
        curr_client->deleteLater();
    }
    void read_client();

    //from out
    void slot_user_to_disconnect(int id)
    {
        users_map_[id]->deleteLater();
        users_map_[id] = nullptr;
    }

signals:
    void signal_new_user(int);
    void signal_user_disconnected(int);
};
#endif // SERVER_H
