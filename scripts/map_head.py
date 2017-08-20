#!/usr/bin/python

import sys
import pandas as pd

mappings = pd.read_csv(sys.argv[1])
num_strands = max(mappings['strand_index'] + 1)
physical_strand_length = mappings[mappings['strand_index'] == 1].iloc[0]['start_index']
num_shapes = len(mappings)

ofile = open(sys.argv[2], 'w')

ofile.write("#ifdef GEOM_HEAD\n\n")

ofile.write("// Auto-Generated file, do not edit manually\n\n")

ofile.write("#include \"HeadMappings.h\"\n\n")

locations = {}
led_index = 0
for index, row in mappings.iterrows():
    for i in range(row['length']):
        locations[row['start_index'] + i] = led_index
        led_index += 1

ofile.write("HeadMappings::Mappings::Mappings() :\n")
ofile.write("    CPixelArrayLegs::Config()\n")
ofile.write("{\n")
ofile.write("    static_assert(%d == c_num_physical_pixels, \"Mismatch in c_num_physical_pixels\");\n" % (physical_strand_length * 8))
ofile.write("    static_assert(%d == c_num_logical_pixels, \"Mismatch in c_num_logical_pixels\");\n" % (sum(mappings['length'])))
ofile.write("    m_num_legs      = " + str(num_shapes) + ";\n")
ofile.write("    m_physical_size = " + str(physical_strand_length * 8) + ";\n")
ofile.write("    m_logical_size  = " + str(sum(mappings['length'])) +";\n")
ofile.write("\n")
ofile.write("    // legs\n")
for index, row in mappings.iterrows():
    ofile.write("    m_leg_offset[%d] = %d;\n" % (row['shape_index'], locations[row['start_index']]))
    ofile.write("    m_leg_size[%d]   = %d;\n" % (row['shape_index'], row['length']))
ofile.write("}\n\n")

ofile.write("size_t HeadMappings::Mappings::GetLocation(size_t index)\n")
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

ofile.write("CPixelArray::Coordinate HeadMappings::Mappings::GetCoordinate(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")

led_index = 0

# mouth left
ofile.write("       // mouth left\n")
length = sum(mappings[mappings['strand_index'] == 0]['length'])
for i in range(length):
    x = -0.75
    y = 0.75 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

# mouth right
ofile.write("       // mouth right\n")
length = sum(mappings[mappings['strand_index'] == 1]['length'])
for i in range(length):
    x = 0.75
    y = 0.75 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

# nose left
ofile.write("       // nose left\n")
loc = mappings[mappings['strand_index'] == 2]
num_shapes = len(loc)
for index, row in loc.reset_index().iterrows():
    length = row['length']
    for i in range(length):
        x = -0.41 + (0.20 * float(i) / length)
        y = 0.75 - 0.75 * float(index) / num_shapes
        ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
        led_index += 1

# nose right
ofile.write("       // nose right\n")
loc = mappings[mappings['strand_index'] == 3]
num_shapes = len(loc)
for index, row in loc.reset_index().iterrows():
    length = row['length']
    for i in range(length):
        x = 0.39 - (0.20 * float(i) / length)
        y = 0.75 - 0.75 * float(index) / num_shapes
        ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
        led_index += 1

# nose top
ofile.write("       // nose top\n")
loc = mappings[mappings['strand_index'] == 4]
num_shapes = len(loc)
for index, row in loc.reset_index().iterrows():
    length = row['length']
    for i in range(length):
        x = -0.20 + (0.40 * float(i) / length)
        y = 0.75 - 0.75 * float(index) / num_shapes
        ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
        led_index += 1

# flame left
ofile.write("       // flame left\n")
length = mappings[(mappings['strand_index'] == 5)].iloc[0]['length']
for i in range(length):
    x = -0.30
    y = 0.0 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

# side left
ofile.write("       // side left\n")
length = mappings[(mappings['strand_index'] == 5)].iloc[1]['length']
for i in range(length):
    x = -0.50
    y = 0.0 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1
# side left
ofile.write("       // horn left\n")
length = mappings[(mappings['strand_index'] == 5)].iloc[2]['length']
for i in range(length):
    x = -0.40
    y = 0.0 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

# flame right
ofile.write("       // flame left\n")
length = mappings[(mappings['strand_index'] == 6)].iloc[0]['length']
for i in range(length):
    x = 0.30
    y = 0.0 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

# side right
ofile.write("       // side left\n")
length = mappings[(mappings['strand_index'] == 6)].iloc[1]['length']
for i in range(length):
    x = 0.50
    y = 0.0 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

# horn right
ofile.write("       // horn left\n")
length = mappings[(mappings['strand_index'] == 6)].iloc[2]['length']
for i in range(length):
    x = 0.40
    y = 0.0 - (float(i) / length) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (led_index, x, y))
    led_index += 1

