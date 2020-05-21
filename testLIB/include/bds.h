#ifndef BDS_H
#define BDS_H

/*!
 * \file
 * \brief Файл, описывающий раздел 4.
 *
 * Данный файл содержит в себе определения раздела двоичных данных,
 * содержащегося в формате GRIB 1
 */
#include <reader.h>
#include <vector>
#include <QList>
/*!
 * \brief Раздел 4. Раздел двоичных данных.
 * \details  Данный отдел не является обязательный.
 * Содержание:
 * Длина раздела и величины данных
 */
class BDS:public Reader
{
protected:
    /*!
     * \brief Структура данных, описывающая содержание раздела двоичных данных
     */
    struct Data {
        long sectionLength;///> Длина раздела
        int flag;///> Флаг, количество неиспользуемых бит в конце раздела
        bool simplePack;///> Простая упаковка
        bool fPoint; ///>Представленные величины с плавающей запятой (в первоначальных данных)
        bool mapPoint;///>Данные по точкам сетки
        bool addflag;///>Нет дополнительных флагов
        int E; ///>Масштабный коэффициент
        float refValue;///> Величина начала отсчета(минимум пакетных величинх
        size_t bit;///> Количество битов, содержащих каждую пакетную величину
        QList<float> pointData;///> Данные
    };
public:
    friend struct uniData;
    BDS(){};
    ~BDS(){};
    /*!
     * \brief Чтение раздела
     * \param[in] file Указатель на файл кодировки grb
     * \param[in] D Десятичный масштабный коэффициент из секции 1
     * \param[in] type Тип данных из секции 1
     * \param[in] scanFlags Флаги сканирования из секции 2
     */
    void readSec(ifstream *file, Data* d, int D, string type, int scanFlag,int Ni,int Nj);

    /*!
     * \brief Вычисляет референсное значение
     * \param[in] октеты 7-10
     */
    void ref(float *,char a, char b, char c, char d);

    //https://www.geeksforgeeks.org/bitwise-and-of-n-binary-strings/
    /*!
     * \brief Расшифровывает простую упаковку
     * \param[in] file Указатель на файл кодировки grb
     * \param[in] d Указатель на структуру Data
     * \param[in] D Десятичный масштабный коэффициент из секции 1
     * \param[in] type Тип данных из секции 1
     */
    QList<float> simple(ifstream *file,Data* d, int D);
    /*!
     * \brief Разбивает строку на данные размером bit
     * \param[in] bit Количество битов, содержащих каждую пакетную величину
     * \param[in] data Строка данных
     * \param[in] dataF Указатель на вектор данных
     */
    void bitData(size_t bit, string data, vector<int>* dataF );
    void directionMinusI(QList<float>*,int, int);
    void directionPlusJ(QList<float> *data, int Nj,int Ni);
};

#endif // BDS_H
