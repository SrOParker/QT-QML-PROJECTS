#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <QWidget>

namespace Ui {
class Calendario;
}

class Calendario : public QWidget
{
    Q_OBJECT

public:
    explicit Calendario(QWidget *parent = nullptr);
    ~Calendario();

private:
    Ui::Calendario *ui;

};

#endif // CALENDARIO_H
