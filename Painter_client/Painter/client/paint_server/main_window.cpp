#include "main_window.h"
#include "ui_main_window.h"
#include "server.h"
#include "client.h"
#include <QTextEdit>
#include <QBrush>
#include <QListWidget>

main_window::main_window(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::main_window)
{
    ui->setupUi(this);
}

main_window::~main_window()
{
    delete ui;
}


void main_window::on_button_connect_clicked()
{
    client_ = new client(ui->input_ip->text(), ui->input_your_name->text(), 1111);

    connect(this,    SIGNAL(signal_send_message(QString,QString)),
            client_, SLOT  (slot_send_message(QString,QString)));
    connect(client_, SIGNAL(signal_new_message(QString,QString)),
            this,    SLOT  (slot_new_message(QString,QString)));
    connect(client_, SIGNAL(signal_new_user_online(QString)),
            this,    SLOT  (slot_new_user_online(QString)));

    //add users from client data
    for(auto& row : client_->dialog_data_)
        ui->dialog_users_list->addItem(row.first);

}

void main_window::on_putton_send_clicked()
{
    QString to = ui->dialog_users_list->item(ui->dialog_users_list->currentRow())->text();
    QString msg = ui->input_mess_field->toPlainText();
    ui->dialog_mess_list->setText(ui->dialog_mess_list->toPlainText() + client_->get_name() + ": " + msg + "\n");

    emit signal_send_message(to, msg);
    //qDebug() << to << " - " << (int)right << " " << msg;
}

void main_window::slot_new_message(QString to, QString msg)
{
    QList<QListWidgetItem *> list = ui->dialog_users_list->findItems(to,Qt::MatchExactly);

    for(auto i : list)
        i->setBackground(QBrush(Qt::green));

    //update dialog_users_list if current is the same as new mess in
    emit ui->dialog_users_list->currentRowChanged(ui->dialog_users_list->currentRow());
}

void main_window::slot_new_user_online(QString name)
{
    ui->dialog_users_list->addItem(name);
}

void main_window::on_dialog_users_list_currentRowChanged(int currentRow)
{
    QString curr_user = ui->dialog_users_list->currentItem()->text();
    ui->dialog_users_list->item(currentRow)->setBackgroundColor(Qt::transparent);

    ui->dialog_mess_list->setText("");
    for(auto& row : client_->dialog_data_[curr_user])
    {
        ui->dialog_mess_list->setText(ui->dialog_mess_list->toPlainText() + row.from + ": " + row.mess + "\n");
    }
}

























