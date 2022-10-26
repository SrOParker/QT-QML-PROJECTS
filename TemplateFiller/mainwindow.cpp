#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui initialization
    ui->pushButtonGenerar->hide();
    ui->listWidget->move(10,10);
    ui->listWidget->resize(this->size().width()-20, this->size().height()-80);

    ui->widgetInSArea->move(10,10);
    ui->widgetInSArea->resize(this->size().width()-20, this->size().height()-80);
    //set widget list a list
    //ui->widgetInSArea->setLayout(main_list_.getLayout());
    //ui->listWidget->setWidget(ui->widgetInSArea);

    main_list_.addCampos(new Campo("hola1"));
    main_list_.addCampos(new Campo("hola2"));
    main_list_.addCampos(new Campo("hola3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->listWidget->resize(this->size().width() - 20, this->size().height() - 80);
    ui->widgetInSArea->resize(this->size().width() - 20, this->size().height() - 80);
}

