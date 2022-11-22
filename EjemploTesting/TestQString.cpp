#include <QtTest>

class TestQString : public QObject{
    Q_OBJECT

private slots:
    void textToUpper();
    void textToUpper_data();

    void textToLower();

};

void TestQString::textToUpper(){
    //QString str = "Hola mundo";

    //PROBANDO QUE FUNCIONA

    //QVERIFY(str.toUpper() == "HOLA MUNDO");
    //QCOMPARE(str.toUpper(), "HOLA MUNDO");
    QFETCH(QString, original);
    QFETCH(QString, cambiadoAMayusculas);
    QBENCHMARK{
        QCOMPARE(original.toUpper(), cambiadoAMayusculas);
    }

}
void TestQString::textToUpper_data(){
    QTest::addColumn<QString>("original");
    QTest::addColumn<QString>("cambiadoAMayusculas");
    QTest::addRow("todoEnMinuscula") << "hola mundo" << "HOLA MUNDO";
    QTest::addRow("mYMAlternadas") << "HoLa muNdo" << "HOLA MUNDO";
    QTest::addRow("todoEnMayuscula") << "HOLA MUNDO" << "HOLA MUNDO";
    // num nombre original cambiado
    //   0 todoE. hola mun HOLA MUN
    //   1 mYMAlt HoLa mUn HOLA MUN
    //   2 todoEM HOLA MUN HOLA MUN
}

void TestQString::textToLower(){
    QString str ="Hey";
    QVERIFY(str.toLower() == "hey");
}

QTEST_MAIN(TestQString);
#include "TestQString.moc"
