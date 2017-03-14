#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QColor>
#include <QMainWindow>
#include <QImage>
#include "main_view.h"
#include "shape_t.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <map>
#include <QLabel>
#include <QUndoStack>
#include "client.h"

namespace Ui { class main_window; }



class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();

protected:
    void closeEvent    (QCloseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent   (QResizeEvent* event)override;

private:
    void connect_all     ();
    void set_color_to_str(QString str, QColor color);
    void prepare_tool_bar();

private:
    Ui::main_window*           ui_;
    main_view*                 view_ { new main_view(900,900, this) };
    std::map<QString, QLabel*> col_labels;
    client *client_;

signals:
    void shape_selected(shape_t::type _shape);
    void save_selected();
    void color_selected(QColor color);
    void pen_size_selected(int width);
    void brush_selected(QColor color);
    void hand_selected();
    void resize_selected();
    void change_pen_clicked(QColor color);
    void change_brush_clicked(QColor color);
    void open_image_clicked(QString path);
    void undo_clicked();
    void redo_clicked();

private slots:
    void on_pushbutton_rect_clicked();
    void on_pushbutton_ellipse_clicked();
    void on_pushbutton_color_clicked();
    void on_pushbutton_line_clicked();
    void on_actionSave_triggered(bool checked);
    void on_pushButton_brush_clicked();
    void on_pushbutton_hand_clicked();
    void on_pushbutton_resize_clicked();
    void on_pb_change_pen_clicked();
    void on_pb_change_brush_clicked();
    void on_comboBox_shape_currentIndexChanged(int index);
    void on_spin_box_pen_size_valueChanged(int arg1);
    void on_action_open_clicked(bool b);

    void on_pushbutton_pen_clicked();
    void on_actionPen_triggered();
    void on_actionRectangle_triggered();
    void on_actionEllipse_triggered();
    void on_actionLine_triggered();
    void on_actionPen_color_triggered();
    void on_actionBrush_color_triggered();
    void on_actionMove_triggered();
    void on_actionResize_triggered();
    void on_actionChange_pen_triggered();
    void on_actionChange_brush_triggered();
    void on_actionUndo_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionRedo_triggered();
    void on_actionText_triggered();
    void on_actionConnect_to_server_triggered();

    void create_client(QString ip, int port);
};

#endif // MAIN_WINDOW_H
