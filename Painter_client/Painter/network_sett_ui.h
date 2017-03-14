#ifndef NETWORK_SETT_UI_H
#define NETWORK_SETT_UI_H

#include <QDialog>
#include "client.h"

namespace Ui {
class network_sett_ui;
}

class network_sett_ui : public QDialog
{
    Q_OBJECT

public:
    explicit network_sett_ui(QWidget *parent = 0);
    ~network_sett_ui();

private slots:
    void on_connect_button_accepted();

private:
    Ui::network_sett_ui *ui;

signals:
    void settings_info(QString ip, int port);
};

#endif // NETWORK_SETT_UI_H
