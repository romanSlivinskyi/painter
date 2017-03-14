#include "network_sett_ui.h"
#include "ui_network_sett_ui.h"

network_sett_ui::network_sett_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::network_sett_ui)
{
    ui->setupUi(this);
}

network_sett_ui::~network_sett_ui()
{
    delete ui;
}

void network_sett_ui::on_connect_button_accepted()
{
    QString ip = ui->sever_ip_input->text();
    int port = ui->port_spin->value();
    emit settings_info(ip, port);
}
