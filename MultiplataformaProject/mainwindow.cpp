#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SystemInfo::instancia().init();
    connect(&timer,
            SIGNAL(timeout()),
            this,
            SLOT(actualizarLabel()));
    timer.start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarLabel()
{
    ui->datosSistemaLabel->setText(QString::number(SystemInfo::instancia().cpuLoad()) + "%");
}

