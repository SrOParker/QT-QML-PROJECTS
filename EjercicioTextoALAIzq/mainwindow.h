#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseReleaseEvent(QMouseEvent *e);
private slots:
    void on_pushButtonToLeft_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonSave_clicked();

    void on_linkHovered(int pos);


private:
    Ui::MainWindow *ui;
    QString textInDrc;
    QVector<QLabel*> textos;
    QVector<int> selected;

signals:
    void hovered_label();
};
#endif // MAINWINDOW_H
