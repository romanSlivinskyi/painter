#include "main_view.h"
#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QPushButton>

main_view::main_view(int _width, int _height, QObject *parent)
{
    Q_UNUSED(parent);
    setMouseTracking(true);
    setScene(scene_);
    scene_->setSceneRect(QRectF(0., 0., _width, _height));
    scene_->setBackgroundBrush(Qt::white);
}

void main_view::resize_s(int w, int h)
{
    scene_->setSceneRect(0, 0, w, h);
}

void main_view::mousePressEvent(QMouseEvent* _event)
{
    QGraphicsView::mousePressEvent(_event);

    switch(shapes_in_.type_)
    {
        case shape_t::type::none:
        {
            break;
        }
        case shape_t::type::rect:
        {
            make_rect(_event->pos());
            break;
        }
        case shape_t::type::ellipse:
        {
            make_ellispe(_event->pos());
            break;
        }
        case shape_t::type::line:
        {
            make_line(_event->pos());
            break;
        }
        case shape_t::type::pen:
        {
            make_pen(_event->pos());
            break;
        }
        case shape_t::type::text:
        {
            make_text(_event->pos());
            break;
        }
        default:
        {
            break;
        }
    }
}

void main_view::mouseReleaseEvent(QMouseEvent* _event)
{
    QGraphicsView::mouseReleaseEvent(_event);
    if(shapes_in_.shape_ != nullptr &&
       shapes_in_.shape_->get_stan() == stan::resizable)
    {
        shapes_in_.shape_->set_stan(stan::off);
        auto command = new shape_com(shapes_in_.shape_->get_info(), shapes_in_.shape_, true);
        undo_stack_->push(new shape_com(shapes_in_.shape_));
        undo_stack_->push(command);
        //network
        if(shapes_in_.type_ == shape_t::type::pen)
        {
            shape_info inf = shapes_in_.shape_->get_info();
            inf.pen_vec =  dynamic_cast<pen_t*>(shapes_in_.shape_)->r_vec;
            emit signal_to_network_command(shapes_in_.type_, inf);
            qDebug() << "PEN TYPE ";
        }
        else
        {
            emit signal_to_network_command(shapes_in_.type_, shapes_in_.shape_->get_info());
        }
        //network
    }
}

void main_view::mouseMoveEvent(QMouseEvent* _event)
{
    QGraphicsView::mouseMoveEvent(_event);

    static auto iT = scene_->addText("X : " + QString::number(_event->x()) +
                     " Y : " + QString::number(_event->y()));
    iT->setPlainText("X: " + QString::number(_event->x()) +
                    "  Y: " + QString::number(_event->y()));

    if(shapes_in_.shape_ != nullptr &&
       shapes_in_.shape_->get_stan() == stan::resizable)
        shapes_in_.shape_->resize(_event->pos());
}

void main_view::make_rect(QPoint pos)
{
    shapes_in_.shape_ = new rect_t(pos,
                                   shapes_in_.curr_pen_,
                                   shapes_in_.curr_brush);
    shapes_in_.shape_vec_.push_back(shapes_in_.shape_);
    scene_->addItem(shapes_in_.shape_);
    shapes_in_.shape_->set_stan(stan::resizable);
    connect(shapes_in_.shape_, SIGNAL(command_done(shape_info,shape_t*,shape_t::type)),
            this,                SLOT(command_done(shape_info,shape_t*,shape_t::type)));
}

void main_view::make_ellispe(QPoint pos)
{
    shapes_in_.shape_ = new ellipse_t(pos,
                                      shapes_in_.curr_pen_,
                                      shapes_in_.curr_brush);
    shapes_in_.shape_vec_.push_back(shapes_in_.shape_);
    scene_->addItem(shapes_in_.shape_);
    shapes_in_.shape_->set_stan(stan::resizable);
    connect(shapes_in_.shape_, SIGNAL(command_done(shape_info,shape_t*,shape_t::type)),
            this,                SLOT(command_done(shape_info,shape_t*,shape_t::type)));
}

void main_view::make_line(QPoint pos)
{
    shapes_in_.shape_ = new line_t(pos,
                                   shapes_in_.curr_pen_,
                                   shapes_in_.curr_brush);
    shapes_in_.shape_vec_.push_back(shapes_in_.shape_);
    scene_->addItem(shapes_in_.shape_);
    shapes_in_.shape_->set_stan(stan::resizable);
    connect(shapes_in_.shape_, SIGNAL(command_done(shape_info,shape_t*,shape_t::type)),
            this,                SLOT(command_done(shape_info,shape_t*,shape_t::type)));
}

void main_view::make_pen(QPoint pos)
{
#ifdef QT_DEBUG
    qDebug() << "here";
#endif
    shapes_in_.shape_ = new pen_t(pos,
                                  shapes_in_.curr_pen_,
                                  shapes_in_.curr_brush);
    shapes_in_.shape_vec_.push_back(shapes_in_.shape_);
    scene_->addItem(shapes_in_.shape_);
    shapes_in_.shape_->set_stan(stan::resizable);
}

void main_view::make_text(QPoint pos)
{
    if(prev_finish){
        prev_finish = false;
        QLineEdit *edit = new QLineEdit();
        QGraphicsProxyWidget * line_ed = scene_->addWidget(edit);
        line_ed->setPos(pos);
        connect(edit, SIGNAL(returnPressed()), this, SLOT(put_text()));
        //..........................
    }
}

void main_view::shape_selected(shape_t::type _shape_type)
{
    for(auto s : shapes_in_.shape_vec_)
        s->set_stan(stan::off);

    shapes_in_.type_ = _shape_type;
}

