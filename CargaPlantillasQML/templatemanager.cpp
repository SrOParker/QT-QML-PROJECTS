#include "templatemanager.h"

TemplateManager::TemplateManager(QObject *parent)
    : QObject{parent}
{

}

void TemplateManager::openTemplate(QString path)
{

    QFile plantilla;
        path = path.split("///")[1];
        qDebug() << path;
        QVector<QString> parts = path.split("/");
        path="";
        for(int i=0; i<parts.size();i++){
            if (i == parts.size()-1){
                path += parts[i];
            }else{
                path += parts[i] + "//";
            }
        }qDebug() << path;
        plantilla.setFileName(path);

        if ( plantilla.open(QIODevice::ReadOnly) ) {

            QString texto( plantilla.readAll() );

            plantilla.close();

            partesPlantilla = texto.split("###");

            int campoParaCompletar = 1;

            if (texto.startsWith("###")) {
                campoParaCompletar = 0;

            }

            for (; campoParaCompletar < partesPlantilla.size(); campoParaCompletar += 2) {

                int indiceCampo = encontrar(partesPlantilla[campoParaCompletar]);

                if (indiceCampo >= 0) {

                    indicesCampos[indiceCampo].append(campoParaCompletar);

                }
                else {

                    campos.append(partesPlantilla[campoParaCompletar]);

                    QVector<int> nuevoVector;
                    nuevoVector.append(campoParaCompletar);

                    indicesCampos.append(nuevoVector);
                }
            }

            //ui->statusbar->showMessage("Plantilla cargada correctamente.", 3000);
            qDebug() << ("SE LEE");
        }else {
            //ui->statusbar->showMessage("Plantilla no especificada.", 3000);
            qDebug() << ("NO SE LEE");
        }
}

void TemplateManager::exportarAPdf()
{
    for (int campo = 0; campo < indicesCampos.size(); campo++) {
        for (int indice = 0; indice < indicesCampos[campo].size(); indice++) {
            partesPlantilla[ indicesCampos[campo][indice] ] = camposRellenos[campo];
            qDebug() << camposRellenos[campo];
        }
    }

    partesPlantilla.replaceInStrings("\n", "<br>");
    partesPlantilla.replaceInStrings("\r", "<br>");

    html = "";

    for (int i = 0; i < partesPlantilla.size(); i++) {
        html += partesPlantilla[i];
    }

    //QTextDocument documento;
    qDebug()<<html;
    //QPrinter impresora(QPrinter::PrinterMode::HighResolution);
    //impresora.setColorMode(QPrinter::Color);
    //impresora.setOutputFormat(QPrinter::PdfFormat);
    //impresora.setOutputFileName( "archivo.pdf" );
    //impresora.setPageMargins(QMargins(10, 20, 10, 15));

    //if (impresora.outputFileName().endsWith(".pdf")) {
    //    documento.setHtml(html);

    //    documento.print(&impresora);


    //    //ui->statusbar->showMessage("Archivo exportado correctamente.", 3000);
    //}

    //else {
    //    //ui->statusbar->showMessage("Nombre de archivo no especificado.", 3000);
    //}
}

QVector<QString> TemplateManager::getCampos()
{
    return campos;
}

void TemplateManager::addCampoRelleno(QString str)
{
    camposRellenos.append(str);
}



int TemplateManager::encontrar(QString nombre)
{
    int indice = -1;
    for (int i {}; i<campos.size();++i){
        if (campos[i] == nombre){
            indice = i;
        }
    }
    return indice;
}

