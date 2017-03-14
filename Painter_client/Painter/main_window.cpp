#include "main_window.h"
#include "ui_main_window.h"
#include <QColorDialog>
#include <QComboBox>
#include <qapplication.h>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QSpinBox>
#include "network_sett_ui.h"

main_window::main_window(QWidget *parent)
    :
    QMainWindow(parent),
    ui_(new Ui::main_window)
{
    setMouseTracking(true);
    ui_->setupUi(this);
    setCentralWidget(view_);

    prepare_tool_bar();
    connect_all();
}

main_window::~main_window()
{
    delete ui_;
}

void main_window::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    QMessageBox::StandardButton answer;

    answer = QMessageBox::question(this, "Painter",
                                   "Do you want to save picture?",
                                   QMessageBox::Yes|QMessageBox::No);

    if (answer == QMessageBox::Yes)
    {
        emit save_selected();
        QApplication::quit();

    }
    else
    {
        QApplication::quit();
    }
}

void main_window::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void main_window::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    qDebug() << centralWidget()->rect();
    view_->resize_s(centralWidget()->width(), centralWidget()->height());
}

void main_window::connect_all()
{
    connect(this,  SIGNAL(shape_selected(shape_t::type)),
            view_, SLOT  (shape_selected(shape_t::type)));
    connect(this,  SIGNAL(save_selected()),
            view_, SLOT  (save_selected()));
    connect(this,  SIGNAL(hand_selected()),
            view_, SLOT  (hand_selected()));
    connect(this, SIGNAL (color_selected(QColor)),
            view_, SLOT  (color_selected(QColor)));
    connect(this, SIGNAL (brush_selected(QColor)),
            view_, SLOT  (brush_selected(QColor)));
    connect(this,  SIGNAL(resize_selected()),
            view_, SLOT  (resize_selected()));
    connect(this, SIGNAL (change_pen_clicked(QColor)),
            view_, SLOT  (change_pen_clicked(QColor)));
    connect(this, SIGNAL (change_brush_clicked(QColor)),
            view_, SLOT  (change_brush_clicked(QColor)));
    connect(this, SIGNAL (pen_size_selected(int)),
            view_, SLOT  (pen_size_selected(int)));
    connect(ui_->actionOpen, SIGNAL(triggered(bool)),
            this,            SLOT(on_action_open_clicked(bool)));
    connect(this, SIGNAL(open_image_clicked(QString)),
            view_, SLOT(open_image_clicked(QString)));
    connect(this, SIGNAL(undo_clicked()),
            view_, SLOT(undo_clicked()));
    connect(this, SIGNAL(redo_clicked()),
            view_, SLOT(redo_clicked()));

}

void main_window::set_color_to_str(QString str, QColor color)
{
    col_labels[str]->setStyleSheet("background-color:" + color.name() + ";"
                                   +"color:" + color.name() + ";");
}

void main_window::prepare_tool_bar()
{
    std::array<QLabel*, 4> labs;
    for(int i = 0; i < 4; ++i)
        labs[i] = new QLabel("PPPPP");
    for(auto l : labs)
    {
        l->setMaximumHeight(15);
        l->setMaximumWidth(15);
    }

    col_labels["pen_color"] = labs[0];
    col_labels["brush_color"] = labs[1];
    col_labels["pen_change_color"] = labs[2];
    col_labels["brush_change_color"] = labs[3];

    set_color_to_str("pen_color", Qt::black);
    set_color_to_str("brush_color",  Qt::white);
    set_color_to_str("pen_change_color", Qt::black);
    set_color_to_str("brush_change_color", Qt::white);

    ui_->toolBar->insertWidget(ui_->actionPen_color, col_labels["pen_color"]);
    ui_->toolBar->insertWidget(ui_->actionBrush_color, col_labels["brush_color"]);
    ui_->toolBar->insertWidget(ui_->actionChange_pen, col_labels["pen_change_color"]);
    ui_->toolBar->insertWidget(ui_->actionChange_brush, col_labels["brush_change_color"]);

    QSpinBox *p_size = new QSpinBox(this);
    p_size->setValue(1);
    p_size->setMinimum(1);
    ui_->toolBar->insertWidget(ui_->actionPen_size, p_size);
    connect(p_size, SIGNAL(valueChanged(int)),
            this, SLOT(on_spin_box_pen_size_valueChanged(int)));
}

void main_window::on_pushbutton_rect_clicked()
{
    emit this->shape_selected(shape_t::type::rect);
    ui_->comboBox_shape->setCurrentIndex(static_cast<int>(shape_t::type::rect));
}

