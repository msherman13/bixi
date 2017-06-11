#include "MapProjection.h"

#include <cmath>

float MapProjection::RadiansToDegrees(float radians)
{
    return radians * 180 / M_PI;
}

float MapProjection::DegreesToRadians(float degrees)
{
    return degrees * M_PI / 180;
}

MapProjection::GeographicCoord MapProjection::Coord3dToGeographic(Coord3d coord)
{
    GeographicCoord ret;

    ret.latitude  = atan2(coord.z, sqrtf(coord.x * coord.x + coord.y * coord.y));
    ret.longitude = atan2(coord.y, coord.x);

    if(ret.longitude < 0)
    {
        ret.longitude = M_PI + M_PI - fabs(ret.longitude);
    }

    return ret;
}

// mercator projection
// see: http://mathworld.wolfram.com/MercatorProjection.html
CPixelArray::Coordinate MapProjection::MercatorProjection(GeographicCoord geog)
{
    const float lambda_o = 0.0;

    CPixelArray::Coordinate ret;
    ret.x = geog.longitude - lambda_o;
    ret.y = 0.5 * log((1 + sin(geog.latitude)) / (1 - sin(geog.latitude)));

    return ret;
}

CPixelArray::Coordinate MapProjection::MercatorProjection3d(Coord3d coord_3d)
{
    GeographicCoord geog = Coord3dToGeographic(coord_3d);

    return MercatorProjection(geog);
}

// lambert conformal conic projection
// see: http://mathworld.wolfram.com/LambertConformalConicProjection.html
CPixelArray::Coordinate MapProjection::LambertProjection(GeographicCoord geog)
{
    CPixelArray::Coordinate ret;

    const float std_par_1 = M_PI / 6; // 30 degrees
    const float std_par_2 = M_PI / 3; // 60 degrees
    const float ref_lat   = M_PI / 2; // 90 degrees (north pole)
    //const float ref_long  = -M_PI / 2.5;
    //const float ref_long  = -1.285 * M_PI;
    const float ref_long  = M_PI;

    float n = log( cos(std_par_1) * (1 / cos(std_par_2) ) ) /
              log( tan(M_PI / 4 + std_par_2 / 2) * ( 1 / tan(M_PI / 4 + std_par_1 / 2) ) );

    float f = ( cos(std_par_1) * pow( tan(M_PI / 4 + std_par_1 / 2), n) ) / n;

    // cot of 0 is 0, but the tangent part returns inf which evaluates to nan
    float rho_tan = std::abs(geog.latitude - M_PI / 2) < epsilon || std::abs(-geog.latitude - M_PI / 2) < epsilon ?
                    0 :
                    1 / tan(M_PI / 4 + geog.latitude / 2);
    float rho = f * pow( rho_tan, n );

    float rho_0_tan = std::abs(ref_lat - M_PI / 2) < epsilon || std::abs(-ref_lat - M_PI / 2) < epsilon ?
                      0 :
                      1 / tan(M_PI / 4 + ref_lat / 2);
    float rho_0 = f * pow( rho_0_tan, n );

    ret.x = rho * sin( n * (geog.longitude - ref_long) );
    ret.y = rho_0 - rho * cos( n * (geog.longitude - ref_long) );

    // normalize to fit within -1.00 to 1.00 boundary
    ret.x /= 2.0;
    ret.y /= -2.0;

    return ret;
}

CPixelArray::Coordinate MapProjection::LambertProjection3d(Coord3d coord_3d)
{
    GeographicCoord geog = Coord3dToGeographic(coord_3d);

    return LambertProjection(geog);
}
