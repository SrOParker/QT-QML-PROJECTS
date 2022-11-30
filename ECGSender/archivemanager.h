#ifndef ARCHIVEMANAGER_H
#define ARCHIVEMANAGER_H
#include <QObject>
#include <QFile>
#include <QTimer>

#include <QDebug>
#include <QtSerialPort/QSerialPort>
class ArchiveManager : public QObject
{
    Q_OBJECT
public:
    explicit ArchiveManager(QObject *parent = nullptr);

    void readFromTXT(const QString &file);
    double getOneInData(int position);
    QString getOneInDataS(int position);
    QVector<double> getAllData();
    void startTimer(int n);

    void startSerialCom(const QString &file, const QString &port, float timerVel, QSerialPort::BaudRate baud);
    void stopSerialCom();
    void resetPositionRec();
protected:
    void addToData(double d, QString str);

    QVector<double> data;
    QVector<QString> dataString;
    QTimer timer;
    int position;
    QSerialPort port;
signals:
    void started();
    void portError();
protected slots:
    void sendValue();

};

#endif // ARCHIVEMANAGER_H

