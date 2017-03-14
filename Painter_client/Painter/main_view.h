#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H
//#define COM_DEB
#include <QDebug>
#include "shape_t.h"

#include <QRectF>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>
#include <QPainter>
#include <QImage>
#include "rect.h"
#include "ellipse_t.h"
#include "line_t.h"
#include <vector>
#include "shape_t.h"
#include "rect_t.h"
#include "pen_t.h"
#include <QUndoStack>
#include <QUndoCommand>
#include "shape_com.h"
#include <text_t.h>
#include <QLineEdit>
#include <algorithm>

using namespace std;

struct shapes_in
{
    shape_t::type     type_     { shape_t::type::none };
    shape_t*          shape_    { nullptr };
    vector<shape_t*>  shape_vec_;
    QPen              curr_pen_ { QPen(Qt::black) };
    QBrush            curr_brush{ QBrush(Qt::transparent) };
};

class main_view : public QGraphicsView
{
    Q_OBJECT

public:
         main_view(int _width = 600, int _height = 600, QObject *parent = nullptr);
    void resize_s (int w, int h);

protected:
    void mousePressEvent   (QMouseEvent* _event) override;
    void mouseReleaseEvent (QMouseEvent* _event) override;
    void mouseMoveEvent    (QMouseEvent* _event) override;

private:
    void make_rect    (QPoint pos);
    void make_ellispe (QPoint pos);
    void make_line    (QPoint pos);
    void make_pen     (QPoint pos);
    void make_text    (QPoint pos);

private:
    QGraphicsScene*  scene_      { new QGraphicsScene } ;
    shapes_in        shapes_in_;
    QUndoStack*      undo_stack_ { new QUndoStack() };

signals:
    void signal_to_network_command(shape_t::type t, shape_info inf);

public slots:
    void shape_selected         (shape_t::type _shape_type);
    void save_selected          ();
    void color_selected         (QColor color);
    void brush_selected         (QColor color);
    void hand_selected          ();
    void resize_selected        ();
    void change_pen_clicked     (QColor color);
    void change_brush_clicked   (QColor color);
    void pen_size_selected      (int width);
    void open_image_clicked     (QString filename);

    void command_done(shape_info info, shape_t *shape, shape_t::type s_type);
    void undo_clicked();
    void redo_clicked();

    void put_text();

    //network
    void from_network_command(shape_t::type type, shape_info inf);
    //network

public:
    //todo
    bool prev_finish = true;
};

#endif // MAIN_VIEW_H
