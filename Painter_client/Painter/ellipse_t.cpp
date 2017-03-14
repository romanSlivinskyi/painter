#include "ellipse_t.h"

void ellipse_t::paint(QPainter *painter, const qstyle *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->setPen(pen_);
    painter->setBrush(brush_);
    painter->drawEllipse(rect_);
}
