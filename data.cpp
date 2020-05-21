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
        /*data_i->Ni = messages.at(i).sec2.Ni;
        data_i->Nj = messages.at(i).sec2.Nj;
        data_i->fi_begin = messages.at(i).sec2.La1;
        data_i->la_begin = messages.at(i).sec2.Lo1;
        data_i->fi_end = messages.at(i).sec2.La2;
        data_i->la_end = messages.at(i).sec2.Lo2;
        data_i->Di = messages.at(i).sec2.Di;
        data_i->Dj = messages.at(i).sec2.Dj_N;*/
        //data_i->typeOfParameter = messages.at(i).sec1.indicator_of_parameter_and_units;
        data_i->pointsData = messages.at(i);
        list->append(*data_i);
    }
    return list;
}


