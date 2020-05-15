#include "data.h"
#include "parser.h"
Data::Data()
{

}

QVector<Data> Data::readData(QString fileName)
{
    Parser parser;
    QList<uniData> messages;
    messages = parser.parse(fileName);
    QVector<Data> _data;
    for(int i = 0; i < messages.size(); i++)
    {
        Data data_i;
        data_i.year = messages.at(i).sec1.year;
        data_i.month = messages.at(i).sec1.month;
        data_i.hour = messages.at(i).sec1.hour;
        data_i.minute = messages.at(i).sec1.minut;
        data_i.Ni = messages.at(i).sec2.Ni;
        data_i.Nj = messages.at(i).sec2.Nj;
        data_i.fi_begin = messages.at(i).sec2.La1;
        data_i.la_begin = messages.at(i).sec2.Lo1;
        data_i.fi_end = messages.at(i).sec2.La2;
        data_i.la_end = messages.at(i).sec2.Lo2;
        data_i.Di = messages.at(i).sec2.Di;
        data_i.Dj = messages.at(i).sec2.Dj_N;
        data_i.readPointData(messages.at(i).sec4.pointData);

        _data.append(data_i);
    }
    return _data;
}

void Data::readPointData(QList<float> _pointData)
{
    for(int i = 0; i < Ni; i++)
    {
        for(int j = 0; j < Nj; j++)
        {
            int _fi = fi_begin + i*Di;
            int _la = la_begin + i*Dj;
            PointData *pd = new PointData(_fi, _la, _pointData.at(i*Nj+j));
            pointsData.append(*pd);
        }
    }
}
