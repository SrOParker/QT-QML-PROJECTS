#include "buttonsignal.h"

ButtonSignal::ButtonSignal(QWidget *parent)
    : QPushButton{parent}
{

}

ButtonSignal::ButtonSignal(Manejador& man, QString name, QWidget *parent) : QPushButton {parent}
{
    manager = &man;
    this->setText(name);
}

void ButtonSignal::mouseReleaseEvent(QMouseEvent *event)
{
    emit manager->activablesSTARTySTOP();
    QByteArray c =("AT+SIGNAL=" + this->text()).toLatin1();
    manager->getPort().write(c);

}
