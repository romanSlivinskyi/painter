#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "server.h"

namespace Ui { class main_window; }

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();

private slots:
    void on_button_start_clicked();
    void on_button_stop_clicked();

    void on_button_disconnect_clicked();

private:
    Ui::main_window *ui;
    server *server_;

public slots:
    void slot_new_user_online(int id);
    void slot_user_disconnected(int id);

signals:
    void user_to_disconnect(int id);
};

#endif // MAIN_WINDOW_H
