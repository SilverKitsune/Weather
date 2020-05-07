#ifndef OPENGLCOORDINATES_H
#define OPENGLCOORDINATES_H

#include "flatcoordinates.h"

/**
 * @brief The OpenglCoordinates class описывающий экранные координаты
 */
class OpenglCoordinates : public FlatCoordinates
{
public:
    OpenglCoordinates() : FlatCoordinates() {}
    OpenglCoordinates(double _x, double _y) : FlatCoordinates(_x, _y) {}
};

#endif // OPENGLCOORDINATES_H
