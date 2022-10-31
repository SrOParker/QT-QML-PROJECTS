#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadA.setText("Boton A presionado");
    threadB.setText("Boton B presionado");

    connect(&threadA, SIGNAL(modifyLabel(QString)), this, SLOT(updateLabelA(QString)));
    connect(&threadB, SIGNAL(modifyLabel(QString)), this, SLOT(updateLabelB(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButtonA_clicked()
{
    threadA.start(); //start() llama a run()
}


void MainWindow::on_pushButtonB_clicked()
{
    threadB.start();
}


void MainWindow::on_pushButtonSalir_clicked()
{
    threadA.stop();
    threadB.stop();

    threadA.wait();
    threadB.wait();

    close();
}

void MainWindow::updateLabelA(const QString &newText)
{
    ui->labelA->setText(newText);
}

void MainWindow::updateLabelB(const QString &newText)
{
    ui->labelB->setText(newText);
}

