#ifndef ELLIPSE_T_H
#define ELLIPSE_T_H

#include "shape_t.h"

typedef QStyleOptionGraphicsItem qstyle;


class ellipse_t : public shape_t
{
public:
    ellipse_t(QPointF pos,
              QPen    pen  = QPen(Qt::black),
              QBrush  brush= QBrush(Qt::transparent),
              int onl_id = -1) : shape_t(pos, pen, brush, onl_id)
    {
        type_ = shape_t::type::ellipse;
    }

    void paint(QPainter                       *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget                        *widget = nullptr) override;
};

#endif // ELLIPSE_T_H
