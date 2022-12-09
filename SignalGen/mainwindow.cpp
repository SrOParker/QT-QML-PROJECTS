#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    for (int i = 0; i < availablePorts.size(); i++) {
        ui->menuSerialPorts->addAction(availablePorts[i].portName());

        ui->menuSerialPorts->actions()[i]->setCheckable(true);
    }

    setWindowTitle("Signal Generator");

    signal = 0;
    dataIndex = 0;

    signalNames.append("RAND");
    signalNames.append("TRIANGULAR");
    signalNames.append("SINE");
    signalNames.append("SQUARE");

    signalValues.resize(4);

    for (int i = 0; i < 50; i++) {
        signalValues[0].append(((rand() % 201) / 100.0) + 1.5);
    }

    for (int i = 0; i < 50; i++) {
        signalValues[1].append(i / 10.0);
    }

    for (int i = 0; i < 50; i++) {
        signalValues[2].append(sin(i * 2.0 * 3.141592 * 0.02));
    }

    for (int i = 0; i < 50; i++) {
        signalValues[3].append(i < 25 ? 0 : 4.5);
    }

    connect(ui->menuSerialPorts, SIGNAL(triggered(QAction*)), this, SLOT(portActionTriggered(QAction*)));
    connect(&port, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendData()));
}

MainWindow::~MainWindow()
{
    port.close();
    delete ui;
}

void MainWindow::portActionTriggered(QAction *action)
{
    for (int i = 0; i < ui->menuSerialPorts->actions().size(); i++) {
        if (ui->menuSerialPorts->actions()[i] != action)
        {
            ui->menuSerialPorts->actions()[i]->setChecked(false);
        }
    }

    if (port.isOpen()) {
        port.close();
    }

    port.setPortName(action->text());
    port.setBaudRate(QSerialPort::Baud115200);

    if (port.open(QIODeviceBase::ReadWrite)) {
        ui->statusbar->showMessage("Puerto abierto exitosamente", 5000);
    }
    else {
        ui->statusbar->showMessage("Error al abrir puerto", 5000);

        for (int i = 0; i < ui->menuSerialPorts->actions().size(); i++) {
            ui->menuSerialPorts->actions()[i]->setChecked(false);
        }
    }
}

void MainWindow::readData()
{
    QByteArray message;

    while (port.bytesAvailable()) {
        message.append(port.readAll());
    }

    if (message.contains("AT+SIGNALS=?")) {
        for (int i = 0; i < signalNames.size(); i++) {
            port.write("AT+" + signalNames[i].toLatin1());
            port.write("\r\n");
        }
    }
    else if (message.contains("AT+CURR")) {
        port.write("AT+" + signalNames[signal].toLatin1());
        port.write("\r\n");
    }
    else if (message.contains("AT+SIGNAL=RAND")) {
        signal = 0;
        port.write("AT+OK\r\n");
    }
    else if (message.contains("AT+SIGNAL=TRIANGULAR")) {
        signal = 1;
        port.write("AT+OK\r\n");
    }
    else if (message.contains("AT+SIGNAL=SINE")) {
        signal = 2;
        port.write("AT+OK\r\n");
    }
    else if (message.contains("AT+SIGNAL=SQUARE")) {
        signal = 3;
        port.write("AT+OK\r\n");
    }
    else if (message.contains("AT+START")) {
        timer.start(100);
        port.write("AT+OK\r\n");
    }
    else if (message.contains("AT+STOP")) {
        timer.stop();
        port.write("AT+OK\r\n");
    }
    else if (message.contains("AT+MAX")) {
        timer.stop();
        port.write("AT+VALUE=5.00\r\n");
    }
    else if (message.contains("AT+MIN")) {
        timer.stop();
        port.write("AT+VALUE=0.00\r\n");
    }
    else {
        port.write("AT+ERROR\r\n");
    }
}

void MainWindow::sendData()
{
    port.write("AT+VALUE=" + QByteArray::number(signalValues[signal][dataIndex]) + "\r\n");

    dataIndex = (dataIndex < (signalValues[signal].size() - 1)) ? (dataIndex + 1) : 0;
}

