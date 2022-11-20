#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H

#include <QObject>
#include <QFile>


class TemplateManager : public QObject
{
    Q_OBJECT
public:
    explicit TemplateManager(QObject *parent = nullptr);
    Q_INVOKABLE void openTemplate(QString path);
    Q_INVOKABLE QVector<QString> getCampos();
    Q_INVOKABLE std::size_t getCamposSize();

    int encontrar(QString nombre);
    QVector<QVector<int>> indicesCampos;
    QStringList partesPlantilla;
    QVector<QString> campos;
signals:

};

#endif // TEMPLATEMANAGER_H
