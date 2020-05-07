#ifndef TEMPERATURE_H
#define TEMPERATURE_H
//#include "Coordinates/flatcoordinates.h"
#include "Coordinates/geocoordinates.h"

/**
 * @brief Класс хранящий температуру и координаты
 */
class Temperature : public GeoCoordinates
{
    float temperature;
    //GeoCoordinates *geoCoord;

public:
    Temperature();
    Temperature(double _fi, double _la, float temp);
    //Temperature(GeoCoordinates *coord, float temp);

};

#endif // TEMPERATURE_H
