#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

/**
 * @brief Класс, описывающий географические координаты
 */
class GeoCoordinates
{
    /** @brief fi - широта */
    int fi;

    /** @brief la - долгота */
    int la;

public:

    GeoCoordinates() : fi(0.0), la(0.0) {}

    GeoCoordinates(int _fi, int _la) : fi(_fi), la(_la) {}

    int Fi() {return fi;}
    int La() {return la;}
};

#endif // GEOCOORDINATES_H
