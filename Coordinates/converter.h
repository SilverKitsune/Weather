#ifndef CONVERTER_H
#define CONVERTER_H

#include "Coordinates/geocoordinates.h"
#include "Coordinates/openglcoordinates.h"
#include "math.h"
#include "includes/glm/glm/glm.hpp"
namespace Converter
{
    const float EQUATORIAL = 6378.1;
    const float POLAR = 6356.8;
    const float E2 = 1.0 - (POLAR/EQUATORIAL)*(POLAR/EQUATORIAL);

    /** @brief The ScreenInfo struct содержит информацию об экране */
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
     * @brief fromGeoToFlat - преобразование географических координат в плоские
     * @param geo - географические координаты
     * @return плоские координаты
     */
    FlatCoordinates *fromGeoToFlat(GeoCoordinates *geo)
    {
         double fi = geo->Fi() * M_PI / 180;
         double la = geo->La() * M_PI / 180;
         double h = 0;

         double Nb = EQUATORIAL/sqrt(1.0 - E2*sin(fi)*sin(fi));
         double X = (Nb+h)*cos(fi)*cos(la);
         double Y = (Nb+h)*cos(fi)*sin(la);

         return new FlatCoordinates(X, Y);
    }

    /**
     * @brief fromFlatToOpengl - преобразование плоских координат в координаты экрана
     * @param flat - плоские координаты
     * @param info - текущая информация об экране
     * @return координаты экрана
     * @todo
     */
    OpenglCoordinates *fromFlatToOpengl(FlatCoordinates *flat, ScreenInfo *info)
    {
        OpenglCoordinates *glCoord;
        ///TODO
        return glCoord;
    }

    /**
     * @brief fromGeoToOpengl - преобразование географических координат в координаты экрана
     * @param geo - географические координаты
     * @param info - текущая информация об экране
     * @return координаты экрана
     */
   /* OpenglCoordinates *fromGeoToOpengl(GeoCoordinates *geo, ScreenInfo *info)
    {
        return fromFlatToOpengl(fromGeoToFlat(geo), info);
    }*/

    glm::vec2 fromGeoToOpengl(GeoCoordinates *geo, float Cx, float Cy)
    {
        //FlatCoordinates *flat  = fromGeoToFlat(geo);
        return glm::vec2((geo->Fi()-Cx)/2, (geo->La()-Cy)/2);
    }


};

#endif // CONVERTER_H
