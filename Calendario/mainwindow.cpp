#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DIMENSION_DIAS 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Exportar,
            SIGNAL(triggered()),
            this,
            SLOT(exportarAPDF()));
    connect(&dialogo,
            SIGNAL(accepted()),
            this,
            SLOT(agregarEventoADia()));

    QDate inicioDeMes(QDate::currentDate().year(),
                      QDate::currentDate().month(),
                      1);
    QDate finalDeMes(QDate::currentDate().year(),
                     QDate::currentDate().month(),
                     QDate::currentDate().daysInMonth());
    //INICIO Y FINAL DE MES , RECALCULAR PARA MOSTRAR UN CALENDARIO ENTERO
    inicioDeMes = inicioDeMes.addDays(-(inicioDeMes.dayOfWeek() -1));
    finalDeMes = finalDeMes.addDays(7 - finalDeMes.dayOfWeek());
    //RESIZE DE WIDGET, Y PANTALLA
    ui->widGCalendario->move(10,10);
    ui->widGCalendario->resize(7*DIMENSION_DIAS,
                               ((inicioDeMes.daysTo(finalDeMes)+1)/7)*DIMENSION_DIAS);

    resize(ui->widGCalendario->width()+170, ui->widGCalendario->height()+ ui->statusbar->height()+20);
    setMaximumSize(ui->widGCalendario->width()+170, ui->widGCalendario->height()+ ui->statusbar->height()+20);
    setMinimumSize(ui->widGCalendario->width()+170, ui->widGCalendario->height()+ ui->statusbar->height()+20);

    // CREACION DE CELDAS Y QFrames
    for (int day = 0; day<inicioDeMes.daysTo(finalDeMes)+1; day++){

        fechas.append(new DiaCalendario(ui->widGCalendario));
        connect(fechas[day], SIGNAL(diaClickeado(int)), this, SLOT(diaSeleccionado(int)));
        connect(fechas[day], SIGNAL(diaHovered(QVector<QString>,int)), this, SLOT(actualizarLabelEventos(QVector<QString>,int)));
        fechas[day]->resize(100,100);
        fechas[day]->setFecha(inicioDeMes.addDays(day).day());
        fechas[day]->move((day%7) * DIMENSION_DIAS, (day/7)*DIMENSION_DIAS);
    }


    //TITULO DE APP
    setWindowTitle("Calendario QT");

}

void MainWindow::diaSeleccionado(int fechaDiaSeleccionado)
{

    for (int i{}; i< fechas.size();++i){
        if(fechas[i]->getFecha() == fechaDiaSeleccionado){
            indiceDiaSeleccionado = i;


            i=fechas.size();
        }
    }
    dialogo.show();
    //qDebug() << "Dia seleccionado";
}

void MainWindow::actualizarLabelEventos(const QVector<QString> &evs, int f)
{
    QString texto = QString::number(f);
    if (evs.size()>0){
        for (int i {}; i<evs.size();++i){
            texto.append("\n"+ evs[i]);
        }
    }else{
        texto.append("\nSin Eventos");
    }
    ui->EventosLabel->setText(texto);
    ui->EventosLabel->adjustSize();
}

void MainWindow::agregarEventoADia()
{
    fechas[indiceDiaSeleccionado]->agregarEvento(dialogo.getEvento());

    manejadorArchivos.setFileName("calendario.txt");
    manejadorArchivos.open(QIODevice::WriteOnly | QIODevice::Text);

    for (int dia{}; dia<fechas.size();dia++){
        manejadorArchivos.write(QByteArray::number(fechas[dia]->getFecha()) + "\n");
        for (int i{}; i<fechas[dia]->cantidadEventosDia();i++) {
            manejadorArchivos.write(fechas[dia]->getEvento(i).toLatin1() + "\n");
        }
    }
    manejadorArchivos.close();
}

void MainWindow::exportarAPDF()
{
    QString html = "";
    QTextDocument documento;
    QPrinter impresora(QPrinter::HighResolution);
    impresora.setOutputFormat(QPrinter::PdfFormat);
    impresora.setOutputFileName(QFileDialog::getSaveFileName(this,"Exportar a PDF","C:\\Users\\iamsr\\Desktop","*.pdf"));
    impresora.setPageMargins(QMargins(20,20,20,20));

    for (int dia {}; dia< fechas.size();++dia){
        html+="<p><b>" + QByteArray::number(fechas[dia]->getFecha()) + "</b></p>";
        if (fechas[dia]->cantidadEventosDia()>0){
            for (int eve{}; eve < fechas[dia]->cantidadEventosDia(); eve++){
                html+="<p>" + fechas[dia]->getEvento(eve) + "</p>";
            }
        }else{
            html+= "<p>Sin Eventos</p>";
        }
    }
    documento.setHtml(html);

    documento.print(&impresora);


    ui->statusbar->showMessage("Archivo exportado.", 3000);
}


MainWindow::~MainWindow()
{
    delete ui;
}


