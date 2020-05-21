#ifndef DATA_H
#define DATA_H

#include "pointdata.h"
#include "parser.h"
class Data
{

  /*  int Ni; //количество точек вдоль параллели
    int Nj; //количество точек вдоль меридиана
    int fi_begin;
    int la_begin;
    int fi_end;
    int la_end;
    int Di; //приращение по i
    int Dj; //приращение по j */

    int year;
    int month;
    int day;
    int hour;
    int minute;
   // string typeOfParameter = "Temp";
    QList<paramData> pointsData;

public:

    Data();
    static QList<Data>* readData(QString fileName);

    /*void setTypeOfParameter(string type) {typeOfParameter = type;}
    string getTypeOfParameter() {return typeOfParameter;}*/
};

#endif // DATA_H
