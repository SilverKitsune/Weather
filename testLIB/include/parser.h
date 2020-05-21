#ifndef PARSER_H
#define PARSER_H

#include <QDebug>

#include "parser_global.h"
#include <is.h>
#include <pds.h>
#include <gds.h>
#include <bms.h>
#include <bds.h>
#include <es.h>

struct uniData{
    PDS::Data sec1;
    GDS::Data sec2;
    BMS::Data sec3;
    BDS::Data sec4;
};

struct paramData{
    float La;
    float Lo;
    float parValue;
    int year;///< Год
    int month;///< Месяц
    int day;/// День
    int hour;/// Час
    int minut;/// Минута
};


class PARSER_EXPORT Parser
{
public:
    Parser(){};
    ~Parser(){};

    void setFile(QString fileName);
    QList<QList<paramData>> parameterData(string param);

private:
    bool checkEOF();
    QList<uniData> parse ();
    ifstream file;
    QString name;
};

#endif // PARSER_H
