#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "Coordinates/flatcoordinates.h"
#include "Coordinates/geocoordinates.h"

/**
 * @brief Класс хранящий температуру и координаты
 */
class PointData : public GeoCoordinates
{
    float param;
    FlatCoordinates *flat;
public:
    PointData(float _fi, float _la, float temp);


};

#endif // TEMPERATURE_H
