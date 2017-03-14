#ifndef RECT_H
#define RECT_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QPainter>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QCursor>

//typedef QStyleOptionGraphicsItem qstyle;

//enum class stan
//{
//    transformable, resizable, moveable, off, sbrush, spen
//};

//class rect_t : public QGraphicsRectItem
//{
//public:
//         rect_t     (QPointF pos,
//                     QPen pen= QPen(Qt::black),
//                     QBrush brush= QBrush(Qt::transparent));

//    void set_stan   (stan s)              { stan_ = s; }
//    stan get_stan   ()                    { return stan_; }
//    void resize     (QPointF finish);
//    void setPen     (QPen pen)            { pen_   = pen;   update(); }
//    void setBrush   (QBrush brush)        { brush_ = brush; update(); }

//protected:
//    QRectF  boundingRect      ()                                const override;
//    void    paint             (QPainter *painter,const qstyle *option,
//                               QWidget *widget = nullptr)             override;
//    void    mouseReleaseEvent (QGraphicsSceneMouseEvent *event)       override;
//    void    mousePressEvent   (QGraphicsSceneMouseEvent *event)       override;
//    void    mouseMoveEvent    (QGraphicsSceneMouseEvent *event)       override;
//    void    hoverEnterEvent   (QGraphicsSceneHoverEvent *event)       override;
//    void    hoverLeaveEvent   (QGraphicsSceneHoverEvent *event)       override;
//    void    hoverMoveEvent    (QGraphicsSceneHoverEvent *event)       override;


//private:
//    void    check_resize      (int curr_x, int curr_y, int diff)
//    {
//        //left
//        if(curr_x > rect_.topLeft().x() &&
//          (curr_x - rect_.topLeft().x()) <= diff)
//        {
//            QPointF p(rect_.topLeft().x() - (prev_.x() - curr_x),
//                      rect_.topLeft().y());
//            rect_.setTopLeft(p);
//        }
//        //right
//        else if(curr_x < rect_.topRight().x() &&
//               (rect_.topRight().x() - curr_x) <= diff)
//        {
//            QPointF p(rect_.topRight().x() + (curr_x - prev_.x()),
//                      rect_.topRight().y());
//            rect_.setTopRight(p);
//        }
//        //up
//        else if(curr_y > rect_.topLeft().y() &&
//                curr_y - rect_.topLeft().y() <= diff)
//        {
//            QPointF p(rect_.topLeft().x(),
//                      rect_.topLeft().y() - (prev_.y() - curr_y) );
//            rect_.setTopLeft(p);
//        }
//        //bottom
//        else if(curr_y < rect_.bottomRight().y() &&
//                rect_.bottomRight().y() - curr_y <= diff)
//        {
//            QPointF p(rect_.bottomRight().x(),
//                      rect_.bottomRight().y() + (curr_y - prev_.y()) );
//            rect_.setBottomRight(p);
//        }
//        update();
//    }
//    void    check_resize_hover(int curr_x, int curr_y, int diff)
//    {
//        //left
//        if(curr_x > rect_.topLeft().x() &&
//          (curr_x - rect_.topLeft().x()) <= diff)
//        {
//            cursor_.setShape(Qt::SizeHorCursor);
//        }
//        //right
//        else if(curr_x < rect_.topRight().x() &&
//               (rect_.topRight().x() - curr_x) <= diff)
//        {
//            cursor_.setShape(Qt::SizeHorCursor);
//        }
//        //up
//        else if(curr_y > rect_.topLeft().y() &&
//                curr_y - rect_.topLeft().y() <= diff)
//        {
//             cursor_.setShape(Qt::SizeVerCursor);
//        }
//        //bottom
//        else if(curr_y < rect_.bottomRight().y() &&
//                rect_.bottomRight().y() - curr_y <= diff)
//        {
//             cursor_.setShape(Qt::SizeVerCursor);
//        }
//        else
//        {
//            cursor_.setShape(Qt::ArrowCursor);
//        }
//        setCursor(cursor_);
//        update();
//    }

//private:
//    QRectF  rect_;
//    QPen    pen_      { Qt::black };
//    QBrush  brush_    { Qt::transparent };
//    QPointF prev_;
//    QCursor cursor_;
//    stan    stan_     { stan::off };

//public:
//    static QPen   glob_pen_   ;
//    static QBrush glob_brush_ ;

//};

#endif // RECT_H
