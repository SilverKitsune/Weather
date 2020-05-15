#ifndef DATA_H
#define DATA_H

#include <QVector>
#include "pointdata.h"
class Data
{
    int Ni; //количество точек вдоль параллели
    int Nj; //количество точек вдоль меридиана
    int fi_begin;
    int la_begin;
    int fi_end;
    int la_end;
    int Di; //приращение по i
    int Dj; //приращение по j
    int year;
    int month;
    int day;
    int hour;
    int minute;
    QVector<PointData> pointsData;
public:
    Data();
    QVector<Data> readData(QString fileName);
private:
    void readPointData(QList<float> _pointData);
};

#endif // DATA_H
