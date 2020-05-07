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
};

/**
 * @brief The Converter class преобразования координат
 */
class Converter
{
public:
    Converter();

    /**
     * @brief fromGeoToFlat - преобразование географических координат в плоские
     * @param geo - географические координаты
     * @return плоские координаты
     * @todo
     */
    FlatCoordinates *fromGeoToFlat(GeoCoordinates *geo);

    /**
     * @brief fromFlatToOpengl - преобразование плоских координат в координаты экрана
     * @param flat - плоские координаты
     * @return координаты экрана
     * @todo
     */
    OpenglCoordinates *fromFlatToOpengl(FlatCoordinates *flat);

    /**
     * @brief fromGeoToOpengl - преобразование географических координат в координаты экрана
     * @param geo - географические координаты
     * @return координаты экрана
     * @todo
     */
    OpenglCoordinates *fromGeoToOpengl(GeoCoordinates *geo);
};

#endif // CONVERTER_H
