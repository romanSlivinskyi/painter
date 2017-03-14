#ifndef SHAPE_COM_H
#define SHAPE_COM_H
//#define COM_DEB
#include "shape_t.h"
#include <QUndoCommand>

class shape_com : public QUndoCommand
{
public:
    shape_com(shape_info info, shape_t *shape, bool start = false);
    shape_com(shape_t *shape);

    void undo() override;
    void redo() override;

    bool start_;
    shape_info now { shape_info() };
    shape_t* pshape { nullptr };
};

#endif // SHAPE_COM_H
