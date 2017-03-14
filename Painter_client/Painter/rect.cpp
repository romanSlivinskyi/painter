//#include "rect.h"
//#include <QDebug>

//QPen   rect_t::glob_pen_    { Qt::black };
//QBrush rect_t::glob_brush_  { Qt::transparent, Qt::SolidPattern };

//rect_t::rect_t(QPointF pos, QPen pen, QBrush brush)
//    :
//    rect_(pos, pos),
//    pen_(pen),
//    brush_(brush)
//{
//    setFlags(QGraphicsItem::ItemIsSelectable |
//             QGraphicsItem::ItemIsMovable |
//             QGraphicsItem::ItemSendsGeometryChanges);

//    setAcceptHoverEvents(true);
//    setRect(rect_);
//}

//QRectF rect_t::boundingRect() const
//{
//    return rect_.isValid() ? rect_ : rect_.normalized();
//}

//void rect_t::resize(QPointF finish)
//{
//    rect_.setBottomRight(finish);
//    setRect(rect_);
//    update();
//}

//void rect_t::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    painter->setPen(pen_);
//    painter->setBrush(brush_);
//    painter->drawRect(rect_);
//}

//void rect_t::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "mouseReleaseEvent";

//    prev_ = event->pos();

//    switch(stan_)
//    {
//        case stan::moveable:
//        {
//            cursor_.setShape(Qt::OpenHandCursor);
//            setCursor(cursor_);

//            break;
//        }
//        case stan::transformable:
//        {
//            break;
//        }
//        case stan::resizable:
//        {
//            break;
//        }
//        default:
//            break;
//    }
//}

//void rect_t::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "mousePressEvent";

//    if(rect_.contains(event->pos()))
//    {
//        prev_ = event->pos();

//        switch(stan_)
//        {
//            case stan::moveable:
//            {
//                cursor_.setShape(Qt::ClosedHandCursor);
//                setCursor(cursor_);

//                break;
//            }
//            case stan::transformable:
//            {
//                break;
//            }
//            case stan::resizable:
//            {
//                break;
//            }
//            case stan::spen:
//            {
//                setPen(glob_pen_);
//                break;
//            }
//            case stan::sbrush:
//            {
//                setBrush(glob_brush_);
//                break;
//            }
//            default:
//                break;
//        }

//    }
//}

//void rect_t::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "mouseMoveEvent";
//    QPointF curr = event->pos();

//    switch(stan_)
//    {
//        case stan::moveable:
//        {
//            QPointF diff = prev_ - curr;
//            rect_.setTopLeft    (rect_.topLeft()     - diff);
//            rect_.setBottomRight(rect_.bottomRight() - diff);
//            break;
//        }
//        case stan::transformable:
//        {
//            check_resize(curr.x(), curr.y(), 20);
//            break;
//        }
//        case stan::resizable:
//        {
//            break;
//        }
//        default:
//            break;
//    }

//    prev_ = curr;
//    setRect(rect_);
//    update();
//}

//void rect_t::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    qDebug() << "hoverEnterEvent";

//    switch(stan_)
//    {
//        case stan::moveable:
//        {
//            cursor_.setShape(Qt::OpenHandCursor);
//            setCursor(cursor_);
//            pen_.setColor(Qt::red);
//            break;
//        }
//        case stan::transformable:
//        {
//            break;
//        }
//        case stan::resizable:
//        {
//            break;
//        }
//        case stan::spen:
//        {
//            cursor_.setShape(Qt::CrossCursor);
//            setCursor(cursor_);
//            break;
//        }
//        case stan::sbrush:
//        {
//            cursor_.setShape(Qt::CrossCursor);
//            setCursor(cursor_);
//            break;
//        }
//        default:
//            break;
//    }

//    update();
//}

//void rect_t::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
//    qDebug() << "hoverLeaveEvent";
//    switch(stan_)
//    {
//        case stan::moveable:
//        {
//            pen_.setColor(Qt::black);
//            cursor_.setShape(Qt::ArrowCursor);
//            setCursor(cursor_);
//            break;
//        }
//        case stan::transformable:
//        {
//            break;
//        }
//        case stan::resizable:
//        {
//            break;
//        }
//        default:
//            break;
//    }
//    update();
//}

//void rect_t::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
//{
//    qDebug() << "hoverMoveEvent";
//    QPointF curr = event->pos();

//    switch(stan_)
//    {
//        case stan::moveable:
//        {
//            break;
//        }
//        case stan::transformable:
//        {
//            check_resize_hover(curr.x(), curr.y(), 20);
//            break;
//        }
//        case stan::resizable:
//        {
//            break;
//        }
//        default:
//            break;
//    }
//    update();
//}

































