
#include <QtTest>
#include "../../templatehandler.h"

struct TestTemplateHandler : public QObject {

    Q_OBJECT
public:
    QStringList obtenerCamposDeArchivo(const QString &file);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_obtenerCampos();
    void test_obtenerCampos_data();

};

void TestTemplateHandler::initTestCase()
{
    QFile testFile1("testFile1.cont");
    testFile1.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream textFile1(&testFile1);

    textFile1 << "texto###campo1###texto###campo2###texto###campo3###texto\n";
    testFile1.close();
    // -----------------------------
    QFile testFile2("testFile2.cont");
    testFile2.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream textFile2(&testFile2);

    textFile2 << "###campo1###texto###campo2###texto###campo3###texto\n";
    testFile2.close();
}

void TestTemplateHandler::cleanupTestCase()
{
    QFile::remove("testFile1.cont");
    QFile::remove("testFile2.cont");
}

void TestTemplateHandler::test_obtenerCampos()
{
    QFETCH(QString, nombreArchivo);
    QFETCH(QStringList, camposObtenidos);

    QBENCHMARK{
        QCOMPARE(obtenerCamposDeArchivo(nombreArchivo), camposObtenidos);
    }
}

void TestTemplateHandler::test_obtenerCampos_data()
{
    QTest::addColumn<QString>("nombreArchivo");
    QTest::addColumn<QStringList>("camposObtenidos");

    QStringList lista;
    lista.append("campo1");
    lista.append("campo2");
    lista.append("campo3");

    QTest::addRow("archivo1") << "testFile1.cont" << lista;
    QTest::addRow("archivo2") << "testFile2.cont" << lista;

    //             nombreArchivo camposObtenidos
    //archivo1     testFile1.cont ["campo1","campo2","campo3"]
    //archivo2     testFile2.cont ["campo1","campo2","campo3"]
}

QStringList TestTemplateHandler::obtenerCamposDeArchivo(const QString &file)
{
    TemplateHandler handler;
    handler.cargarTemplate(file);
    return handler.obtenerCampos();
}


QTEST_MAIN(TestTemplateHandler);
#include "TestTemplateHandler.moc"
