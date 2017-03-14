#ifndef LINE_T_H
#define LINE_T_H

#include "shape_t.h"

typedef QStyleOptionGraphicsItem qstyle;

class line_t : public shape_t
{
public:
    line_t(QPointF pos,
           QPen    pen   = QPen(Qt::black),
           QBrush  brush = QBrush(Qt::transparent),
           int onl_id = -1) : shape_t(pos, pen, brush, onl_id)
    {
        type_ = shape_t::type::line;
    }

    void paint(QPainter     *painter,
               const qstyle *option,
               QWidget      *widget = nullptr) override;

};

#endif // LINE_T_H
