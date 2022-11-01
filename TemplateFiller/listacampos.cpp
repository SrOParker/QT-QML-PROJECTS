#include "listacampos.h"

ListaCampos::ListaCampos(QWidget *parent)
{
    layout_ = new QVBoxLayout(this);
}

ListaCampos::~ListaCampos()
{
    for (int i{}; i<list_.size();i++){
        delete list_[i];
    }delete layout_;
}

void ListaCampos::addCampos(QString label)
{
    list_.append(new Campo(this));
    list_[list_.size() - 1]->setLabelText(label);
    layout_->addWidget(list_[list_.size()-1]);
}

int ListaCampos::cantCampos()
{
    return list_.size();
}

QString ListaCampos::labelAt(int i)
{
    QString dev="";
    if (i < list_.size() && i>=0){
        dev = list_[i]->getLabelText();
    }
    return dev;
}

QString ListaCampos::textAt(int i)
{
    QString dev="";
    if (i < list_.size() && i>=0){
        dev = list_[i]->getLineEditText();
    }
    return dev;
}

int ListaCampos::encontrar(QString label)
{
    int indice = -1;
    for (int i {}; i<list_.size();++i){
        if (list_[i]->getLabelText() == label){
            indice = i;
        }
    }
    return indice;
}
