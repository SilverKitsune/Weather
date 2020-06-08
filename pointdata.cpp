#include "pointdata.h"
#include "Coordinates/converter.h"
PointData::PointData(float _fi, float _la, float temp) : GeoCoordinates (_fi, _la), param(temp)
{
    flat = Converter::fromGeoToFlat(this); //??
}
