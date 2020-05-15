#ifndef TABLESSECTION1_H
///Центры
enum class OrigCenters{
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
    //IG=99-101,

};
///Единица времени прогноза
enum class TimeUnit{
    minute=0,
    hour=1,
    day=2,
    month=3,
    year=4,
    decade=5,
    normal=6,//30 years
    century=7,
    //8-253 reserved
    second=254
};

/// Типы данных
enum class dataTypes{
GRB_PRESSURE= 1,  /* Давление, Pa     */
GRB_PRESSURE_MSL=2,   /*Давление, приведенное к среднему уровню моря Pa     */
GRB_GEOPOT_HGT=7,   /*Высота геопотенциала, gpm    */
GRB_TEMP=11,   /*Температура, K      */
GRB_TEMP_POT=13,   /*Потенциальная температура, K      */
GRB_TMAX=15,   /*Максимальная температура, K      */
GRB_TMIN=16,   /*Минимальная температура, K      */
GRB_DEWPOINT=17,   /*Температура точки росы, K      */
GRB_WIND_DIR=31,   /*Напрвление ветра, °      */
GRB_WIND_SPEED=32,   /*Скорость ветра, m/s    */
GRB_WIND_VX=33,   /* m/s    */
GRB_WIND_VY=34,   /* m/s    */
GRB_CUR_VX=49,   /* m/s    */
GRB_CUR_VY=50,   /* m/s    */
GRB_HUMID_SPEC=51,   /* kg/kg  */
GRB_HUMID_REL=52,   /* %      */
GRB_PRECIP_RATE=59,   /* l/m2/s */
GRB_PRECIP_TOT=61,   /* l/m2   */
GRB_SNOW_DEPTH=66,   /* m      */
GRB_CLOUD_TOT=71,   /* %      */
GRB_CLOUD_LOW=72,   /* %      */
GRB_CLOUD_MID=73,   /* %      */
GRB_CLOUD_HIG=74,   /* %      */
GRB_FRZRAIN_CATEG=141,   /* 1=yes 0=no */
GRB_SNOW_CATEG=143,   /* 1=yes 0=no */
GRB_CIN=156,   /* J/kg   */
GRB_CAPE=157,   /* J/kg   */
GRB_WIND_GUST=180,   /* m/s */
GRB_WIND_GUST_VX=181,   /* m/s */
GRB_WIND_GUST_VY=182,   /* m/s */

// Waves
GRB_WAV_SIG_HT=100,   /* m */
GRB_WAV_WND_DIR=101,  /* deg */
GRB_WAV_WND_HT=102,   /* m */
GRB_WAV_WND_PER=103,   /* s */
GRB_WAV_SWL_DIR=104,   /* deg */
GRB_WAV_SWL_HT=105,   /* m */
GRB_WAV_SWL_PER=106,   /* s */
GRB_WAV_PRIM_DIR=107,   /* deg */
GRB_WAV_PRIM_PER=108,   /* s */
GRB_WAV_SCDY_DIR=109,   /* deg */
GRB_WAV_SCDY_PER=110,   /* s */
GRB_WAV_WHITCAP_PROB=155,   /* % */
GRB_WAV_MAX_DIR=207,   /* deg */
GRB_WAV_MAX_PER=208,   /* s */
GRB_WAV_MAX_HT=220,   /* m */

GRB_PRV_WAV_SIG=242,   /* private: all parameter */
GRB_PRV_WAV_MAX=243,   /* private: all parameter */
GRB_PRV_WAV_SWL=244,   /* private: all parameter */
GRB_PRV_WAV_WND=245,   /* private: all parameter */
GRB_PRV_WAV_PRIM=246,   /* private: all parameter */
GRB_PRV_WAV_SCDY=247,   /* private: all parameter */

//----------------------------------------------------
GRB_PRV_WIND_JET=248,   /* private: wind jet stream */
GRB_PRV_WIND_DIR=249,   /* private: wind direction in degrees */
GRB_PRV_WIND_XY2D=250,   /* private: GRB_WIND_VX+GRB_WIND_VX */
GRB_PRV_DIFF_TEMPDEW=251,   /* private: GRB_TEMP-GRB_DEWPOINT */
GRB_PRV_THETA_E=252,   /* K   */
GRB_PRV_CUR_DIR=253,   /* private: current direction in degrees */
GRB_PRV_CUR_XY2D=254,   /* private: GRB_CUR_VX+GRB_CUR_VX */

GRB_TYPE_NOT_DEFINED=0 /* private */


};
///Тип уровня или слоя
enum class levelType{
    LV_GND_SURF=1,
    LV_ISOTHERM0=4,
    LV_ISOBARIC=100,    // hPa
    LV_MSL=102,
    LV_ABOV_MSL=103,    // m
    LV_ABOV_GND=105,    // m
    LV_SIGMA=107,
    LV_ATMOS_ENT=10,
    LV_ATMOS_ALL=200,

    LV_CLOUD_LOW_BOTTOM=212,
    LV_CLOUD_MID_BOTTOM=222,
    LV_CLOUD_HIG_BOTTOM=232,
    LV_CLOUD_LOW_TOP=213,
    LV_CLOUD_MID_TOP=223,
    LV_CLOUD_HIG_TOP=233,
    LV_CLOUD_LOW_LAYER=214,
    LV_CLOUD_MID_LAYER=224,
    LV_CLOUD_HIG_LAYER=234
};
#endif // TABLESSECTION1_H
