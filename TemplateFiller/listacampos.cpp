#include "listacampos.h"

ListaCampos::ListaCampos()
{
    layout_ = new QVBoxLayout(this);
}

void ListaCampos::addCampos(Campo *c)
{


    layout_->addWidget(c);
    list_.push_back(c);


}

QVector<Campo*> &ListaCampos::getList()
{
    return list_;
}

QVBoxLayout *ListaCampos::getLayout()
{
    return layout_;
}
