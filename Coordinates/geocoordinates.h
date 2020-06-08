#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

/**
 * @brief Класс, описывающий географические координаты
 */
class GeoCoordinates
{
    /** @brief fi - широта */
    float fi;

    /** @brief la - долгота */
    float la;

public:

    GeoCoordinates() : fi(0.0), la(0.0) {}

    GeoCoordinates(float _fi, float _la) : fi(_fi), la(_la) {}

    float Fi() {return fi;}
    float La() {return la;}
};

#endif // GEOCOORDINATES_H
