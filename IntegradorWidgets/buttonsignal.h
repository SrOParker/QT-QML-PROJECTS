#ifndef BUTTONSIGNAL_H
#define BUTTONSIGNAL_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include "manejador.h"
class ButtonSignal : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonSignal(QWidget *parent = nullptr);
    ButtonSignal(Manejador& man,QString name, QWidget *parent = nullptr);

private:
    Manejador* manager;
signals:


    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // BUTTONSIGNAL_H
