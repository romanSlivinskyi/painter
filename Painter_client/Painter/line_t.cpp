#include "line_t.h"

#include "rect.h"
#include <QDebug>


void line_t::paint(QPainter *painter, const qstyle *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->setPen(pen_);
    painter->setBrush(brush_);
    painter->drawLine(rect_.topLeft(), rect_.bottomRight());
}
