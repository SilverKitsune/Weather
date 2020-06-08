#ifndef FLATCOORDINATES_H
#define FLATCOORDINATES_H

/**
 * @brief Класс описывающий плоские координаты
 */
class FlatCoordinates
{
protected:
    float x;
    float y;

public:

    FlatCoordinates() : x(0.0), y(0.0) {}

    FlatCoordinates(float _x, float _y) : x(_x), y(_y) {}

    float X() {return x;}
    float Y() {return y;}
};

#endif // FLATCOORDINATES_H
