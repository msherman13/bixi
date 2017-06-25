#!/usr/bin/python

import sys
import pandas as pd
import map_projection

df = pd.read_csv(sys.argv[1])

pixels_per_strand = df.groupby('strand_index').sum()['length'].max()

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
            [x, y] = map_projection.lambert_proj_cartesian(row['x1'] + slope_x * raw,\
                                                            row['y1'] + slope_y * raw,\
                                                            row['z1'] + slope_z * raw)
            pixel['x']     = x
            pixel['y']     = y
            pixels = pixels.append(pixel, ignore_index=True)
            logical_index += 1
            raw += 1

pixels = pixels.set_index('logical_index')

# scale so 0.99 is max coordinate
#max_x = max(abs(df['x1']).max(), abs(df['x2']).max())
#max_y = max(abs(df['y1']).max(), abs(df['y2']).max())
#x_scale = 0.99 / max_x
#y_scale = 0.99 / max_y
#pixels['x'] = pixels['x'] * x_scale
#pixels['y'] = pixels['y'] * y_scale

ofile = open(sys.argv[2], 'w')

ofile.write("#ifdef GEOM_DOME\n\n")

ofile.write("// Auto-Generated file, do not edit manually\n\n")

ofile.write("#include \"DomeMappings.h\"\n\n")

ofile.write("size_t DomeMappings::Mappings::GetLocation(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
for index, row in pixels.iterrows():
    ofile.write("        case %d: return %d;\n" % (index, row['raw_index']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("CPixelArray::Coordinate DomeMappings::Mappings::GetCoordinate(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
for index, row in pixels.iterrows():
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (index, row['x'], row['y']))
ofile.write("        default: return CPixelArray::Coordinate();\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("DomeMappings::Mappings::Mappings() :\n")
ofile.write("    CPixelArrayLegs::Config()\n")
ofile.write("{\n")
ofile.write("    m_num_legs = %d;\n" % (len(df)))
ofile.write("    m_physical_size = c_num_physical_pixels;\n\n")
ofile.write("    m_logical_size  = c_num_logical_pixels;\n\n")
for index, row in df.iterrows():
    ofile.write("    m_leg_offset[%d] = %d;\n" % (index, row['start_index']))
    ofile.write("    m_leg_size[%d] = %d;\n" % (index, row['end_index'] + 1 - row['start_index']))
ofile.write("}\n\n")

pixels = pixels.reset_index().set_index('raw_index')

ofile.write("size_t DomeMappings::ShapeStartIndex(size_t shape_index)\n")
ofile.write("{\n")
ofile.write("    switch(shape_index)\n")
ofile.write("    {\n")
for index, row in df.groupby('shape_index').first().iterrows():
    ofile.write("        case %d: return %d;\n" % (index, pixels.loc[int(row['start_index'])]['logical_index']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

df = df.reset_index().set_index('shape_index')

ofile.write("size_t DomeMappings::ShapeEndIndex(size_t shape_index)\n")
ofile.write("{\n")
ofile.write("    switch(shape_index)\n")
ofile.write("    {\n")
for index, row in df.groupby('shape_index').last().iterrows():
    ofile.write("        case %d: return %d;\n" % (index, pixels.loc[int(row['end_index'])]['logical_index']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("size_t DomeMappings::ShapeStartLeg(size_t shape_index)\n")
ofile.write("{\n")
ofile.write("    switch(shape_index)\n")
ofile.write("    {\n")
for index, row in df.groupby('shape_index').first().iterrows():
    ofile.write("        case %d: return %d;\n" % (index, row['index']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("size_t DomeMappings::ShapeEndLeg(size_t shape_index)\n")
ofile.write("{\n")
ofile.write("    switch(shape_index)\n")
ofile.write("    {\n")
for index, row in df.groupby('shape_index').last().iterrows():
    ofile.write("        case %d: return %d;\n" % (index, row['index']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("#endif // GEOM_DOME")
