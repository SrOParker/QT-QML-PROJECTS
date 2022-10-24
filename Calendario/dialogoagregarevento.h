#ifndef DIALOGOAGREGAREVENTO_H
#define DIALOGOAGREGAREVENTO_H

#include <QDialog>

namespace Ui {
class DialogoAgregarEvento;
}

class DialogoAgregarEvento : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoAgregarEvento(QWidget *parent = nullptr);
    ~DialogoAgregarEvento();
    QString getEvento();

    void show();
private:
    Ui::DialogoAgregarEvento *ui;
};

#endif // DIALOGOAGREGAREVENTO_H
