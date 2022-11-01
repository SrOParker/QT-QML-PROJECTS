#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QFileDialog>
#include <QScrollArea>
#include <QMap>
#include <QMapIterator>
#include <QtPrintSupport/QPrinter>
#include "listacampos.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ListaCampos *campos;

    QVector<QVector<int>> indicesCampos;

    QStringList partesPlantilla;

protected:
    void resizeEvent(QResizeEvent* event);
public slots:
    void abrirPlantilla();
    void generarPdf();
};
#endif // MAINWINDOW_H
