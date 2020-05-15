#include <QCoreApplication>
#include <include/parser.h>

#include <QString>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName="C:\\Users\\kicha\\Documents\\Diplom\\grib files\\gfs20200112200203822.grb";//

    Parser parser;
//Проверка постой библиотки
    QList<uniData> test;
    test = parser.parse(fileName);
    return a.exec();
}
