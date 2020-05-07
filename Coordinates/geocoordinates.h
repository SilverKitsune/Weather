#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

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

    double Fi() {return fi;}
    double La() {return la;}
};

#endif // GEOCOORDINATES_H
