#!/usr/bin/python

import sys
import numpy as np
import pandas as pd
import math

# in degrees
def geographic_to_3d_x(latitude, longitude):
    lat_rad = latitude * math.pi / 180.0
    lon_rad = longitude * math.pi / 180.0

    x = math.cos(lat_rad) * math.cos(lon_rad)
    y = math.cos(lat_rad) * math.sin(lon_rad)
    z = math.sin(lat_rad)

    return [x, y, z]


df = pd.read_csv(sys.argv[1]).dropna(how='all')

out = df.copy()
del(out['lat1'])
del(out['lon1'])
del(out['lat2'])
del(out['lon2'])

out['x1'] = np.nan
out['y1'] = np.nan
out['z1'] = np.nan
out['x2'] = np.nan
out['y2'] = np.nan
out['z2'] = np.nan

for index, row in df.iterrows():
    [x, y, z] = geographic_to_3d_x(row['lat1'], row['lon1'])
    out.set_value(index, 'x1', x)
    out.set_value(index, 'y1', y)
    out.set_value(index, 'z1', z)
    [x, y, z] = geographic_to_3d_x(row['lat2'], row['lon2'])
    out.set_value(index, 'x2', x)
    out.set_value(index, 'y2', y)
    out.set_value(index, 'z2', z)

print(out.to_string())
out.to_csv(sys.argv[2], index=False)
