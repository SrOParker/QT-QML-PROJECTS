#include "campo.h"

Campo::Campo(QWidget *parent)
{
    //parentamos los widgets label y line edit al widget campo
    name_.setParent(this);
    line_edit_campo_.setParent(this);
    //inicializo name_ el label
    name_.setText("label");
    name_.adjustSize();
    name_.move(10, 0);
    name_.setFixedHeight(name_.height());
    //inicializo line_edit_campo_
    line_edit_campo_.setText("label");
    line_edit_campo_.adjustSize();
    line_edit_campo_.move(0, name_.height() + 5);
    line_edit_campo_.setFixedHeight(line_edit_campo_.height());
    //inicializo el tamaño que va a tener un campo por def
    setFixedHeight(name_.height() + 10 + line_edit_campo_.height());
    //preparo el line edit despues de inicializarlo
    line_edit_campo_.setText("");
}

void Campo::setLabelText(QString text)
{
    name_.setText(text);
}

QString Campo::getLabelText()
{
    return name_.text();
}

QString Campo::getLineEditText()
{
    return line_edit_campo_.text();
}

void Campo::resizeEvent(QResizeEvent *event)
{
    name_.resize(width(), name_.height());
    line_edit_campo_.resize(width(), line_edit_campo_.height());
}
