#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "Coordinates/flatcoordinates.h"
#include"Coordinates/geocoordinates.h"

/**
 * @brief Класс хранящий температуру и координаты
 */
class Temperature
{
    float temperature;
    FlatCoordinates faltCoord;
    GeoCoordinates geoCoord;
public:
    Temperature();
};

#endif // TEMPERATURE_H
