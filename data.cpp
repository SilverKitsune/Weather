#include "data.h"
Data::Data()
{

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
        data_i->pointsData = messages.at(i);
        list->append(*data_i);
    }
    return list;
}


