#!/usr/bin/python

import sys
import pandas as pd

mappings = pd.read_csv(sys.argv[1])
num_strands = max(mappings['strand_index'] + 1)
physical_strand_length = mappings[mappings['strand_index'] == 1].iloc[0]['start_index']
num_shapes = len(mappings)
shapes_per_leg = len(mappings[mappings['strand_index'] < 4]) / 4
shapes_per_neck = len(mappings[mappings['strand_index'] > 4])

ofile = open(sys.argv[2], 'w')

ofile.write("#ifdef GEOM_LEGS_NECK\n\n")

ofile.write("// Auto-Generated file, do not edit manually\n\n")

ofile.write("#include \"LegsAndNeckMappings.h\"\n\n")

ofile.write("LegsAndNeckMappings::Mappings::Mappings() :\n")
ofile.write("    CPixelArrayLegs::Config()\n")
ofile.write("{\n")
ofile.write("    static_assert(%d == c_num_physical_pixels, \"Mismatch in c_num_physical_pixels\");\n" % (physical_strand_length * num_strands))
ofile.write("    static_assert(%d == c_num_logical_pixels, \"Mismatch in c_num_logical_pixels\");\n" % (sum(mappings['length'])))
ofile.write("    m_num_legs      = " + str(num_shapes) + ";\n")
ofile.write("    m_physical_size = " + str(physical_strand_length * num_strands) + ";\n")
ofile.write("    m_logical_size  = " + str(sum(mappings['length'])) +";\n")
ofile.write("\n")
ofile.write("    // legs\n")
for index, row in mappings.iterrows():
    ofile.write("    m_leg_offset[%d] = %d;\n" % (row['shape_index'], row['start_index']))
    ofile.write("    m_leg_size[%d]   = %d;\n" % (row['shape_index'], row['length']))
ofile.write("}\n\n")

ofile.write("size_t LegsAndNeckMappings::Mappings::GetLocation(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
led_index = 0
for index, row in mappings.iterrows():
    for i in range(row['length']):
        location = row['start_index'] + i
        ofile.write("        case %d: return %d;\n" % (led_index, location))
        led_index += 1
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("CPixelArray::Coordinate LegsAndNeckMappings::Mappings::GetCoordinate(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
led_index = 0
for index, row in mappings.iterrows():
    if row['strand_index'] < 4:
        for i in range(row['length']):
            leg_index = row['shape_index']
            index_in_leg = i / float(row['length'])
            overall_leg_index = row['strand_index']
            x = 0.50 + 0.10 * (leg_index % shapes_per_leg)
            y = 0.75 - index_in_leg * 0.50
            if overall_leg_index < 2:
                x *= -1.0
            if overall_leg_index % 2 != 0:
                y *= -1.0
            ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
            led_index += 1
    else:
        for i in range(row['length']):
            neck_index = row['shape_index'] - 4 * shapes_per_leg
            index_in_neck = i / float(row['length'])
            x = -0.20 + index_in_neck * 0.40
            y = 0.10 * neck_index
            ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
            led_index += 1
ofile.write("        default: return CPixelArray::Coordinate();\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("#endif // GEOM_LEGS_NECK")
