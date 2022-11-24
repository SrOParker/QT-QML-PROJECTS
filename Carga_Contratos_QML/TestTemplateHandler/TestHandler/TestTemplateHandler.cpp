
#include <QtTest>
#include "../../templatehandler.h"

struct TestTemplateHandler : public QObject {

    Q_OBJECT
public:
    QStringList obtenerCamposDeArchivo(const QString &file);
    QString obtenerCamposModificados(const QString &file);
private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_obtenerCampos();
    void test_obtenerCampos_data();

    void test_completarCampo();
    void test_completarCampo_data();
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
    // -----------------------------
    QFile testFile3("testFile3.cont");
    testFile3.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream textFile3(&testFile3);

    textFile3 << "Primer texto###campo1### texto###campo2### texto otro texto sabes á. ###campo3###texto\n";
    testFile3.close();
    // -----------------------------
    QFile testFile4("testFile4.cont");
    testFile4.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream textFile4(&testFile4);

    textFile4 << "###campo1### texto###campo2### texto otro texto sabes á. ###campo3###texto\n";
    testFile4.close();
}

void TestTemplateHandler::cleanupTestCase()
{
    QFile::remove("testFile1.cont");
    QFile::remove("testFile2.cont");
    QFile::remove("testFile3.cont");
    QFile::remove("testFile4.cont");


    QFile::remove("testFile1Modificado.txt");
    QFile::remove("testFile2Modificado.txt");
    QFile::remove("testFile3Modificado.txt");
    QFile::remove("testFile4Modificado.txt");
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
    QTest::addRow("archivo3") << "testFile3.cont" << lista;
    QTest::addRow("archivo4") << "testFile4.cont" << lista;

    //             nombreArchivo camposObtenidos
    //archivo1     testFile1.cont ["campo1","campo2","campo3"]
    //archivo2     testFile2.cont ["campo1","campo2","campo3"]
    // ...              ...           ...
}

void TestTemplateHandler::test_completarCampo()
{
    QFETCH(QString, nombreArchivo);
    QFETCH(QString, textoModificado);

    QBENCHMARK{
        QCOMPARE(obtenerCamposModificados(nombreArchivo), textoModificado);
    }
}

void TestTemplateHandler::test_completarCampo_data()
{
    QTest::addColumn<QString>("nombreArchivo");
    QTest::addColumn<QString>("textoModificado");
    QTest::addRow("archivo1") << "testFile1.cont" << "textoPrimer campo modificadotextoEste es el segundo campotextocampitotexto\n";
    QTest::addRow("archivo2") << "testFile2.cont" << "Primer campo modificadotextoEste es el segundo campotextocampitotexto\n";
    QTest::addRow("archivo3") << "testFile3.cont" << "Primer textoPrimer campo modificado textoEste es el segundo campo texto otro texto sabes á. campitotexto\n";
    QTest::addRow("archivo4") << "testFile4.cont" << "Primer campo modificado textoEste es el segundo campo texto otro texto sabes á. campitotexto\n";
    //"###Primer campo modificado### texto###Este es el segundo campo### texto otro texto sabes á. ###campito###texto\n";
}

QStringList TestTemplateHandler::obtenerCamposDeArchivo(const QString &file)
{
    TemplateHandler handler;
    handler.cargarTemplate(file);
    return handler.obtenerCampos();
}

QString TestTemplateHandler::obtenerCamposModificados(const QString &file)
{
    TemplateHandler handler;

    handler.cargarTemplate(file);

    handler.completarCampo("campo1", "Primer campo modificado");
    handler.completarCampo("campo2", "Este es el segundo campo");
    handler.completarCampo("campo3", "campito");

    handler.guardarTXT(file.split(".")[0] + "Modificado.txt");


    QFile archivoModificado(file.split(".")[0] + "Modificado.txt");
    archivoModificado.open(QIODevice::ReadOnly | QIODevice::Text);
    QString textoModificado = archivoModificado.readAll();
    archivoModificado.close();

    return textoModificado;
}






















QTEST_MAIN(TestTemplateHandler);
#include "TestTemplateHandler.moc"

