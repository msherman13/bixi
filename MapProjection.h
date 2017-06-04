#include <cmath>
#include "PixelArray.h"

namespace MapProjection
{
    struct GeographicCoord
    {
        float latitude  = 0.0;
        float longitude = 0.0;
    };

    struct Coord3d
    {
        // -1.0 to 1.0
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
    };

    float RadiansToDegrees(float radians)
    {
        return radians * 180 / M_PI;
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * M_PI / 180;
    }

    GeographicCoord Coord3dToGeographic(Coord3d coord)
    {
        GeographicCoord ret;

        ret.latitude  = atan2(coord.z, sqrtf(coord.x * coord.x + coord.y * coord.y));
        ret.longitude = atan2(coord.y, coord.x);

        return ret;
    }

    // mercator projection
    // see: http://mathworld.wolfram.com/MercatorProjection.html
    CPixelArray::Coordinate Coord3dTo2d(Coord3d coord_3d)
    {
        // first convert to latitude and longitude
        GeographicCoord geog = Coord3dToGeographic(coord_3d);

        const float lambda_o = 0.0;

        CPixelArray::Coordinate ret;
        ret.x = geog.longitude - lambda_o;
        ret.y = 0.5 * log((1 + sin(geog.latitude)) / (1 - sin(geog.latitude)));

        return ret;
    }
};
