#include "main_window.h"
#include "ui_main_window.h"
#include "server.h"
#include <QListWidget>
#include <QTextEdit>

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


void main_window::on_button_start_clicked()
{
    server_ = new server(ui->spinBox_port->value());
    connect(server_, SIGNAL(signal_new_user(int)),
            this, SLOT(slot_new_user_online(int)));
    connect(server_, SIGNAL(signal_user_disconnected(int)),
            this, SLOT(slot_user_disconnected(int)));
    connect(this, SIGNAL(user_to_disconnect(int)),
            server_, SLOT(slot_user_to_disconnect(int)));

    ui->status->setText("Working...");
    ui->status->setStyleSheet("color: green;");
}

void main_window::on_button_stop_clicked()
{
    server_->deleteLater();
    ui->status->setText("Deleted...");
    ui->status->setStyleSheet("color: red;");
}

void main_window::slot_new_user_online(int id)
{
    ui->users_list->addItem(QString::number(id));
}

void main_window::slot_user_disconnected(int id)
{
   QList<QListWidgetItem *> list = ui->users_list->findItems(QString::number(id), Qt::MatchExactly);
   if(!list.empty())
   {
       qDebug() << "Disconnected :" << id;
       delete list[0];
   }
}

void main_window::on_button_disconnect_clicked()
{
    int id = ui->users_list->currentItem()->text().toInt();\
    QList<QListWidgetItem *> list = ui->users_list->findItems(QString::number(id), Qt::MatchExactly);
    if(!list.empty())
        delete list[0];
    emit user_to_disconnect(id);
}
