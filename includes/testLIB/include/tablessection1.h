#ifndef TABLESSECTION1_H
/*!
 * \file
 * \brief Файл, описывающий кодовые таблицы раздела 1
 *
 * Данный файл содержит в себе следующие кодовые таблицы:
 * Идентификатор центра
 * Единица времени
 * Указатель параметра
 * Фиксированные уровни или слои, дл которых включаются данные
 */
enum class OrigCenters ///<Идентификатор центра
{
    USWS_NationalMetCenter=7,
    USWS_NWSTelecommsGateway=8,
    USWS_FieldStations=9,
    JapaneseMA_Tokyo=34,
    NHC_Miami=52,
    CanadianMS_Montreal=54,
    USAF_GWC=57,
    USNavy_FNOC=58,
    NOAAFSL_BoulderCO=59,
    UKMO_Bracknell=74,
    FWS_Toulouse=85,
    ESA=97,
    ECforMediumRangeForecaste=98,
    DeBilt=99
};

enum class TimeUnit ///< Единица времени
{
    minute=0,///< Минута
    hour=1,///< Час
    day=2,///< День
    month=3,///< Месяц
    year=4,///< Год
    decade=5,///< Декада (10 лет)
    normal=6,///< Нормаль (30 лет)
    century=7,///< Век
    second=254///< Секунда
};

enum class dataTypes///< Указатель параметра
{
GRB_PRESSURE= 1,  ///< Давление, Pa
GRB_PRESSURE_MSL=2,  ///< Давление, приведенное к среднему уровню моря, Pa
GRB_GEOPOT_HGT=7, ///<  Высота геопотенциала, gpm
GRB_TEMP=11, ///<  Температура, K
GRB_TEMP_POT=13, ///< Потенциальная температура, K
GRB_TMAX=15, ///< Максимальная температура
GRB_TMIN=16, ///< Минимальная температура
GRB_DEWPOINT=17,///< Температура точки росы
GRB_WIND_DIR=31, ///<  Напрвление ветра
GRB_WIND_SPEED=32,  ///< Скорость ветра
GRB_WIND_VX=33,  ///< Компонента ветра u
GRB_WIND_VY=34,  ///< Комонента ветра v
GRB_CUR_VX=49,   ///< Компонента течения  u
GRB_CUR_VY=50,   ///< Компонента течения v
GRB_HUMID_SPEC=51, ///< Удельная влажность
GRB_HUMID_REL=52,   ///< Относительная влажность, %
GRB_PRECIP_RATE=59,  ///<Интенсивность выпадения осадков
GRB_PRECIP_TOT=61,   ///< Суммарное количество осадков
GRB_SNOW_DEPTH=66,   ///< Высота снежного покрова
GRB_CLOUD_TOT=71,   ///< Общая облачность, %
GRB_CLOUD_LOW=72,   ///< Конвективная облачность, %
GRB_CLOUD_MID=73,   ///< Нижняя облачность, %
GRB_CLOUD_HIG=74,   ///< Средняя облачность

// Waves
GRB_WAV_SIG_HT=100,   ///< Значимая высота комбинированных ветровых волн и зыби
GRB_WAV_WND_DIR=101,  ///< Направление ветровых волны
GRB_WAV_WND_HT=102,   ///< Значимая высота ветровых волн
GRB_WAV_WND_PER=103,   ///< Средний период ветровых волн
GRB_WAV_SWL_DIR=104,   ///< Направление зыби
GRB_WAV_SWL_HT=105,   ///<Значимая высота зыби
GRB_WAV_SWL_PER=106,   ///< Средний период зыби
GRB_WAV_PRIM_DIR=107,   ///< Основное направление волн
GRB_WAV_PRIM_PER=108,   ///< Основной средний период волн
GRB_WAV_SCDY_DIR=109,   ///< Вторичное направление волн
GRB_WAV_SCDY_PER=110,   ///< Вторичный средний период волн

};

enum class levelType///< Тип уровня или слоя
{
    LV_GND_SURF=1, ///< Земная или водная поверхность
    LV_ISOTHERM0=4, ///< Уровень изотермы
    LV_ISOBARIC=100, ///< Изобарическая поверхность
    LV_MSL=102, ///< Средний уровень моря
    LV_ABOV_MSL=103, ///< Установленная высота над средним уровнем моря
    LV_ABOV_GND=105,  ///< Установленный уровень высоты над поверхностью
    LV_SIGMA=107, ///< Уровень сигма

    LV_ATMOS_ALL=200, ///< Вся атмосфера

};
#endif // TABLESSECTION1_H