void main_window::on_pushbutton_ellipse_clicked()
{
    emit this->shape_selected(shape_t::type::ellipse);
    ui_->comboBox_shape->setCurrentIndex(static_cast<int>(shape_t::type::ellipse));
}

void main_window::on_pushbutton_color_clicked()
{   
    QColor color = QColorDialog::getColor();
    ui_->label_pen->setStyleSheet("background-color:" + color.name() + ";");
    emit color_selected(color);
}

void main_window::on_pushbutton_line_clicked()
{
    emit this->shape_selected(shape_t::type::line);
    ui_->comboBox_shape->setCurrentIndex(static_cast<int>(shape_t::type::line));
}

void main_window::on_actionSave_triggered(bool checked)
{
    Q_UNUSED(checked);
    emit save_selected();
}

void main_window::on_pushButton_brush_clicked()
{
    QColor color = QColorDialog::getColor();
    ui_->label_brush->setStyleSheet("background-color:" + color.name() + ";");
    emit brush_selected(color);
}

void main_window::on_pushbutton_hand_clicked()
{
    emit hand_selected();
}

void main_window::on_pushbutton_resize_clicked()
{
    emit resize_selected();
}

void main_window::on_pb_change_pen_clicked()
{
    QColor color = QColorDialog::getColor();
    emit change_pen_clicked(color);
}

void main_window::on_pb_change_brush_clicked()
{
    QColor color = QColorDialog::getColor();
    emit change_brush_clicked(color);
}

void main_window::on_comboBox_shape_currentIndexChanged(int index)
{
    emit shape_selected((shape_t::type)index);
}

void main_window::on_spin_box_pen_size_valueChanged(int arg1)
{
    emit pen_size_selected(arg1);
}

void main_window::on_action_open_clicked(bool b)
{
    Q_UNUSED(b);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
                                                    tr("Images (*.*)"));

    emit open_image_clicked(filename);
}

void main_window::on_pushbutton_pen_clicked()
{
    emit this->shape_selected(shape_t::type::pen);
    ui_->comboBox_shape->setCurrentIndex(static_cast<int>(shape_t::type::pen));
}

void main_window::on_actionPen_triggered()
{
    emit this->shape_selected(shape_t::type::pen);
    //ui_->comboBox_shape->setCurrentIndex(static_cast<int>(shape_t::type::pen));
}

void main_window::on_actionRectangle_triggered()
{
    emit this->shape_selected(shape_t::type::rect);
}

void main_window::on_actionEllipse_triggered()
{
    emit this->shape_selected(shape_t::type::ellipse);
}

void main_window::on_actionLine_triggered()
{
    emit this->shape_selected(shape_t::type::line);
}

void main_window::on_actionPen_color_triggered()
{
    QColor color = QColorDialog::getColor();
    set_color_to_str("pen_color",color);
    emit color_selected(color);
}

void main_window::on_actionBrush_color_triggered()
{
    QColor color = QColorDialog::getColor();
    set_color_to_str("brush_color",color);
    emit brush_selected(color);
}

void main_window::on_actionMove_triggered()
{
    emit hand_selected();
}

void main_window::on_actionResize_triggered()
{
    emit resize_selected();
}

void main_window::on_actionChange_pen_triggered()
{
    QColor color = QColorDialog::getColor();
    set_color_to_str("pen_change_color", color);
    emit change_pen_clicked(color);
}

void main_window::on_actionChange_brush_triggered()
{
    QColor color = QColorDialog::getColor();
    set_color_to_str("brush_change_color", color);
    emit change_brush_clicked(color);
}

void main_window::on_actionUndo_triggered()
{
    emit undo_clicked();
}

void main_window::on_actionSave_triggered()
{

}

void main_window::on_actionSave_As_triggered()
{

}

void main_window::on_actionRedo_triggered()
{
    emit redo_clicked();
}

void main_window::on_actionText_triggered()
{
    emit this->shape_selected(shape_t::type::text);
}

void main_window::on_actionConnect_to_server_triggered()
{
     network_sett_ui *sett = new network_sett_ui(this);
     sett->show();
     connect(sett,SIGNAL(settings_info(QString,int)),
             this, SLOT(create_client(QString,int)));
}

void main_window::create_client(QString ip, int port)
{
    //network
    client_ = new client(ip, port);
    connect(view_, SIGNAL(signal_to_network_command(shape_t::type,shape_info)),
            client_, SLOT(slot_send_paint_command(shape_t::type,shape_info)));
    connect(client_, SIGNAL(signal_new_paint_command(shape_t::type,shape_info)),
            view_, SLOT(from_network_command(shape_t::type,shape_info)));
    ui_->actionConnect_to_server->setChecked(true);
    //network
}


























