#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include <vector>
#include <map>
#include "shape_t.h"

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

class client : public QObject
{
    Q_OBJECT

public:
             client      (const QString& hostName, quint16 port);
    void     send_packet (packet pack);

private:
    QTcpSocket* server_;


signals:
    void signal_new_paint_command(shape_t::type t, shape_info inf);

public slots:
    void slot_connected     ();
    void slot_error         (QAbstractSocket::SocketError err);
    void slot_read_server   ();
    void slot_send_paint_command(shape_t::type t, shape_info inf);
};

#endif // CLIENT_H
