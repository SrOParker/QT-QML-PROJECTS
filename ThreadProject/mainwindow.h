#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonA_clicked();

    void on_pushButtonB_clicked();

    void on_pushButtonSalir_clicked();

    void updateLabelA(const QString& newText );

    void updateLabelB(const QString& newText );

private:
    Ui::MainWindow *ui;

    Thread threadA;
    Thread threadB;
};
#endif // MAINWINDOW_H
