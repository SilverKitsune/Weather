#include <QCoreApplication>
#include <include/parser.h>

#include <QString>
#include <QTextStream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName="C:\\Users\\kicha\\Documents\\Diplom\\grib files\\gfs20200112200203822.grb";//



    Parser parser;
    QList<QList<paramData>> test;
    string type="Temp";
    //Устанавливаем файл для чтения
    parser.setFile(fileName);
    //Получаем данные по временным промежуткам. Каждый элемент содержит координату точки, значение параметра и дату
    test=parser.parameterData(type);
    return a.exec();
}
