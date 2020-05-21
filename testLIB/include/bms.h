#ifndef BMS_H
#define BMS_H
/*!
 * \file
 * \brief Файл, описывающий раздел 3.
 *
 * Данный файл содержит в себе определения раздела битового отображения,
 * содержащегося в формате GRIB 1
 */
#include <reader.h>
#include <QList>
/*!
 * \brief Раздел 3. Раздел битового отображения.
 * \details  Данный отдел не является обязательный.
 * Содержание:
 * Длина раздела, бит на точку сетки, в соответствующей последовательности
 * обозначает пропуск (бит 0) или включение (бит 1) данных в соответусвующих точках
 */
class BMS:public Reader
{
protected:
    /*!
     * \brief Структура данных, описывающая содержание раздела битового отображения
     */
    struct Data{
        QList<bool> bitMap;///> Битовое отображения
        long sectionLength;///> Длина раздела
        int unusedBit;///> Количество неиспользуемых битов в конце раздела
        bool specificBitmap;///> Является ли битовое отображение предопределенным
    };
public:
    friend struct uniData;
    BMS(){};
    ~BMS(){};
    /*!
     * Чтение секции
     * \param[in] file Указатель на файл кодировки grb
     * \param[in] d Указатель на структуру Data
     * \param[in] pointQuantity Количество точек
     */
    void readSec(ifstream *file, Data* d, int);
    /*!
     * Получение битовой карты
     */
    QList<bool> getBitMap();
};

#endif // BMS_H
