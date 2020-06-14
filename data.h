#ifndef DATA_H
#define DATA_H

#include "pointdata.h"
#include "parser.h"

class Data
{
public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int Ni = 7; //*
    int Nj = 7; //*
   // string typeOfParameter = "Temp";
    QList<PointData> *pD;

    Data();
    ~Data();
    static QList<Data>* readData(QString fileName);

    /*void setTypeOfParameter(string type) {typeOfParameter = type;}
    string getTypeOfParameter() {return typeOfParameter;}*/
};

#endif // DATA_H
