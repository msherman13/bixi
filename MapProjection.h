#pragma once

#include "PixelArray.h"

namespace MapProjection
{
    constexpr float epsilon = 0.0001;

    struct GeographicCoord
    {
        float latitude  = 0.0;
        float longitude = 0.0;
    };

    struct Coord3d
    {
        Coord3d(float xin, float yin, float zin) :
            x(xin),
            y(yin),
            z(zin)
        {}

        // -1.0 to 1.0
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
    };

    float RadiansToDegrees(float radians);
    float DegreesToRadians(float degrees);

    CPixelArray::Coordinate PolarToCartesian(double theta, double radius);
    GeographicCoord Coord3dToGeographic(Coord3d coord);

    // mercator projection
    // see: http://mathworld.wolfram.com/MercatorProjection.html
    CPixelArray::Coordinate MercatorProjection(GeographicCoord geog);

    CPixelArray::Coordinate MercatorProjection3d(Coord3d coord_3d);

    // lambert conformal conic projection
    // see: http://mathworld.wolfram.com/LambertConformalConicProjection.html
    CPixelArray::Coordinate LambertProjection(GeographicCoord geog);

    CPixelArray::Coordinate LambertProjection3d(Coord3d coord_3d);

    CPixelArray::Coordinate AlbersProjection(GeographicCoord geog);
};
