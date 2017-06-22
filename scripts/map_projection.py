#!/usr/bin/python

#from math import *
import math

epsilon = 0.0001

def radians_to_deg(radians):
    return radians * 180.0 / math.pi

def deg_to_radians(deg):
    return deg * math.pi / 180.0

def cartesian_to_geodetic(x, y, z):
    lat = math.atan2(z, math.sqrt(x * x + y * y))
    lon = math.atan2(y, x) - math.pi / 2.0

    if lon < 0.0:
        lon = math.pi + math.pi - math.fabs(lon)
    elif lon > 2.0 * math.pi:
        lon -= 2.0 * math.pi

    return [lat, lon]

def lambert_proj(lat, lon):
    std_par_1 = math.pi / 6.0
    std_par_2 = math.pi / 3.0
    ref_lat   = math.pi / 2.0
    ref_lon   = math.pi

    n = math.log( math.cos(std_par_1) * (1.0 / math.cos(std_par_2)) ) / \
        math.log( math.tan(math.pi / 4.0 + std_par_2 / 2.0) * ( 1.0 / math.tan(math.pi / 4.0 + std_par_1 / 2.0) ) )

    f = ( math.cos(std_par_1) * math.pow(math.tan(math.pi / 4.0 + std_par_1 / 2.0), n)) / n

    rho_tan = 0.0 if \
            (math.fabs(lat - math.pi / 2.0) < epsilon or math.fabs(-lat - math.pi / 2.0) < epsilon) else \
            (1.0 / math.tan(math.pi / 4.0 + lat / 2.0))
    rho = f * math.pow(rho_tan, n)

    rho_0_tan = 0.0 if (math.fabs(ref_lat - math.pi / 2.0) < epsilon) else (1.0 / math.tan(math.pi / 4.0 + ref_lat / 2.0))
    rho_0 = f * math.pow(rho_0_tan, n)

    x = rho * math.sin(n * (lon - ref_lon))
    y = rho_0 - rho * math.cos(n * (lon - ref_lon))

    x /= 2.0
    y /= -2.0

    return [x, y]

def lambert_proj_cartesian(x, y, z):
    [lat, lon] = cartesian_to_geodetic(x, y, z)

    return lambert_proj(lat, lon)
