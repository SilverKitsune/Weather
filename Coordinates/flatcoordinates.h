#ifndef FLATCOORDINATES_H
#define FLATCOORDINATES_H

/**
 * @brief Класс описывающий плоские координаты
 */
class FlatCoordinates
{
protected:
    double x;
    double y;

public:

    FlatCoordinates() : x(0.0), y(0.0) {}

    FlatCoordinates(double _x, double _y) : x(_x), y(_y) {}

    double X() {return x;}
    double Y() {return y;}
};

#endif // FLATCOORDINATES_H