void main_view::save_selected()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Images (*.png)"));
    QPixmap image(scene_->width(), scene_->height());
    QPainter painter(&image);

    scene_->render(&painter);

    if(!image.save(filename))
        qDebug() << "error save ";
}

void main_view::color_selected(QColor color)
{
    shapes_in_.curr_pen_.setColor(color);
}

void main_view::brush_selected(QColor color)
{
    shapes_in_.curr_brush.setColor(color);
}

void main_view::hand_selected()
{
    shapes_in_.type_ = shape_t::type::none;

    for(auto s : shapes_in_.shape_vec_)
        s->set_stan(stan::moveable);
}

void main_view::resize_selected()
{
    shapes_in_.type_ = shape_t::type::none;
#ifdef QT_DEBUG
    qDebug() << shapes_in_.shape_vec_.size();
#endif
    for(auto s : shapes_in_.shape_vec_)
        s->set_stan(stan::transformable);
}

void main_view::change_pen_clicked(QColor color)
{
    shapes_in_.type_ = shape_t::type::none;

    shape_t::glob_pen_.setColor(color);
    for(auto s : shapes_in_.shape_vec_)
        s->set_stan(stan::spen);
}

void main_view::change_brush_clicked(QColor color)
{
    shapes_in_.type_ = shape_t::type::none;

    shape_t::glob_brush_.setColor(color);
    for(auto s : shapes_in_.shape_vec_)
        s->set_stan(stan::sbrush);
}

void main_view::pen_size_selected(int width)
{
    shapes_in_.curr_pen_.setWidth(width);
}

void main_view::open_image_clicked(QString filename)
{
    QImage image(filename);
    auto item = new QGraphicsPixmapItem( QPixmap::fromImage(image));
    scene_->addItem(item);
}

void main_view::command_done(shape_info info, shape_t *shape, shape_t::type s_type)
{
    auto command = new shape_com(info, shape);
    undo_stack_->push(command);
#ifdef COM_DEB
    qDebug() << "stack size = " << undo_stack_->count() << "\n---------------------\n";
#endif
    qDebug() << "------ type = " << (int)s_type;
    emit signal_to_network_command(s_type, info);
    //network
}

void main_view::undo_clicked()
{
#ifdef COM_DEB
    qDebug() << "Undo clicked();" ;
#endif
    undo_stack_->undo();
    scene_->update();
}

void main_view::redo_clicked()
{
#ifdef COM_DEB
    qDebug() << "Redo clicked();" ;
#endif
    undo_stack_->redo();
    scene_->update();
}

void main_view::put_text() //if ok clicked in make text(), to put text item to sxcene
{
    QLineEdit *edit = (QLineEdit*)sender();

    shapes_in_.shape_ = new text_t(edit->pos(),
                                   edit->text(),
                                   shapes_in_.curr_pen_,
                                   shapes_in_.curr_brush);
    shapes_in_.shape_vec_.push_back(shapes_in_.shape_);
    scene_->addItem(shapes_in_.shape_);
    shapes_in_.shape_->set_stan(stan::off);
    //...net
    shape_info inf = shapes_in_.shape_->get_info();
    inf.text = dynamic_cast<text_t*>(shapes_in_.shape_)->text_;
    emit signal_to_network_command(shapes_in_.type_, inf);
    qDebug() <<"Text = " << inf.text;
    //......
    edit->deleteLater();
    prev_finish = true;
}

void main_view::from_network_command(shape_t::type type, shape_info inf)
{
    /*in this case its just create new item
     *the goal is to set the inf if shape is
     *already exists
     */


    //chek if there is item with that online id
    auto iter = std::find_if(shapes_in_.shape_vec_.begin(), shapes_in_.shape_vec_.end(),[&](shape_t* s)
    {
            return s->online_id == inf.online_id;
    });
    if(iter != shapes_in_.shape_vec_.end())
    {
        (*iter)->set_info(shape_info());
        //(*iter)->set_info(inf)
//        scene_->update();
//        qDebug() << "TRUE  - " << (int)(*iter)->get_stan();
    }
    //else
    //delete curr shape
    if(shapes_in_.shape_ != nullptr)
        shapes_in_.shape_->set_info(shape_info());

    auto add_s_from_net = [&](shape_t* s)
    {
        s->resize(inf.rect_.bottomRight());
        s->set_stan(stan::off);
        shapes_in_.shape_vec_.push_back(s);
        scene_->addItem(s);
        connect(s,   SIGNAL(command_done(shape_info, shape_t*, shape_t::type)),
                this,SLOT(command_done(shape_info, shape_t*, shape_t::type)));
        scene_->update();
    };
    switch(type)
    {
        case shape_t::type::rect:
        {
            shape_t *from_net  = new rect_t(inf.rect_.topLeft(), inf.pen_, inf.brush_, inf.online_id);
            add_s_from_net(from_net);
            break;
        }
        case shape_t::type::ellipse:
        {
            shape_t *from_net  = new ellipse_t(inf.rect_.topLeft(), inf.pen_, inf.brush_, inf.online_id);
            add_s_from_net(from_net);
            break;
        }
        case shape_t::type::line:
        {
            shape_t *from_net  = new line_t(inf.rect_.topLeft(), inf.pen_, inf.brush_, inf.online_id);
            add_s_from_net(from_net);
            break;
        }
        case shape_t::type::text:
        {
            shape_t *from_net  = new text_t(inf.rect_.topLeft(), inf.text, inf.pen_, inf.brush_, inf.online_id);
            add_s_from_net(from_net);
            break;
        }
        case shape_t::type::pen:
        {
            shape_t *from_net  = new pen_t(inf.rect_.topLeft(), inf.pen_, inf.brush_, inf.pen_vec, inf.online_id);
            add_s_from_net(from_net);
            break;
        }
        default:
            break;
    }

}





















