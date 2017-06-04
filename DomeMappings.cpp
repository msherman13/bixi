#include "DomeMappings.h"

size_t DomeMappings::GetLocation(size_t index)
{
    return index;
}

CPixelArray::Coordinate DomeMappings::GetCoordinate(size_t index)
{
    int latitude  = 10 * (index / 37);
    int longitude = 10 * (index % 37);

    MapProjection::GeographicCoord geog;
    geog.latitude  = MapProjection::DegreesToRadians(latitude);
    geog.longitude = MapProjection::DegreesToRadians(longitude);

    return MapProjection::LambertProjection(geog);
}
