#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "cargadorimagenes.h"
#include "claseprueba.h"

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

    engine.addImageProvider("provisorDeImagenes", new CargadorImagenes);

    //para invocar desde qml a esta clase de c++ y poder crear objetos
    qmlRegisterType<ClasePrueba> ("itcloud.claseprueba", 1,0, "ClaseDePrueba");

    engine.load(url);

    return app.exec();
}
