#ifndef TEXT_T_H
#define TEXT_T_H

#include "shape_t.h"

class text_t : public shape_t
{
public:
    text_t(QPointF pos,
           QString text,
           QPen    pen  = QPen(Qt::black),
           QBrush  brush= QBrush(Qt::transparent),
           int onl_id = -1)
        :
          shape_t(pos, pen, brush, onl_id),
          text_(text)
    {
        type_ = shape_t::type::text;
        rect_.setRect(pos.x(), pos.y(), text.length() * 10, 50);
    }

//    QRectF boundingRect() const override
//    {
//        return { 0,0,2000, 2000};
//    }

    //void resize(QPointF finish) override
    //{
//        rect_.setRect(0,0,1000, 1000);
//        setRect(rect_);
   // }
    void paint(QPainter                       *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget                        *widget = nullptr) override
    {
        Q_UNUSED(option); Q_UNUSED(widget);
        painter->setPen(pen_);
        painter->setBrush(QBrush(pen_.color()));
        painter->drawText(rect_.topLeft() + QPointF(10, 10), text_);
        update();
    }



public:
    QString text_;
};

#endif // TEXT_T_H
