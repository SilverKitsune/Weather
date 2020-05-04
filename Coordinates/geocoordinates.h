#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

#include "Coordinates/flatcoordinates.h"

/**
 * @brief Класс, описывающий географические координаты
 */
class GeoCoordinates
{
    /** @brief fi - широта */
    double fi;

    /** @brief la - долгота */
    double la;

public:

    GeoCoordinates() : fi(0.0), la(0.0) {}

    GeoCoordinates(double _fi, double _la) : fi(_fi), la(_la) {}

    /**
     * @brief ToFlat - перевод географических координат в плоские
     * @return плоские координаты
     */
    FlatCoordinates *ToFlat();

};

#endif // GEOCOORDINATES_H
