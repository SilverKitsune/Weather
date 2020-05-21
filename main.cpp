#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

  /*  QCoreApplication a(argc, argv);
        QString fileName="C:\\Users\\Allo4ka\\Downloads\\Telegram Desktop\\gfs20200112200203822.grb";//
        Parser parser;
        QList<QList<paramData>> test;
        string type="Temp";
        //Устанавливаем файл для чтения
        parser.setFile(fileName);
        //Получаем данные по временным промежуткам. Каждый элемент содержит координату точки, значение параметра и дату
        test=parser.parameterData(type);
        return a.exec();*/
}
