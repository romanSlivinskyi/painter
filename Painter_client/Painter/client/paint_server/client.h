#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include <vector>
#include <map>

enum class packet_type { name, message };
struct packet
{
    int          size;
    QString      from;
    QString      to;
    packet_type  type;
    QString      data;
};
struct mess_info
{
    QString from;
    QString mess;
};

class client : public QObject
{
    Q_OBJECT

public:
             client      (const QString& hostName, const QString& name, quint16 port);
    void     send_packet (packet pack);
    QString  get_name    ()                                      const;

private:
    QTcpSocket*                             server_;
    QString                                 name_  ;
public:
    std::map<QString, std::vector<mess_info>> dialog_data_;
    std::vector<QString> vec_names_;

signals:
    void signal_new_user_online (QString name);
    void signal_new_message     (QString from, QString msg);

public slots:
    void slot_connected     ();
    void slot_error         (QAbstractSocket::SocketError err);
    void slot_read_server   ();
    void slot_send_message  (QString to, QString data);

};

#endif // CLIENT_H
