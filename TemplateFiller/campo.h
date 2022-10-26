#ifndef CAMPO_H
#define CAMPO_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class Campo : public QWidget{
    Q_OBJECT
public:
    explicit Campo(QWidget * parent);
    Campo();
    Campo(QString n);
private:
    QLabel name_;
    QLineEdit line_edit_campo_;
};

#endif // CAMPO_H
