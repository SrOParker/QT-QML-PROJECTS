#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&hilo, SIGNAL(actualizarCPU(double)), this, SLOT(actualizarLabel(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarLabel(double dato)
{
     ui->datosSistemaLabel->setText(QString::number(dato));
     ui->widgetGrafico->nuevoDato(dato);
}


void MainWindow::on_dialWidget_valueChanged(int value)
{
    ui->widgetGrafico->actualizarZoom(value);
}

