#!/usr/bin/python

import sys

NUM_STRANDS         = 8
STRAND_LENGTH       = 300

ofile = open(sys.argv[1], 'w')

ofile.write("#ifdef GEOM_HEAD\n\n")

ofile.write("// Auto-Generated file, do not edit manually\n\n")

ofile.write("#include \"HeadMappings.h\"\n\n")

ofile.write("HeadMappings::Mappings::Mappings() :\n\
    CPixelArrayLegs::Config()\n\
{\n\
    m_num_legs      = 8;\n\
    m_physical_size = c_num_physical_pixels;\n\
    m_logical_size  = c_num_logical_pixels;\n\
\n\
    // mouth left\n\
    m_leg_offset[0] = 0;\n\
    m_leg_size[0]   = 300;\n\
\n\
    // mouth right\n\
    m_leg_offset[1] = 300;\n\
    m_leg_size[1]   = 300;\n\
\n\
    // nose left\n\
    m_leg_offset[2] = 600;\n\
    m_leg_size[2]   = 300;\n\
\n\
    // nose right\n\
    m_leg_offset[3] = 900;\n\
    m_leg_size[3]   = 300;\n\
\n\
    // side left\n\
    m_leg_offset[4] = 1200;\n\
    m_leg_size[4]   = 300;\n\
\n\
    // side right\n\
    m_leg_offset[5] = 1500;\n\
    m_leg_size[5]   = 300;\n\
\n\
    // flame left\n\
    m_leg_offset[6] = 1800;\n\
    m_leg_size[6]   = 300;\n\
\n\
    // flame right\n\
    m_leg_offset[7] = 2100;\n\
    m_leg_size[7]   = 300;\n\
\n\
}\n\n");

ofile.write("CPixelArray::Coordinate HeadMappings::Mappings::GetCoordinate(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")

# mouth left
ofile.write("       // mouth left\n")
for i in range(300):
    x = -0.20
    y = 0.75 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (0 + i, x, y))

# mouth right
ofile.write("       // mouth right\n")
for i in range(300):
    x = 0.20
    y = 0.75 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (300 + i, x, y))

# nose left
ofile.write("       // nose left\n")
for i in range(300):
    x = -0.10
    y = 0.75 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (600 + i, x, y))

# nose right
ofile.write("       // nose right\n")
for i in range(300):
    x = 0.10
    y = 0.75 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (900 + i, x, y))

# side left
ofile.write("       // side left\n")
for i in range(300):
    x = -0.50
    y = 0.0 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (1200 + i, x, y))

# side right
ofile.write("       // side right\n")
for i in range(300):
    x = 0.50
    y = 0.0 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (1500 + i, x, y))

# flame left
ofile.write("       // flame left\n")
for i in range(300):
    x = -0.30
    y = 0.0 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (1800 + i, x, y))

# flame right
ofile.write("       // flame right\n")
for i in range(300):
    x = 0.30
    y = 0.0 - (float(i) / 300) * 0.75
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (2100 + i, x, y))
ofile.write("        default: return CPixelArray::Coordinate();\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("#endif // GEOM_HEAD")
