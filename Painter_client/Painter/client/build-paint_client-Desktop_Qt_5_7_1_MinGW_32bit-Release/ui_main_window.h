/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_window
{
public:
    QWidget *centralWidget;
    QLineEdit *input_ip;
    QPushButton *button_connect;
    QListWidget *dialog_users_list;
    QTextEdit *dialog_mess_list;
    QPushButton *putton_send;
    QTextEdit *input_mess_field;
    QLineEdit *input_your_name;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *main_window)
    {
        if (main_window->objectName().isEmpty())
            main_window->setObjectName(QStringLiteral("main_window"));
        main_window->resize(478, 342);
        centralWidget = new QWidget(main_window);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        input_ip = new QLineEdit(centralWidget);
        input_ip->setObjectName(QStringLiteral("input_ip"));
        input_ip->setGeometry(QRect(10, 40, 141, 20));
        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setGeometry(QRect(160, 40, 61, 23));
        button_connect->setStyleSheet(QStringLiteral("background-color: green;"));
        dialog_users_list = new QListWidget(centralWidget);
        dialog_users_list->setObjectName(QStringLiteral("dialog_users_list"));
        dialog_users_list->setGeometry(QRect(10, 70, 141, 191));
        dialog_mess_list = new QTextEdit(centralWidget);
        dialog_mess_list->setObjectName(QStringLiteral("dialog_mess_list"));
        dialog_mess_list->setGeometry(QRect(160, 70, 311, 191));
        putton_send = new QPushButton(centralWidget);
        putton_send->setObjectName(QStringLiteral("putton_send"));
        putton_send->setGeometry(QRect(420, 270, 51, 41));
        input_mess_field = new QTextEdit(centralWidget);
        input_mess_field->setObjectName(QStringLiteral("input_mess_field"));
        input_mess_field->setGeometry(QRect(160, 270, 251, 41));
        input_your_name = new QLineEdit(centralWidget);
        input_your_name->setObjectName(QStringLiteral("input_your_name"));
        input_your_name->setGeometry(QRect(10, 10, 141, 20));
        main_window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(main_window);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 478, 21));
        main_window->setMenuBar(menuBar);

        retranslateUi(main_window);

        QMetaObject::connectSlotsByName(main_window);
    } // setupUi

    void retranslateUi(QMainWindow *main_window)
    {
        main_window->setWindowTitle(QApplication::translate("main_window", "Client", Q_NULLPTR));
        input_ip->setText(QApplication::translate("main_window", "localhost", Q_NULLPTR));
        button_connect->setText(QApplication::translate("main_window", "connect", Q_NULLPTR));
        putton_send->setText(QApplication::translate("main_window", "Send", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class main_window: public Ui_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
