#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QPainter>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QCursor>
#include <QUndoStack>
#include <QUndoCommand>
#include <QVector>

struct shape_info
{
    int     online_id { -1 } ;
    QRectF  rect_  { QRectF(0,0,0,0) };
    QPen    pen_   { Qt::transparent };
    QBrush  brush_ { Qt::transparent };

    //....BAD
    QString text { "" };
    QVector<QRectF> pen_vec = {};
    //.......

    friend bool operator==(const shape_info& lhs, const shape_info& rhs)
    {
        return
        lhs.rect_  == rhs.rect_ &&
        lhs.pen_   == rhs.pen_ &&
        lhs.brush_ == rhs.brush_;
    }
};

enum class stan
{
    transformable, resizable, moveable, off, sbrush, spen
};

typedef QStyleOptionGraphicsItem qstyle;

class shape_t :public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    enum class type
    {
        none = 0, line, rect, ellipse, pen, text, abstract
    };
    enum class dir
    {
        none = 0, left, right, up, bottom,
    };

         shape_t     (QPointF pos,
                     QPen pen= QPen(Qt::black),
                     QBrush brush= QBrush(Qt::transparent),
                      int onl_id = -1);

    void       set_info (const shape_info& info);
    shape_info get_info ();
    void       set_stan (stan s)      { stan_ = s; update();}
    stan       get_stan ()            { return stan_; }
    void       setPen   (QPen pen)    { pen_   = pen; leave_pen_ = pen; update(); }
    void       setBrush (QBrush brush){ brush_ = brush;  update(); }

    virtual void resize(QPointF finish);

protected:
    QRectF  boundingRect      ()                                const override;
    void    paint             (QPainter *painter,
                               const qstyle *option,
                               QWidget *widget = nullptr)             override;
    void    mouseReleaseEvent (QGraphicsSceneMouseEvent *event)       override;
    void    mousePressEvent   (QGraphicsSceneMouseEvent *event)       override;
    void    mouseMoveEvent    (QGraphicsSceneMouseEvent *event)       override;
    void    hoverEnterEvent   (QGraphicsSceneHoverEvent *event)       override;
    void    hoverLeaveEvent   (QGraphicsSceneHoverEvent *event)       override;
    void    hoverMoveEvent    (QGraphicsSceneHoverEvent *event)       override;

protected:
    void    check_resize      (int curr_x, int curr_y, int diff);
    void    check_resize_hover(int curr_x, int curr_y, int diff);

private:
    //...... bad
    QPen hover_pen_ { Qt::green, 3, Qt::DashDotLine };
    QPen leave_pen_;
    //......

//protected:
public:
    QRectF  rect_;
    QPen    pen_      { Qt::black };
    QBrush  brush_    { Qt::transparent };
    QPointF prev_;
    QCursor cursor_;
    stan    stan_     { stan::off };
    type    type_     { type::abstract };
public:
    int     online_id { -1 } ;

public:
    static QPen   glob_pen_   ;
    static QBrush glob_brush_ ;
    static int    Z;

signals:
    void command_done(shape_info s, shape_t *shape, shape_t::type s_type);


private:
    dir dir_trans {dir::none} ;
};

#endif // SHAPE_H
