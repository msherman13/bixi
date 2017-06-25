#!/usr/bin/python

import sys

NUM_STRANDS         = 6
NUM_SHAPES_PER_LEG  = 4
NUM_LEGS            = 4
NUM_LEG_SHAPES      = NUM_SHAPES_PER_LEG * NUM_LEGS
NUM_SHAPES_PER_NECK = 8
NUM_NECKS           = 1
NUM_NECK_SHAPES     = NUM_SHAPES_PER_NECK * NUM_NECKS
LEG_SHAPE_PHYS_LEN  = 150
LEG_SHAPE_LOG_LEN   = 123
NECK_SHAPE_PHYS_LEN = 180
NECK_SHAPE_LOG_LEN  = 150
STRAND_LENGTH       = NUM_NECK_SHAPES * NECK_SHAPE_PHYS_LEN / 2
LOGICAL_LEG_LEN     = NUM_LEG_SHAPES * LEG_SHAPE_LOG_LEN
PHYSICAL_LEG_LEN    = NUM_LEG_SHAPES * LEG_SHAPE_PHYS_LEN
LOGICAL_NECK_LEN    = NUM_NECK_SHAPES * NECK_SHAPE_LOG_LEN
PHYSICAL_NECK_LEN   = NUM_NECK_SHAPES * NECK_SHAPE_PHYS_LEN

ofile = open(sys.argv[1], 'w')

ofile.write("#ifdef GEOM_LEGS_NECK\n\n")

ofile.write("// Auto-Generated file, do not edit manually\n\n")

ofile.write("#include \"LegsAndNeckMappings.h\"\n\n")

ofile.write("LegsAndNeckMappings::Mappings::Mappings() :\n\
    CPixelArrayLegs::Config()\n\
{\n\
    m_num_legs      = c_num_shapes;\n\
    m_physical_size = c_num_physical_pixels;\n\
    m_logical_size  = c_num_logical_pixels;\n\
\n\
    // legs\n\
    for(size_t i=0;i<c_num_legs * c_shapes_per_leg;i++)\n\
    {\n\
        m_leg_offset[i] = i * c_leg_shape_log_len;\n\
        m_leg_size[i]   = c_leg_shape_log_len;\n\
    }\n\
\n\
    // neck\n\
    for(size_t i=0;i<c_num_necks * c_shapes_per_neck;i++)\n\
    {\n\
        m_leg_offset[c_num_legs * c_shapes_per_leg + i] =\n\
            c_num_legs * c_shapes_per_leg * c_leg_shape_log_len + i * c_neck_shape_log_len;\n\
        m_leg_size[c_num_legs * c_shapes_per_leg + i]   = c_neck_shape_log_len;\n\
    }\n\
}\n\n");

ofile.write("size_t LegsAndNeckMappings::Mappings::GetLocation(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
for i in range(LOGICAL_LEG_LEN):
    leg_index = int(i / LEG_SHAPE_LOG_LEN)
    overall_leg_index = int(leg_index / NUM_SHAPES_PER_LEG)
    leg_index_in_strand = leg_index - overall_leg_index * NUM_SHAPES_PER_LEG
    offset    = overall_leg_index * STRAND_LENGTH + leg_index_in_strand * LEG_SHAPE_PHYS_LEN + (i - (leg_index * LEG_SHAPE_LOG_LEN))
    if i % LEG_SHAPE_LOG_LEN == 0:
        ofile.write("        // Leg%d, Shape %d\n" % (overall_leg_index, (leg_index % NUM_SHAPES_PER_LEG)))
    ofile.write("        case %d: return %d;\n" % (i, offset))
for i in range(LOGICAL_NECK_LEN):
    neck_index = int(i / NECK_SHAPE_LOG_LEN)
    strand_index = int(neck_index / (NUM_SHAPES_PER_NECK / 2))
    neck_index_in_strand = neck_index - strand_index * (NUM_SHAPES_PER_NECK / 2)
    offset    = NUM_LEGS * STRAND_LENGTH + strand_index * STRAND_LENGTH + neck_index_in_strand * NECK_SHAPE_PHYS_LEN + (i - (neck_index * NECK_SHAPE_LOG_LEN))
    if i % NECK_SHAPE_LOG_LEN == 0:
        ofile.write("        // Neck%d, Shape %d\n" % (strand_index, neck_index % (NUM_SHAPES_PER_NECK / 2)))
    ofile.write("        case %d: return %d;\n" % (i + LOGICAL_LEG_LEN, offset))
ofile.write("        default: return 0;\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("CPixelArray::Coordinate LegsAndNeckMappings::Mappings::GetCoordinate(size_t index)\n")
ofile.write("{\n")
ofile.write("    switch(index)\n")
ofile.write("    {\n")
for i in range(LOGICAL_LEG_LEN):
    leg_index = int(i / LEG_SHAPE_LOG_LEN)
    index_in_leg = float(i - (leg_index * LEG_SHAPE_LOG_LEN)) / LEG_SHAPE_LOG_LEN
    overall_leg_index = leg_index / NUM_SHAPES_PER_LEG
    x = 0.50 + 0.10 * (leg_index % NUM_SHAPES_PER_LEG)
    y = 0.75 - index_in_leg * 0.50
    if overall_leg_index < NUM_LEGS / 2:
        x *= -1.0
    if overall_leg_index % 2 != 0:
        y *= -1.0
    if i % LEG_SHAPE_LOG_LEN == 0:
        ofile.write("        // Leg%d, Shape %d\n" % (overall_leg_index, (leg_index % NUM_SHAPES_PER_LEG)))
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (i, x, y))
for i in range(LOGICAL_NECK_LEN):
    neck_index = int(i / NECK_SHAPE_LOG_LEN)
    index_in_neck = float(i - (neck_index * NECK_SHAPE_LOG_LEN)) / NECK_SHAPE_LOG_LEN
    x = -0.20 + index_in_neck * 0.40
    y = 0.10 * neck_index
    if i % NECK_SHAPE_LOG_LEN == 0:
        ofile.write("        // Neck%d, Shape %d\n" % (strand_index, neck_index % (NUM_SHAPES_PER_NECK / 2)))
    ofile.write("        case %d: return CPixelArray::Coordinate(%f, %f);\n" % (i + LOGICAL_LEG_LEN, x, y))
ofile.write("        default: return CPixelArray::Coordinate();\n")
ofile.write("    }\n")
ofile.write("}\n\n")

ofile.write("#endif // GEOM_LEGS_NECK")
