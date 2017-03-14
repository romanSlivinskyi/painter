#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui { class main_window; }

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();

private slots:
    void on_button_connect_clicked();
    void on_putton_send_clicked();

    void on_dialog_users_list_currentRowChanged(int currentRow);

private:
    Ui::main_window* ui;
    client*          client_;

signals:
    void signal_send_message(QString to,QString msg);

public slots:
    void slot_new_message(QString to, QString msg);
    void slot_new_user_online(QString name);
};

#endif // MAIN_WINDOW_H
