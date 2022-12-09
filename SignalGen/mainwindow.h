#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

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

    QSerialPort port;

    QStringList signalNames;

    QTimer timer;

    QList< QList< float > > signalValues;

    int signal;
    int dataIndex;

private slots:
    void portActionTriggered(QAction* action);

    void readData();
    void sendData();
};
#endif // MAINWINDOW_H
