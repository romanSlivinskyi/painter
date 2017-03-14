#include "shape_com.h"

//shape_com::shape_com()
//{

//}

shape_com::shape_com(shape_info info, shape_t *shape, bool start) :
    now(info),
    pshape(shape),
    start_(start)
{
#ifdef COM_DEB
    qDebug() << "---------------------\ncommand constructor();";
#endif
}

shape_com::shape_com(shape_t *shape): //empty constr
    pshape(shape)
{
#ifdef COM_DEB
    qDebug() << "---------------------\ncommand empty constructor();";
#endif

}

void shape_com::undo()
{
    pshape->set_info(now);
#ifdef COM_DEB
    qDebug() << "undo() -> " << now.rect_ ;
#endif
}

void shape_com::redo()
{
    pshape->set_info(now);
#ifdef COM_DEB
    qDebug() << "redo(); -> " << now.rect_ ;
#endif
}
