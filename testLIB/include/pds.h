#ifndef PDS_H
#define PDS_H

#include <reader.h>
#include <tablessection1.h>
#define isleapyear(y) ((((y)%4==0) && ((y)%100!=0))||((y)%400==0))



class PDS : public Reader
{
protected:
    struct Data{
        long sectionLength;  ///Длина секции
        int parameter_table_version_number;///Номер версии основных таблиц GRIB
        string identification_of_center;///Идентификатор центрального производителя
        int generating_process_ID_number;///Цифровой  ID  процесса генерации
        int grid_identification;///Идентификация сетки (географическое положение и площадь)
        bool GDS; ///Флаг наличия GDS(true-included,else omitted)
        bool BMS;///Флаг наличия BMS(true-included,else omitted)
        string indicator_of_parameter_and_units;///Индикатор параметра и единиц измерения
        int indicator_of_type_of_level_or_layer;///Индикатор типа уровня или слоя
        int info_of_the_level_or_layer;///Высота, давление и т. д. уровня или слоя
        int year;
        int month;
        int day;
        int hour;
        int minut;
        long long refDate;
        long long curDate;
        int forecast_time_unit; ///Единица времени прогноза tablessection1.h TimeUnit
        int P1,P2;
        int time_range_indicator;//parse Table 5
        int periodSec;
        int number_missing_from_averages_or_accumulations;
        int century;
        int identification_of_sub_center;
        int D;///Десятичный масштабный коэффициент D
    };
public:
    friend struct uniData;
    PDS(){}
    ~PDS(){}
    void readSec(ifstream* file, Data* d);
    long long UTC_mktime (int year,int month,int day,int hour,int min,int sec);
    void factorD(int*,char a,char b);
    string centerIndentification(char a);
    string dataType(char a);
    int period(int unit,int P1,int P2, int range);

};

#endif // PDS_H
