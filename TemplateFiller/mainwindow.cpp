#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    campos = new ListaCampos();
    ui->listWidget->setWidget(campos);

    connect(ui->actionRead_Template, SIGNAL(triggered()), this, SLOT(abrirPlantilla()));
    connect(ui->pushButtonGenerar, SIGNAL(clicked()), this, SLOT(generarPdf()));

}

MainWindow::~MainWindow()
{
    delete campos;

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->listWidget->resize(this->size().width() - 20, this->size().height() - 100);
    ui->listWidget->move(10,10);
    ui->pushButtonGenerar->move(width() - (ui->pushButtonGenerar->width() +10), ui->listWidget->height()+20);
}

void MainWindow::abrirPlantilla()
{
    QFile plantilla;

        plantilla.setFileName(QFileDialog::getOpenFileName(this, "Abrir", "", "*.cont"));

        if ( plantilla.open(QIODevice::ReadOnly) ) {
            QString texto( plantilla.readAll() );

            plantilla.close();

            partesPlantilla = texto.split("###");

            int campoParaCompletar = 1;

            if (texto.startsWith("###")) {
                campoParaCompletar = 0;
            }

            for (; campoParaCompletar < partesPlantilla.size(); campoParaCompletar += 2) {
                int indiceCampo = campos->encontrar(partesPlantilla[campoParaCompletar]);

                if (indiceCampo >= 0) {
                    indicesCampos[indiceCampo].append(campoParaCompletar);
                }
                else {
                    campos->addCampos(partesPlantilla[campoParaCompletar]);

                    QVector<int> nuevoVector;
                    nuevoVector.append(campoParaCompletar);

                    indicesCampos.append(nuevoVector);
                }
            }

            ui->statusbar->showMessage("Plantilla cargada correctamente.", 3000);
        }

        else {
            ui->statusbar->showMessage("Plantilla no especificada.", 3000);
        }
}

void MainWindow::generarPdf()
{
    for (int campo = 0; campo < indicesCampos.size(); campo++) {
        for (int indice = 0; indice < indicesCampos[campo].size(); indice++) {
            partesPlantilla[ indicesCampos[campo][indice] ] = campos->textAt(campo);
        }
    }

    partesPlantilla.replaceInStrings("\n", "<br>");
    partesPlantilla.replaceInStrings("\r", "<br>");

    QString html = "";

    for (int i = 0; i < partesPlantilla.size(); i++) {
        html += partesPlantilla[i];
    }

    QTextDocument documento;

    QPrinter impresora(QPrinter::HighResolution);
    impresora.setOutputFormat(QPrinter::PdfFormat);
    impresora.setOutputFileName( QFileDialog::getSaveFileName(this, "Exportar a PDF", "C:\\Users\\iamsr\\Desktop", "*.pdf") );
    impresora.setPageMargins(QMargins(10, 20, 10, 15));

    if (impresora.outputFileName().endsWith(".pdf")) {
        documento.setHtml(html);

        documento.print(&impresora);

        ui->statusbar->showMessage("Archivo exportado correctamente.", 3000);
    }

    else {
        ui->statusbar->showMessage("Nombre de archivo no especificado.", 3000);
    }
}












