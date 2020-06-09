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
    PointData(): GeoCoordinates(), param(0.0) {}
    PointData(float _fi, float _la, float temp);
    float getParam() {return param;}


};

#endif // TEMPERATURE_H
