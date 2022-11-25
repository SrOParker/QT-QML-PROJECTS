#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "archivemanagerreceiver.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    ArchiveManagerReceiver archive;

    //archive.readFromTXT("ECG.txt");
    archive.startSerialCom("COM2",  QSerialPort::Baud9600);
    archive.startTimer(20);


    engine.load(url);

    return app.exec();
}