ofile.write("        default: return CPixelArray::Coordinate();\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("bool HeadMappings::Mappings::ApplyGamma(size_t index)\n")
ofile.write("{\n")
ofile.write("    if(index >= 1800 && index < 2100 + 300)\n")
ofile.write("    {\n")
ofile.write("        return false;\n")
ofile.write("    }\n")
ofile.write("    else\n")
ofile.write("    {\n")
ofile.write("        return true;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("size_t HeadMappings::ShapeStartIndex(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
start_index = 0
ofile.write("        case 0: return %d; // mouth left\n" % (start_index))
start_index += sum(mappings[mappings['strand_index'] == 0]['length'])
ofile.write("        case 1: return %d; // mouth right\n" % (start_index))
start_index += sum(mappings[mappings['strand_index'] == 1]['length'])
ofile.write("        case 2: return %d; // nose left\n" % (start_index))
start_index += sum(mappings[(mappings['strand_index'] == 2) & (mappings['length'] < 150)]['length'])
ofile.write("        case 3: return %d; // cheek left\n" % (start_index))
start_index += sum(mappings[(mappings['strand_index'] == 2) & (mappings['length'] >= 150)]['length'])
ofile.write("        case 4: return %d; // nose right\n" % (start_index))
start_index += sum(mappings[(mappings['strand_index'] == 3) & (mappings['length'] < 150)]['length'])
ofile.write("        case 5: return %d; // cheek right\n" % (start_index))
start_index += sum(mappings[(mappings['strand_index'] == 3) & (mappings['length'] >= 150)]['length'])
ofile.write("        case 6: return %d; // nose top\n" % (start_index))
start_index += sum(mappings[mappings['strand_index'] == 4]['length'])
ofile.write("        case 7: return %d; // flame left\n" % (start_index))
start_index += mappings[mappings['strand_index'] == 5].iloc[0]['length']
ofile.write("        case 8: return %d; // eye left\n" % (start_index))
start_index += mappings[mappings['strand_index'] == 5].iloc[1]['length']
ofile.write("        case 9: return %d; // brow left\n" % (start_index))
start_index += mappings[mappings['strand_index'] == 5].iloc[2]['length']
ofile.write("        case 10: return %d; // flame right\n" % (start_index))
start_index += mappings[mappings['strand_index'] == 6].iloc[0]['length']
ofile.write("        case 11: return %d; // eye right\n" % (start_index))
start_index += mappings[mappings['strand_index'] == 6].iloc[1]['length']
ofile.write("        case 12: return %d; // brow right\n" % (start_index))
start_index += mappings[mappings['strand_index'] == 6].iloc[2]['length']
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("size_t HeadMappings::ShapeSize(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
ofile.write("        case 0: return %d; // mouth left\n" % (mappings[mappings['strand_index'] == 0].iloc[0]['length']))
ofile.write("        case 1: return %d; // mouth right\n" % (mappings[mappings['strand_index'] == 1].iloc[0]['length']))
ofile.write("        case 2: return %d; // nose left\n" % (sum(mappings[(mappings['strand_index'] == 2) & (mappings['length'] < 150)]['length'])))
ofile.write("        case 3: return %d; // cheek left\n" % (sum(mappings[(mappings['strand_index'] == 2) & (mappings['length'] >= 150)]['length'])))
ofile.write("        case 4: return %d; // nose right\n" % (sum(mappings[(mappings['strand_index'] == 3) & (mappings['length'] < 150)]['length'])))
ofile.write("        case 5: return %d; // cheek right\n" % (sum(mappings[(mappings['strand_index'] == 3) & (mappings['length'] >= 150)]['length'])))
ofile.write("        case 6: return %d; // nose top\n" % (sum(mappings[mappings['strand_index'] == 4]['length'])))
ofile.write("        case 7: return %d; // flame left\n" % (mappings[mappings['strand_index'] == 5].iloc[0]['length']))
ofile.write("        case 8: return %d; // eye left\n" % (mappings[mappings['strand_index'] == 5].iloc[1]['length']))
ofile.write("        case 9: return %d; // brow left\n" % (mappings[mappings['strand_index'] == 5].iloc[2]['length']))
ofile.write("        case 10: return %d; // flame right\n" % (mappings[mappings['strand_index'] == 6].iloc[0]['length']))
ofile.write("        case 11: return %d; // eye right\n" % (mappings[mappings['strand_index'] == 6].iloc[1]['length']))
ofile.write("        case 12: return %d; // brow right\n" % (mappings[mappings['strand_index'] == 6].iloc[2]['length']))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("size_t HeadMappings::ShapeNumLegs(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
ofile.write("        case 0: return 1; // mouth left\n")
ofile.write("        case 1: return 1; // mouth right\n")
ofile.write("        case 2: return %d; // nose left\n" % (len(mappings[mappings['strand_index'] == 2]) - 1))
ofile.write("        case 3: return 1; // cheek left\n")
ofile.write("        case 4: return %d; // nose right\n" % (len(mappings[mappings['strand_index'] == 3]) - 1))
ofile.write("        case 5: return 1; // cheek righ\n")
ofile.write("        case 6: return %d; // nose top\n" % (len(mappings[mappings['strand_index'] == 4])))
ofile.write("        case 7: return 1; // flame left\n")
ofile.write("        case 8: return 1; // eye left\n")
ofile.write("        case 9: return 1; // brow left\n")
ofile.write("        case 10: return 1; // flame right\n")
ofile.write("        case 11: return 1; // eye right\n")
ofile.write("        case 12: return 1; // brow right\n")
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("#endif // GEOM_HEAD")
