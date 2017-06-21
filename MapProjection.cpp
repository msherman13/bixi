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

    // hack: 0 longitude is at (x == 0 && y > 0)
    ret.longitude = atan2(coord.y, coord.x) - M_PI/2;

    if(ret.longitude < 0)
    {
        ret.longitude = M_PI + M_PI - fabs(ret.longitude);
    }
    else if(ret.longitude > 2 * M_PI)
    {
        ret.longitude -= 2 * M_PI;
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
    const float ref_long  = M_PI;

    float n = log( cos(std_par_1) * (1 / cos(std_par_2) ) ) /
              log( tan(M_PI / 4 + std_par_2 / 2) * ( 1 / tan(M_PI / 4 + std_par_1 / 2) ) );

    float f = ( cos(std_par_1) * pow( tan(M_PI / 4 + std_par_1 / 2), n) ) / n;

    // cot of 0 is 0, but the tangent part returns inf which evaluates to nan
    float rho_tan = std::abs(geog.latitude - M_PI / 2) < epsilon || std::abs(-geog.latitude - M_PI / 2) < epsilon ?
                    0 :
                    1 / tan(M_PI / 4 + geog.latitude / 2);
    float rho = f * pow( rho_tan, n );

    float rho_0_tan = fabs(ref_lat - M_PI / 2) < epsilon || fabs(-ref_lat - M_PI / 2) < epsilon ?
                      0 :
                      1 / tan(M_PI / 4 + ref_lat / 2);
    float rho_0 = f * pow( rho_0_tan, n );

    ret.x = rho * sin( n * (geog.longitude - ref_long) );
    ret.y = rho_0 - rho * cos( n * (geog.longitude - ref_long) );

    static int index = 0;

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

// albers projection
// see: https://en.wikipedia.org/wiki/Albers_projection
CPixelArray::Coordinate MapProjection::AlbersProjection(GeographicCoord geog)
{
    CPixelArray::Coordinate ret;

    const float std_par_1 = M_PI / 6; // 30 degrees
    const float std_par_2 = M_PI / 3; // 60 degrees
    const float ref_lat   = M_PI / 2; // 90 degrees (north pole)
    const float ref_long  = 0;

    float n = 0.5 * (sin(std_par_1) + sin(std_par_2));
    float theta = n * (geog.longitude - ref_long);
    float c = pow( cos(std_par_1), 2) + 2 * n * sin(std_par_1);
    float rho = (1 / n) * (sqrt(c - 2 * n * sin(geog.latitude)));
    float rho_o = (1 / n) * (sqrt(c - 2 * n * sin(ref_lat)));

    ret.x = rho * sin(theta);
    ret.y = rho_o - rho * cos(theta);

    ret.x /= 5.0;
    ret.y /= 5.0;

    return ret;
}
