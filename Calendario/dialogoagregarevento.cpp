#include "dialogoagregarevento.h"
#include "ui_dialogoagregarevento.h"

DialogoAgregarEvento::DialogoAgregarEvento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoAgregarEvento)
{
    ui->setupUi(this);
}

DialogoAgregarEvento::~DialogoAgregarEvento()
{
    delete ui;
}

QString DialogoAgregarEvento::getEvento()
{
    return ui->lineEdit->text();
}

void DialogoAgregarEvento::show()
{
    ui->lineEdit->clear();
    QDialog::show();
}
