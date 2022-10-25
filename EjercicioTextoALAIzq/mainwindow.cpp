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
}


MainWindow::~MainWindow()
{
    for (int i = textos.size()-1; i>=0;i--){
        delete textos[i];
        textos.pop_back();
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
    //for (int i = textos.size()-1; i>=0;i--){
    //    delete textos[i];
    //    textos.pop_back();
    //}
    //for (int i = 0; i<selected.size();i++){
    //    textos[selected[i]]->setText("");
    //}
    //for (int i = 0; i<textos.size();i++){
    //    if (textos[i]->text()==""){
    //        for (int j=i;j<textos.size();j++){
    //            if (textos[j]->text()!=""){
    //                textos[i] = textos[j];
    //                textos[j]->setText("");
    //            }
    //        }
    //        if (i==textos.size()-1 && textos[i]->text()==""){
    //            textos[i]->setText("");
    //        }
    //    }
    //}
    //selected.clear();
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
    int count=0;
    for (int i=0;i<selected.size();i++) {
        if (selected[i] == pos){
            if (selected.size()>=1){
                selected[i] = selected[selected.size()-1];
                selected.pop_back();
                textos[pos]->setStyleSheet("QLabel {background:none;}");

                count++;
            }else{
                selected.pop_back();
                textos[i]->setStyleSheet("QLabel {background:none;}");
                count++;
            }

        }
    }
    if (count==0){
        selected.append(pos);
        textos[pos]->setStyleSheet("QLabel{ background: red;}");
    }
    for (int i=0;i<selected.size();i++){
        qDebug()<< selected[i] << " ";
    }qDebug()<<"\n Size:"<<selected.size() <<"\n";


}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    for (int i{}; i<textos.size();++i){
        if (textos[i]->underMouse()){
            emit on_linkHovered(i);
        }
    }
}
