#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setStyleSheet("QTextEdit { background:white; border: 1px solid black;}");
    ui->labelIZQ->setStyleSheet("QLabel { background:white; border: 1px solid black;}");

    ui->textEdit->resize(300, 500);
    ui->labelIZQ->resize(ui->textEdit->size());
    resize(800,600);
    setMinimumSize(800,600);
    setMaximumSize(800,600);

    setMouseTracking(true);
    ui->pushButtonESelected->setEnabled(false);
}


MainWindow::~MainWindow()
{
    for (int i = textos.size()-1; i>=0;i--){
        delete textos[i];
    }
    delete ui;
}


void MainWindow::on_pushButtonToLeft_clicked()
{
    textos.append(new QLabel(ui->textEdit->toPlainText(), ui->widget));
    textos[textos.size()-1]->adjustSize();
    textos[textos.size()-1]->move(3, (textos.size()-1)*textos[textos.size()-1]->height());
    textos[textos.size()-1]->show();


}


void MainWindow::on_pushButtonClear_clicked()
{

    for(int i {}; i<textos.size();i++){
        delete textos[i];

    }
    textos.clear();

}


void MainWindow::on_pushButtonSave_clicked()
{

    QFile manejadorArchivos;
    manejadorArchivos.setFileName("textoGuardado.txt");
    manejadorArchivos.open(QIODevice::WriteOnly | QIODevice::Text);
    for (int i =0;i<textos.size();i++){
        manejadorArchivos.write(textos[i]->text().toLatin1()+"\n");
    }
    manejadorArchivos.close();

    ui->statusbar->showMessage("Texto guardado", 2000);
}


void MainWindow::on_linkHovered(int pos)
{
    if(selected.contains(pos)){
        textos[pos]->setStyleSheet("QLabel { background-color:none; }");
        selected.remove(selected.indexOf(pos));
        if (selected.isEmpty()){
            ui->pushButtonESelected->setEnabled(false);
        }
    }else{
        textos[pos]->setStyleSheet("QLabel { background-color: green; }");
        selected.append(pos);
        ui->pushButtonESelected->setEnabled(true);
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    for (int i{}; i<textos.size();++i){
        if (textos[i]->underMouse()){
            on_linkHovered(i);
        }
    }
}


void MainWindow::on_pushButtonESelected_clicked()
{
    for(int i{}; i < selected.size() ; i++){
        for(int j{}; j < (selected.size()-1); j++){
            if (selected[j] > selected[j+1]){
                int aux = selected[j];
                selected[j] = selected [j+1];
                selected[j+1] = aux;
            }
        }
    }

    int cantidadBorrados=0;
    for (int i=0;i<selected.size();i++){
        delete textos[selected[i]-cantidadBorrados];
        textos.remove(selected[i]-cantidadBorrados);
        cantidadBorrados++;
    }
    for (int i=0;i<textos.size();i++){
        textos[i]->move(0, i*textos[i]->height());
    }

    selected.clear();
}









