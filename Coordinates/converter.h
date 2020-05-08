#ifndef CONVERTER_H
#define CONVERTER_H

#include "Coordinates/geocoordinates.h"
#include "Coordinates/openglcoordinates.h"

/**
 * @brief The ScreenInfo struct содержит информацию об экране
 */
struct ScreenInfo
{
    /** @brief scale - масштаб */
    float scale;

    /** @brief width - ширина  */
    int width;

    /** @brief height - высота */
    int height;

    /** @brief LeftUpCorner - географические координаты верхнего левого угла*/
    GeoCoordinates *LeftUpCorner;
};

/**
 * @brief The Converter class преобразования координат
 */
class Converter
{
    const double EQUATORIAL = 6378.1;
    const double POLAR = 6356.8;
    double E2 = 1.0 - (POLAR/EQUATORIAL)*(POLAR/EQUATORIAL);
public:
    Converter();

    /**
     * @brief fromGeoToFlat - преобразование географических координат в плоские
     * @param geo - географические координаты
     * @return плоские координаты
     */
    FlatCoordinates *fromGeoToFlat(GeoCoordinates *geo);

    /**
     * @brief fromFlatToOpengl - преобразование плоских координат в координаты экрана
     * @param flat - плоские координаты
     * @param info - текущая информация об экране
     * @return координаты экрана
     * @todo
     */
    OpenglCoordinates *fromFlatToOpengl(FlatCoordinates *flat, ScreenInfo *info);

    /**
     * @brief fromGeoToOpengl - преобразование географических координат в координаты экрана
     * @param geo - географические координаты
     * @param info - текущая информация об экране
     * @return координаты экрана
     */
    OpenglCoordinates *fromGeoToOpengl(GeoCoordinates *geo, ScreenInfo *info);
};

#endif // CONVERTER_H
