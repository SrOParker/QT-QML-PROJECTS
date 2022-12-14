#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "archivemanagerreceiverinterface.h"
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
    qmlRegisterType<ArchiveManagerReceiverInterface>("archivemanager.receiver.interface",1,0,"ReceiverData");
    ArchiveManagerReceiver archive;

    //archive.readFromTXT("ECG.txt");
    archive.startSerialCom("COM3",  QSerialPort::Baud115200);
    archive.startTimer(20);


    engine.load(url);

    return app.exec();
}
