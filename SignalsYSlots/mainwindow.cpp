#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Forma de hacer señal y slot
    //funcion para conectar dos objetos : el horizontal slider manda la señal cuando cambia su value, y el spin recoge ese slot
    //parametros: objeto que emite señal, señal, objeto que recibe señal, slot
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));

    connect(ui->pushButton1, SIGNAL(clicked(bool)), this, SLOT(togglearWidgets()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Comprueba si el slider y el spinbox estan visibles o no, y los cambia a visible u oculto
void MainWindow::togglearWidgets(){
    ui->horizontalSlider->setVisible(!ui->horizontalSlider->isVisible());
    ui->spinBox->setVisible(!ui->spinBox->isVisible());
}
