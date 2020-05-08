#include "converter.h"
#include "math.h"
Converter::Converter()
{

}

FlatCoordinates *Converter::fromGeoToFlat(GeoCoordinates *geo)
{
     double fi = geo->Fi() * M_PI / 180;
     double la = geo->La() * M_PI / 180;
     double h = 0;

     double Nb = EQUATORIAL/sqrt(1.0 - E2*sin(fi)*sin(fi));
     double X = (Nb+h)*cos(fi)*cos(la);
     double Y = (Nb+h)*cos(fi)*sin(la);

     return new FlatCoordinates(X, Y);

}

OpenglCoordinates *Converter::fromFlatToOpengl(FlatCoordinates *flat, ScreenInfo *info)
{
    OpenglCoordinates *glCoord;
    ///TODO
    return glCoord;
}

OpenglCoordinates *Converter::fromGeoToOpengl(GeoCoordinates *geo, ScreenInfo *info)
{
    return fromFlatToOpengl(fromGeoToFlat(geo), info);
}
