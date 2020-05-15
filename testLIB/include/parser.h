#ifndef PARSER_H
#define PARSER_H

#include <QDebug>

#include "parser_global.h"
#include <is.h>
#include <pds.h>
#include <gds.h>
#include <bds.h>
#include <es.h>

struct uniData{
    PDS::Data sec1;
    GDS::Data sec2;
  //  BMS sec3;
    BDS::Data sec4;
};

class PARSER_EXPORT Parser
{
public:
    Parser(){};
    ~Parser(){};
    QList<uniData> parse (QString fileName);
private:
    bool checkEOF();
    ifstream file;
};

#endif // PARSER_H
