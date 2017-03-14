#ifndef PEN_T_H
#define PEN_T_H

#include "shape_t.h"
#include <QVector>

class pen_t : public shape_t
{
public:
    pen_t(QPointF pos,
          QPen    pen   = QPen(Qt::black),
          QBrush  brush = QBrush(Qt::black),
          QVector<QRectF> points_vec = {},
          int onl_id = -1);

    void   resize      (QPointF finish)                 override;
    QRectF boundingRect()                        const  override;
    void   paint       (QPainter     *painter,
                        const qstyle *option,
                        QWidget      *widget = nullptr) override;

public:
    QVector<QRectF> r_vec;
    QRect re;
    QPointF cache_p = { QPointF(0,0) };
};

#endif // PEN_T_H
