#include "calendario.h"
#include "ui_calendario.h"

Calendario::Calendario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calendario)
{
    ui->setupUi(this);
}

Calendario::~Calendario()
{
    delete ui;
}

