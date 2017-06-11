#!/usr/bin/python

import sys
import pandas as pd

df = pd.read_csv(sys.argv[1])

# map to individual pixels
pixels = pd.DataFrame(columns=['raw_index', 'logical_index', 'x', 'y', 'z'])
logical_index = 0
for name, group in df.groupby('shape_index'):
    for index, row in group.reset_index().iterrows():
        raw = 0
        length = abs(row['end_index'] - row['start_index']) + 1
        slope_x = (row['x2'] - row['x1']) / length
        slope_y = (row['y2'] - row['y1']) / length
        slope_z = (row['z2'] - row['z1']) / length
        for j in range(int(row['start_index']), int(row['end_index'] + 1)):
            pixel = pd.Series()
            pixel['raw_index'] = j
            pixel['logical_index'] = logical_index
            pixel['x']     = row['x1'] + slope_x * raw
            pixel['y']     = row['y1'] + slope_y * raw
            pixel['z']     = row['z1'] + slope_z * raw
            pixels = pixels.append(pixel, ignore_index=True)
            logical_index += 1
            raw += 1

pixels = pixels.set_index('logical_index')

# scale so 0.99 is max coordinate
#max_x = max(df['x1'].max(), df['x2'].max())
#max_y = max(df['y1'].max(), df['y2'].max())
#max_z = max(df['z1'].max(), df['z2'].max())
#x_scale = 0.99 / max_x
#y_scale = 0.99 / max_y
#z_scale = 0.99 / max_z
#pixels['x'] = pixels['x'] * x_scale
#pixels['y'] = pixels['y'] * y_scale
#pixels['z'] = pixels['z'] * z_scale

ofile = open(sys.argv[2], 'w')

ofile.write("// Auto-Generated file, do not edit manually\n\n")

ofile.write("#include \"DomeMappings.h\"\n\n")

ofile.write("size_t DomeMappings::GetLocation(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
for index, row in pixels.iterrows():
    ofile.write("        case %d: return %d;\n" % (index, row['raw_index']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("CPixelArray::Coordinate DomeMappings::GetCoordinate(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
for index, row in pixels.iterrows():
    ofile.write("        case %d: return MapProjection::LambertProjection3d(MapProjection::Coord3d(%f, %f, %f));\n" % (index, row['x'], row['y'], row['z']))
ofile.write("        default: return CPixelArray::Coordinate();\n")
ofile.write("    }\n")
ofile.write("}\n\n")

df = df.set_index('leg_index')

ofile.write("DomeMappings::Mappings::Mappings() :\n")
ofile.write("    CPixelArrayLegs::Config()\n")
ofile.write("{\n")
ofile.write("    m_num_legs = %d;\n" % (len(df)))
ofile.write("    m_physical_size = c_num_physical_pixels;\n\n")
for index, row in df.iterrows():
    ofile.write("    m_start_index[%d] = %d;\n" % (index, row['start_index']))
    ofile.write("    m_end_index[%d] = %d;\n" % (index, row['end_index']))
ofile.write("}")
