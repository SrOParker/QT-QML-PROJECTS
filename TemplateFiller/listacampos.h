#ifndef LISTACAMPOS_H
#define LISTACAMPOS_H

#include <QWidget>
#include <QVBoxLayout>

#include "campo.h"

class ListaCampos : public QWidget{
    Q_OBJECT
public:
    explicit ListaCampos(QWidget *parent = nullptr);
    ~ListaCampos();

    void addCampos(QString label);
    int cantCampos();
    QString labelAt(int i);
    QString textAt(int i);
    int encontrar(QString label);
private:
    QVector<Campo*> list_;
    QVBoxLayout * layout_;
};

#endif // LISTACAMPOS_H
