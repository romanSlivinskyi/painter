#ifndef RECT_T_H
#define RECT_T_H

#include "shape_t.h"


class rect_t : public shape_t
{
public:
    rect_t(QPointF pos,
           QPen    pen   = QPen(Qt::black),
           QBrush  brush = QBrush(Qt::transparent),
           int onl_id = -1) : shape_t(pos, pen, brush, onl_id)
    {
        type_ = shape_t::type::rect;
    }

    void paint(QPainter     *painter,
               const qstyle *option,
               QWidget      *widget = nullptr) override;
};

#endif // RECT_T_H
