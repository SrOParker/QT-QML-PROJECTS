#include "templatehandler.h"

TemplateHandler::TemplateHandler()
{

}

bool TemplateHandler::cargarTemplate(const QString &file)
{
    QFile archivo(file);

    if(archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        //Leemos el texto entero
        QString textoleido = archivo.readAll();
        //Separamos el texto en partes y lo guardamos
        partesPlantilla = textoleido.split("###");
        //Elegimos el inicio del texto

        for(int campoParaCompletar =1; campoParaCompletar<partesPlantilla.size() ;campoParaCompletar+=2){
            //Corroboramos que el campo no exista. Que no haya sido leído previamente
            //Si no existe lo creamos
            if (!tagsCampos.contains(partesPlantilla[campoParaCompletar])){
                tagsCampos.append(partesPlantilla[campoParaCompletar]);
                campos[partesPlantilla[campoParaCompletar]] = "";
            }
            //Si existe nos da igual por que ya esta guardado
        }
        return true;
    }else{
        return false;
    }
}

QStringList TemplateHandler::obtenerCampos()
{
    return tagsCampos;
}

void TemplateHandler::completarCampo(const QString &campo, const QString &contenido)
{
        campos[campo] = contenido;
}

bool TemplateHandler::guardar(const QString &file)
{

}

