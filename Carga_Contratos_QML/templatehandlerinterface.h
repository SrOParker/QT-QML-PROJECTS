#ifndef TEMPLATEHANDLERINTERFACE_H
#define TEMPLATEHANDLERINTERFACE_H

#include <QObject>
#include "templatehandler.h"
class TemplateHandlerInterface : public QObject
{
    Q_OBJECT
public:
    explicit TemplateHandlerInterface(QObject *parent = nullptr);

    Q_INVOKABLE bool        cargarTemplate(const QString &file);
    Q_INVOKABLE QStringList obtenerCampos();
    Q_INVOKABLE void        completarCampo(const QString &campo, const QString &contenido);
    Q_INVOKABLE bool        guardarTXT(const QString &file);
    Q_INVOKABLE void        guardarPDF(const QString &file);
    Q_INVOKABLE QString     getCampo(const QString key);
    Q_INVOKABLE int         cantidadCampos();
private:
    TemplateHandler handler;
signals:

};

#endif // TEMPLATEHANDLERINTERFACE_H
