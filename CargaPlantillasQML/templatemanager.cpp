#include "templatemanager.h"

#include <QDebug>

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

QVector<QString> TemplateManager::getCampos()
{
    return campos;
}

std::size_t TemplateManager::getCamposSize()
{
    return campos.size();
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
