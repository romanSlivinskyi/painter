#include "shape_t.h"

#include <QDebug>

QPen   shape_t::glob_pen_    { Qt::black };
QBrush shape_t::glob_brush_  { Qt::transparent, Qt::SolidPattern };
int    shape_t::Z            { 0 };

shape_t::shape_t(QPointF pos, QPen pen, QBrush brush, int onl_id)
    :
    rect_(pos, pos),
    pen_(pen),
    brush_(brush),
    online_id(onl_id),
    leave_pen_(pen)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);
    setRect(rect_);
}

void shape_t::set_info(const shape_info &info)
{
    online_id = info.online_id;
    rect_ = info.rect_;
    pen_ = info.pen_;
    brush_ = info.brush_;
}

shape_info shape_t::get_info()
{
    shape_info info;
    info.online_id = online_id;
    info.rect_ = rect_;
    info.pen_ = pen_;
    info.brush_ = brush_;
    return info;
}

QRectF shape_t::boundingRect() const
{
    return rect_.isValid() ? rect_ : rect_.normalized();
}

void shape_t::resize(QPointF finish)
{
    rect_.setBottomRight(finish);
    setRect(rect_);
    update();
}

void shape_t::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->setPen(pen_);
    painter->setBrush(brush_);
    painter->drawRect(rect_);
}

void shape_t::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef QT_DEBUG
    qDebug() << "mouseReleaseEvent";
#endif

    prev_ = event->pos();

    switch(stan_)
    {
        case stan::moveable:
        {
            cursor_.setShape(Qt::OpenHandCursor);
            setCursor(cursor_);

            break;
        }
        case stan::transformable:
        {
            dir_trans = dir::none;
            cursor_.setShape(Qt::ArrowCursor);
            break;
        }
        case stan::resizable:
        {
            break;
        }
        default:
            break;
    }

    if(stan_ != stan::off)
    {
        shape_info info;
        info.online_id = online_id; //AAAAAAAAAA
        info.rect_ = rect_;
        info.pen_ = leave_pen_;
        info.brush_ = brush_;
        emit command_done(info, this, type_); //todo send type
    }
}

void shape_t::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef QT_DEBUG
    qDebug() << "mousePressEvent";
#endif

    if(rect_.contains(event->pos()))
    {
        prev_ = event->pos();

        switch(stan_)
        {
            case stan::moveable:
            {
                cursor_.setShape(Qt::ClosedHandCursor);
                setCursor(cursor_);
                ++Z;
                setZValue(Z);
#ifdef QT_DEBUG
                qDebug() << "Z = " << Z;
#endif
                break;
            }
            case stan::transformable:
            {
                break;
            }
            case stan::resizable:
            {
                break;
            }
            case stan::spen:
            {
                setPen(glob_pen_);
                break;
            }
            case stan::sbrush:
            {
                setBrush(glob_brush_);
                break;
            }
            default:
                break;
        }

    }
}

void shape_t::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef QT_DEBUG
    qDebug() << "mouseMoveEvent";
#endif
    QPointF curr = event->pos();



    switch(stan_)
    {
        case stan::moveable:
        {
            QPointF diff = prev_ - curr;
            rect_.setTopLeft    (rect_.topLeft()     - diff);
            rect_.setBottomRight(rect_.bottomRight() - diff);
            break;
        }
        case stan::transformable:
        {
#ifdef QT_DEBUG
        qDebug() << "move : " << curr;
#endif

            check_resize(curr.x(), curr.y(), 20);
            break;
        }
        case stan::resizable:
        {
            break;
        }
        default:
            break;
    }

    prev_ = curr;
    setRect(rect_);
    update();
}

void shape_t::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);

#ifdef QT_DEBUG
    qDebug() << "hoverEnterEvent";
