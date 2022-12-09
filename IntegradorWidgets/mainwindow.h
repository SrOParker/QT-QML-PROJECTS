#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "manejador.h"
#include "buttonsignal.h"
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
    void portActionTriggered(QAction* action);

    void on_buttonSignals_clicked();

    void on_pushButtonSTART_clicked();

    void activeSTARTandSTOP();
    void on_pushButtonSTOP_clicked();

    void on_pushButtonCurrent_clicked();

    void currentSignalInStatusBar();
private:
    Ui::MainWindow *ui;

    Manejador manager;

    QVector<ButtonSignal*> signalsButtons;



};
#endif // MAINWINDOW_H
