#ifndef CAMPO_H
#define CAMPO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class Campo : public QWidget{
    Q_OBJECT
public:
    explicit Campo(QWidget * parent=nullptr);
    void setLabelText(QString text);
    QString getLabelText();
    QString getLineEditText();
private:
    QLabel name_;
    QLineEdit line_edit_campo_;
protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // CAMPO_H
