#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonEnviar_clicked()
{
    ui->label_resultado->setText("<b>Nombre: </b>" + ui->lineEditNombre->text() + "<br><br>" +
                                 "<b>Apellido: </b>" + ui->lineEditApellido->text() +"<br><br>"+
                                 "<b>Edad: </b>" +ui->lineEditEdad->text());
}


void MainWindow::on_lineEditEdad_textChanged(const QString &arg1)
{
    ui->spinBoxEdad->setValue(arg1.toInt());
    ui->horizontalSlider->setValue(arg1.toInt());
}


void MainWindow::on_spinBoxEdad_valueChanged(int arg1)
{
    ui->lineEditEdad->setText(QString::number(arg1));
    ui->horizontalSlider->setValue(arg1);
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->lineEditEdad->setText(QString::number(position));
    ui->spinBoxEdad->setValue(position);
}

