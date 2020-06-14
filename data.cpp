#include "data.h"
Data::Data()
{
    pD = new QList<PointData> ();
}

Data::~Data()
{
    pD->clear();
    delete pD;
}

QList<Data>* Data::readData(QString fileName)
{
    Parser parser;
    QList<QList<paramData>> messages;
    parser.setFile(fileName);
    messages = parser.parameterData("Temp");

    QList<Data> *list = new QList<Data>();
    for(int i = 0; i < messages.size(); i++)
    {
        Data *data_i = new Data();
        data_i->year = messages.at(i).at(0).year;
        data_i->month = messages.at(i).at(0).month;
        data_i->day = messages.at(i).at(0).day;
        data_i->hour = messages.at(i).at(0).hour;
        data_i->minute = messages.at(i).at(0).minut;
        for(int j = 0; j < messages.at(i).size(); j++)
        {
            data_i->pD->append(PointData(messages.at(i).at(j).La,
                                         messages.at(i).at(j).Lo,
                                         messages.at(i).at(j).parValue));
        }
        list->append(*data_i);
    }
    return list;
}


