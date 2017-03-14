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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_window
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *edit_main;
    QPlainTextEdit *edit_user;
    QPlainTextEdit *edit_online;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_send;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *main_window)
    {
        if (main_window->objectName().isEmpty())
            main_window->setObjectName(QStringLiteral("main_window"));
        main_window->resize(482, 342);
        centralWidget = new QWidget(main_window);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        edit_main = new QPlainTextEdit(centralWidget);
        edit_main->setObjectName(QStringLiteral("edit_main"));
        edit_main->setGeometry(QRect(10, 10, 271, 251));
        edit_user = new QPlainTextEdit(centralWidget);
        edit_user->setObjectName(QStringLiteral("edit_user"));
        edit_user->setGeometry(QRect(10, 270, 221, 41));
        edit_online = new QPlainTextEdit(centralWidget);
        edit_online->setObjectName(QStringLiteral("edit_online"));
        edit_online->setGeometry(QRect(290, 60, 181, 111));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 210, 41, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 30, 91, 31));
        label_2->setFont(font);
        pushButton_send = new QPushButton(centralWidget);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(240, 280, 41, 23));
        main_window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(main_window);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 482, 21));
        main_window->setMenuBar(menuBar);

        retranslateUi(main_window);

        QMetaObject::connectSlotsByName(main_window);
    } // setupUi

    void retranslateUi(QMainWindow *main_window)
    {
        main_window->setWindowTitle(QApplication::translate("main_window", "Client", Q_NULLPTR));
        label->setText(QApplication::translate("main_window", "You:", Q_NULLPTR));
        label_2->setText(QApplication::translate("main_window", "Online:", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("main_window", "Send", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class main_window: public Ui_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
