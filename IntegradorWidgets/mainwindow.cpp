#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    for (int i = 0; i < availablePorts.size(); i++) {
        ui->menuPorts->addAction(availablePorts[i].portName());

        ui->menuPorts->actions()[i]->setCheckable(true);
    }
    ui->pushButtonSTART->setVisible(false);
    ui->pushButtonSTOP->setVisible(false);
    ui->pushButtonCurrent->setVisible(false);

    xPosActual = 0;

    connect(ui->menuPorts, SIGNAL(triggered(QAction*)), this, SLOT(portActionTriggered(QAction*)));
    connect(&manager, SIGNAL(activablesSTARTySTOP()), this, SLOT(activeSTARTandSTOP()));
    connect(&manager, SIGNAL(currentSignalview()), this, SLOT(currentSignalInStatusBar()));
    connect(&manager, SIGNAL(signalDataEmited(float)), this, SLOT(paintDataReceived(float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::portActionTriggered(QAction *action)
{
    for (int i = 0; i < ui->menuPorts->actions().size(); i++) {
        if (ui->menuPorts->actions()[i] != action)
        {
            ui->menuPorts->actions()[i]->setChecked(false);
        }
    }

    if (manager.getPort().isOpen()) {
        manager.getPort().close();
    }

    manager.getPort().setPortName(action->text());
    manager.getPort().setBaudRate(QSerialPort::Baud115200);

    if (manager.getPort().open(QIODeviceBase::ReadWrite)) {
        ui->statusbar->showMessage("Puerto abierto exitosamente", 5000);
    }
    else {
        ui->statusbar->showMessage("Error al abrir puerto", 5000);

        for (int i = 0; i < ui->menuPorts->actions().size(); i++) {
            ui->menuPorts->actions()[i]->setChecked(false);
        }
    }

    //LEYENDO Y CREANDO BOTONES
    manager.getPort().write("AT+SIGNALS=?");

    ui->buttonSignals->setEnabled(true);
}


void MainWindow::on_buttonSignals_clicked()
{
    int xToMove = ui->centralwidget->width()/5;
    if(manager.getSignals().size()>0){
        for(int i=0; i < manager.getSignals().size(); i++){
            ButtonSignal* but = new ButtonSignal(manager, manager.getSignals()[i],ui->centralwidget);
            signalsButtons.append(but);
        }
    }
    for(int i{}; i < signalsButtons.size();i++){
        signalsButtons[i]->setVisible(true);
        signalsButtons[i]->resize(ui->buttonSignals->size());
        signalsButtons[i]->move(xToMove,ui->centralwidget->height() - ui->buttonSignals->height() - ui->statusbar->height());

        xToMove += signalsButtons[i]->width()+10;
    }
    ui->buttonSignals->setEnabled(false);

}


void MainWindow::on_pushButtonSTART_clicked()
{
    manager.getPort().write("AT+START");
    ui->pushButtonSTOP->setEnabled(true);
    ui->pushButtonSTART->setEnabled(false);

    for(int i=0; i < signalsButtons.size();i++){
        signalsButtons[i]->setEnabled(false);
    }
}

void MainWindow::activeSTARTandSTOP()
{
    ui->pushButtonSTART->setEnabled(true);
    ui->pushButtonSTART->setVisible(true);
    ui->pushButtonSTOP->setVisible(true);
    ui->pushButtonSTOP->setEnabled(false);

    ui->pushButtonCurrent->setVisible(true);
}


void MainWindow::on_pushButtonSTOP_clicked()
{
    manager.getPort().write("AT+STOP");
    ui->pushButtonSTOP->setEnabled(false);
    ui->pushButtonSTART->setEnabled(true);
}


void MainWindow::on_pushButtonCurrent_clicked()
{
    manager.readVariable = 1;
    manager.getPort().write("AT+CURR");
    //ui->statusbar->showMessage("LA SEÑAL SELECCIONADA ES "+manager.getCurrentSignal(), 7000);
}

void MainWindow::currentSignalInStatusBar()
{
    ui->statusbar->showMessage("LA SEÑAL SELECCIONADA ES "+manager.getCurrentSignal(), 5000);
    manager.readVariable = 0;
}

void MainWindow::paintDataReceived(float dato)
{
    //qDebug() << dato;
    xPosActual++;
    ui->widget->passDataAndPaint(xPosActual, dato * 20);
}

