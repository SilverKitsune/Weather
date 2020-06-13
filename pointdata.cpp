#include "pointdata.h"
#include <math.h>
PointData::PointData(float _fi, float _la, float temp) : GeoCoordinates (_fi, _la), param(temp)
{
    flat = toFlat(_fi, _la);
}

FlatCoordinates* PointData::toFlat(float _fi, float _la)
{
    float fi = _fi * M_PI / 180;
    float la = _la * M_PI / 180;
    float h = 0;

    float EQUATORIAL = 6378.1;
    float POLAR = 6356.8;
    float E2 = 1.0 - (POLAR/EQUATORIAL)*(POLAR/EQUATORIAL);
    float Nb = EQUATORIAL/sqrt(1.0 - E2*sin(fi)*sin(fi));
    float X = (Nb+h)*cos(fi)*cos(la);
    float Y = (Nb+h)*cos(fi)*sin(la);

    return new FlatCoordinates(X, Y);
}
