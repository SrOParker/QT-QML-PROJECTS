#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>

class TemplateManager : public QObject
{
    Q_OBJECT
public:
    explicit TemplateManager(QObject *parent = nullptr);
    Q_INVOKABLE void openTemplate(QString path);
    Q_INVOKABLE void exportarAPdf();

    Q_INVOKABLE QVector<QString> getCampos();
    Q_INVOKABLE void addCampoRelleno(QString str);
    int encontrar(QString nombre);


    QVector<QVector<int>> indicesCampos;
    QStringList partesPlantilla;
    QVector<QString> campos;
    QVector<QString> camposRellenos;
    QTextDocument document;
    QString html;
signals:

};

#endif // TEMPLATEMANAGER_H
