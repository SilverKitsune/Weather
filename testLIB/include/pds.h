#ifndef PDS_H
#define PDS_H
/*!
 * \file
 * \brief Файл, описывающий раздел 1.
 *
 * Данный файл содержит в себе определение продукции,
 * содержащегося в формате GRIB 1
 */

#include <reader.h>
#include <tablessection1.h>
#define isleapyear(y) ((((y)%4==0) && ((y)%100!=0))||((y)%400==0))

/*!
 * \brief Раздел 1. Раздел определения продукции.
 * \details  Содержание:
 * Длина раздела, идентификация закодированного анализа или прогноза
 */


class PDS : public Reader
{
protected:
    /*!
     * \brief Структура данных, описывающая содержание раздела определения продукции
     */
    struct Data{
        long sectionLength;  ///< Длина секции
        int parameter_table_version_number;///< Номер версии основных таблиц GRIB
        string identification_of_center;///< Идентификатор центрального производителя
        int generating_process_ID_number;///< Цифровой  ID  процесса генерации
        int grid_identification;///< Идентификация сетки (географическое положение и площадь)
        bool GDS; ///< Флаг наличия GDS(true-included,else omitted)
        bool BMS;///< Флаг наличия BMS(true-included,else omitted)
        string indicator_of_parameter_and_units;///< Индикатор параметра и единиц измерения
        int indicator_of_type_of_level_or_layer;///< Индикатор типа уровня или слоя
        int info_of_the_level_or_layer;///< Высота, давление и т. д. уровня или слоя
        int year;///< Год
        int month;///< Месяц
        int day;/// День
        int hour;/// Час
        int minut;/// Минута
        long long refDate;
        long long curDate;
        int forecast_time_unit; ///< Единица времени прогноза tablessection1.h TimeUnit
        int P1,P2; ///< Периоды времени
        int time_range_indicator;///< Указатель времени
        int periodSec;///< Период в секундах
        int number_missing_from_averages_or_accumulations;///< Число утраченных случаев в расчете в случае статистической обработки
        int century;/// < Век
        int identification_of_sub_center;///< Указатель подцентра
        int D;///< Десятичный масштабный коэффициент D
    };
public:
    friend struct uniData;
    PDS(){}
    ~PDS(){}
    /*!
     * Чтение секции
     * \param[in] file Указатель на файл кодировки grb
     * \param[in] d Указатель на структуру Data
     */
    void readSec(ifstream* file, Data* d);
    /*!
     * Перевод времени в формат UTC
     * \param[in] year Год
     * \param[in] month Месяц
     * \param[in] day День
     * \param[in] hour Час
     * \param[in] min Минуты
     * \param[in] sec Секунды
     *
     * \return время в формате UTC
     */
    long long UTC_mktime (int year,int month,int day,int hour,int min,int sec);
    /*!
     * Вычисление десятичного масштабного коэффициента
     * \param[in] D Указатель на десятичный масштабный коэффициент
     * \param[in] a содержание октета 27
     * \param[in] a содержание октета 28
     */
    void factorD(int*,char a,char b);
    /*!
     * Идентификация центра-поставщика/производителя продукции
     * \param[in] file содержание октета 5
     * \return идентификатор центра
     */
    string centerIndentification(char a);
    /*!
     * Идентификация параметра
     * \param[in] file содержание октета 9
     * \return тип данных
     */
    string dataType(char a);
    /*!
     * Вычисление периода времени между последовательными анализами
     * \param[in] unit указатель времени
     * \param[in] P1 период времени
     * \param[in] P2 период времени
     * \param[in] range указатель единицы времени
     * \return период времени
     */
    int period(int unit,int P1,int P2, int range);

};

#endif // PDS_H
