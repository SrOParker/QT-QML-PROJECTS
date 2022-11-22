#ifndef TEMPLATEHANDLER_H
#define TEMPLATEHANDLER_H

#include <QString>
#include <QFile>
#include <QMap>


class TemplateHandler
{
public:
    TemplateHandler();

    //Abre la plantilla. si puede true si no false
    bool        cargarTemplate(const QString &file);

    //Devuelve la lista de campos
    QStringList obtenerCampos();

    //
    void        completarCampo(const QString &campo, const QString &contenido);

    //
    bool        guardar(const QString &file);
private:



    //VARIABLES DE CLASE

    // Toda la plantilla dividida por ### en un vector de strings
    QStringList partesPlantilla;

    // Par de valores para cada campo con su textfield
    QMap<QString, QString> campos;

    // Nombres de los campos a rellenar
    QStringList tagsCampos;
};

#endif // TEMPLATEHANDLER_H
