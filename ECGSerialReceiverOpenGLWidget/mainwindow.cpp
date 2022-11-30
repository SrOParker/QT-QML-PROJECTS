#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aMr_.startSerialCom("COM4", QSerialPort::Baud115200);
    connect(&aMr_, SIGNAL(dataReceived(QVariantList)), this, SLOT(agregarDato(QVariantList)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::agregarDato(const QVariantList &nuevosDatos)
{
    for (int i{}; i<nuevosDatos.size();++i){
        ui->widget->addValueToSignal(nuevosDatos[i].toFloat());
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->widget->resize(width()-10, height()-10);
    ui->widget->move(5,5);
}

