#include "pen_t.h"

pen_t::pen_t(QPointF pos, QPen pen, QBrush brush, QVector<QRectF> points_vec, int onl_id)
    :
      shape_t(pos, pen, brush, onl_id),
      cache_p(pos),
      r_vec(points_vec)
{

}

QRectF pen_t::boundingRect() const
{
    return { 0,0,1000, 1000};
}

void pen_t::paint(QPainter *painter, const qstyle *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);

    painter->setPen(pen_);
    painter->setBrush(QBrush(pen_.color()));
    for(const auto& e : r_vec)
        painter->drawEllipse(e);
}

void pen_t::resize(QPointF finish)
{
    float X = cache_p.x();
    float Y = cache_p.y();
    float fX = finish.x();
    float fY = finish.y();
    do
    {
        X = X < fX ? ++X : X > fX ? --X : X;
        Y = Y < fY ? ++Y : Y > fY ? --Y : Y;
        r_vec.append(QRectF(X,Y, 1,1));
    }
    while(X != fX || Y != fY);

    cache_p = finish;
    r_vec.append({finish, finish + QPointF(1,1)});
    update();
}




























