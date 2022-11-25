#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "archivemanagerinterface.h"

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
    qmlRegisterType<ArchiveManagerInterface>("ArchiveManager.Interface",1,0,"ArchiveManager");
    //ArchiveManager archive;

    //archive.readFromTXT("ECG.txt");
    //archive.startSerialCom("ECS.txt", "COM1", 500, QSerialPort::Baud9600);

    //archive.readFromTXT("ECG.txt");
    //archive.startTimer(2);
    engine.load(url);

    return app.exec();
}


//main -> start -> ECG.txt, COM1, 500, QSerialPort::Baud9600
