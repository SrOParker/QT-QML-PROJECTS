#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "archivemanagerreceiver.h"

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
    ArchiveManagerReceiver aMr_;
    // QWidget interface
private slots:
    void agregarDato(const QVariantList &nuevosDatos);
protected:
    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
