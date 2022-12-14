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
    float getOneInData(int position);
    QString getOneInDataS(int position);
    QVector<float> getAllData();
    void startTimer(int n);


    void resetPositionRec();
protected:
    void addToData(float d, QString str);

    QVector<float> data;
    QVector<QString> dataString;
    QTimer timer;
    int position;
    QSerialPort port;
public slots:
    void startSerialCom(const QString &file, const QString &port, float timerVel, QSerialPort::BaudRate baud);
    void stopSerialCom();
signals:
    void started();
    void stopped();
    void portError();
protected slots:
    void sendValue();

};

#endif // ARCHIVEMANAGER_H