#endif
 qDebug() << "hoverEnterEvent";
    switch(stan_)
    {
        case stan::moveable:
        {
            cursor_.setShape(Qt::OpenHandCursor);
            setCursor(cursor_);
            pen_ = hover_pen_;
            break;
        }
        case stan::transformable:
        {
            break;
        }
        case stan::resizable:
        {
            break;
        }
        case stan::spen:
        {
            cursor_.setShape(Qt::CrossCursor);
            setCursor(cursor_);
            break;
        }
        case stan::sbrush:
        {
            cursor_.setShape(Qt::CrossCursor);
            setCursor(cursor_);
            break;
        }
        default:
            break;
    }

    update();
}

void shape_t::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
#ifdef QT_DEBUG
    qDebug() << "hoverLeaveEvent";
#endif
    switch(stan_)
    {
        case stan::moveable:
        {
            pen_ = leave_pen_;
            cursor_.setShape(Qt::ArrowCursor);
            setCursor(cursor_);
            break;
        }
        case stan::transformable:
        {
            break;
        }
        case stan::resizable:
        {
            break;
        }
        default:
            break;
    }
    update();
}

void shape_t::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
#ifdef QT_DEBUG
    qDebug() << "hoverMoveEvent";
#endif
    QPointF curr = event->pos();

    switch(stan_)
    {
        case stan::moveable:
        {
            break;
        }
        case stan::transformable:
        {
            check_resize_hover(curr.x(), curr.y(), 20);
            break;
        }
        case stan::resizable:
        {
            break;
        }
        default:
            break;
    }
    update();
}

void shape_t::check_resize(int curr_x, int curr_y, int diff)
{
    //left
    if((curr_x > rect_.topLeft().x() &&
            (curr_x - rect_.topLeft().x()) <= diff) || dir_trans == dir::left)
    {
        dir_trans = dir::left;
        QPointF p(rect_.topLeft().x() - (prev_.x() - curr_x),
                  rect_.topLeft().y());
        rect_.setTopLeft(p);
    }
    //right
    else if((curr_x < rect_.topRight().x() &&
            (rect_.topRight().x() - curr_x) <= diff) || dir_trans == dir::right)
    {
        dir_trans = dir::right;
        QPointF p(rect_.topRight().x() + (curr_x - prev_.x()),
                  rect_.topRight().y());
        rect_.setTopRight(p);
    }
    //up
    else if((curr_y > rect_.topLeft().y() &&
            curr_y - rect_.topLeft().y() <= diff) || dir_trans == dir::up)
    {
        dir_trans = dir::up;
        QPointF p(rect_.topLeft().x(),
                  rect_.topLeft().y() - (prev_.y() - curr_y) );
        rect_.setTopLeft(p);
    }
    //bottom
    else if((curr_y < rect_.bottomRight().y() &&
            rect_.bottomRight().y() - curr_y <= diff) || dir_trans == dir::bottom)
    {
        dir_trans = dir::bottom;
        QPointF p(rect_.bottomRight().x(),
                  rect_.bottomRight().y() + (curr_y - prev_.y()) );
        rect_.setBottomRight(p);
    }
    //update();
}

void shape_t::check_resize_hover(int curr_x, int curr_y, int diff)
{
    //left
    if(curr_x > rect_.topLeft().x() &&
            (curr_x - rect_.topLeft().x()) <= diff)
    {
        cursor_.setShape(Qt::SizeHorCursor);
    }
    //right
    else if(curr_x < rect_.topRight().x() &&
            (rect_.topRight().x() - curr_x) <= diff)
    {
        cursor_.setShape(Qt::SizeHorCursor);
    }
    //up
    else if(curr_y > rect_.topLeft().y() &&
            curr_y - rect_.topLeft().y() <= diff)
    {
        cursor_.setShape(Qt::SizeVerCursor);
    }
    //bottom
    else if(curr_y < rect_.bottomRight().y() &&
            rect_.bottomRight().y() - curr_y <= diff)
    {
        cursor_.setShape(Qt::SizeVerCursor);
    }
    else
    {
        cursor_.setShape(Qt::ArrowCursor);
    }
    setCursor(cursor_);
    update();
}

































