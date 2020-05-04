#ifndef FLATCOORDINATES_H
#define FLATCOORDINATES_H

/**
 * @brief Класс описывающий плоские координаты
 */
class FlatCoordinates
{
    double x;
    double y;

    //Coordinates of centre
    double centreX;
    double centreY;

public:

    FlatCoordinates() : x(0.0), y(0.0), centreX(0.0), centreY(0.0) {}

    FlatCoordinates(double _x, double _y) : x(_x), y(_y) {}

    /**
     * @brief ChangeSystem - перевод в систему координат с центром в точке с координатами (newCentreX,newCentreY)
     * @param newCentreX - новая координата X центра
     * @param newCentreY - новая координата Y центра
     */
    void ChangeSystem(double newCentreX, double newCentreY);
};

#endif // FLATCOORDINATES_H
