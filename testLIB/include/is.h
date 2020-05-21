#ifndef IS_H
#define IS_H
/*!
 * \file
 * \brief Файл, описывающий раздел 0.
 *
 * Данный файл содержит в себе определения раздела указателя,
 * содержащегося в формате GRIB 1
 */

#include <reader.h>
/*!
 * \brief Раздел 0. Раздел указателя.
 * \details  Содержание:
 * "GRIB", длина сообщения, номер издания GRIB
 */
class IS : public Reader
{
public:
    IS(){}
    ~IS(){}
    /*!
     * Чтение секции
     * \param[in] file Указатель на файл кодировки grb
     */
    void readSec(ifstream*);
private:
    long totalLength;///< Длина сообщения
    int editNumber;///< Номер издания GRIB
};

#endif // IS_H
