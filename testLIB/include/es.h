#ifndef ES_H
#define ES_H
/*!
 * \file
 * \brief Файл, описывающий раздел 5.
 *
 * Данный файл содержит в себе определения конечного раздела,
 * содержащегося в формате GRIB 1
 */
#include<reader.h>
/*!
 * \brief Раздел 5. Конечный раздел.
 * \details  Содержание:
 * 7777
 */
class ES :public Reader
{
public:
    ES(){};
    virtual ~ES(){};
    /*!
     * Чтение секции
     * \param[in] file Указатель на файл кодировки grb
     */
    virtual void readSec(ifstream *file);
};


#endif // ES_H
