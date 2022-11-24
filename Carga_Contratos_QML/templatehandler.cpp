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
    if (tagsCampos.contains(campo)){
        campos[campo] = contenido;
    }
}

void TemplateHandler::guardarPDF(const QString &file)
{
    for(int i = 1; i < partesPlantilla.size(); i+=2){
        partesPlantilla[i] = campos[partesPlantilla[i]];
    }

    QString html = partesPlantilla.join("");
    html.replace("\r", "<br>");
    html.replace("\n", "<br>");

    QTextDocument documento;
    documento.setHtml(html);

    QPrinter impresora(QPrinter::HighResolution);
    impresora.setOutputFormat(QPrinter::PdfFormat);
    impresora.setOutputFileName(file);
    impresora.setPageMargins(QMargins(10,20,10,15));

    documento.print(&impresora);
    documento.isEmpty();
}

QString TemplateHandler::getCampo(const QString key)
{
    return campos[key];
}

int TemplateHandler::cantidadCampos()
{
    return campos.size();
}

bool TemplateHandler::guardarTXT(const QString &file)
{
    for(int i = 1; i < partesPlantilla.size(); i+=2){
        partesPlantilla[i] = campos[partesPlantilla[i]];
    }
    //Archivo de texto
    QFile archivo(file);
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream textoArchivo(&archivo);
        textoArchivo << partesPlantilla.join("");
        //join("") de QStringList une todos los strings de la lista en un solo string

        archivo.close();
        return true;
    }else return false;
}
