#ifndef LISTACAMPOS_H
#define LISTACAMPOS_H

#include <QVBoxLayout>

#include "campo.h"

class ListaCampos : public QWidget{
    Q_OBJECT
public:
    ListaCampos();
    void addCampos(Campo * c);
    QVector<Campo*> &getList();
    QVBoxLayout *getLayout();
private:
    QVector<Campo*> list_;
    QVBoxLayout * layout_;
};

#endif // LISTACAMPOS_H
