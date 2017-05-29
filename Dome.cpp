#include "Dome.h"
#include "RoutineSwipe.h"
#include "RoutineFire.h"

CDome::CDome(CPixelArray* pixels) :
    CPixelArray(pixels)
{
    CPixelArray::Config config;
    config.m_num_legs  = 6;

    // top right double-hex
    config.m_origin    = CPixelArray::Coordinate(0.25, 0.25);
    config.m_scale     = 0.50;
    config.m_start[0]  = 201;
    config.m_end[0]    = 187;
    config.m_start[1]  = 186;
    config.m_end[1]    = 172;
    config.m_start[2]  = 171;
    config.m_end[2]    = 157;
    config.m_start[3]  = 156;
    config.m_end[3]    = 142;
    config.m_start[4]  = 231;
    config.m_end[4]    = 217;
    config.m_start[5]  = 216;
    config.m_end[5]    = 202;
    config.m_corner_coordinates[0] = CPixelArray::Coordinate( 0.3750,  0.1875);
    config.m_corner_coordinates[1] = CPixelArray::Coordinate( 0.5000,  0.0625);
    config.m_corner_coordinates[2] = CPixelArray::Coordinate( 0.3750, -0.0625);
    config.m_corner_coordinates[3] = CPixelArray::Coordinate( 0.1875, -0.0625);
    config.m_corner_coordinates[4] = CPixelArray::Coordinate( 0.0625,  0.0625);
    config.m_corner_coordinates[5] = CPixelArray::Coordinate( 0.1875,  0.1875);
    m_shapes[0] = new CPixelArray(pixels, config);

    config.m_scale     = 0.375;
    config.m_origin    = CPixelArray::Coordinate(0.25, 0.25);
    config.m_start[0]  = 263;
    config.m_end[0]    = 256;
    config.m_start[1]  = 255;
    config.m_end[1]    = 248;
    config.m_start[2]  = 247;
    config.m_end[2]    = 240;
    config.m_start[3]  = 239;
    config.m_end[3]    = 232;
    config.m_start[4]  = 279;
    config.m_end[4]    = 272;
    config.m_start[5]  = 271;
    config.m_end[5]    = 264;
    config.m_corner_coordinates[0] = CPixelArray::Coordinate( 0.34375, 0.1250);
    config.m_corner_coordinates[1] = CPixelArray::Coordinate( 0.40625, 0.0625);
    config.m_corner_coordinates[2] = CPixelArray::Coordinate( 0.34375, 0.0000);
    config.m_corner_coordinates[3] = CPixelArray::Coordinate( 0.21875, 0.0000);
    config.m_corner_coordinates[4] = CPixelArray::Coordinate( 0.15625, 0.0625);
    config.m_corner_coordinates[5] = CPixelArray::Coordinate( 0.21875, 0.1250);
    m_shapes[1] = new CPixelArray(pixels, config);

    // bottom left double-hex
    config.m_num_legs  = 6;
    config.m_origin    = CPixelArray::Coordinate(-0.25, -0.25);
    config.m_scale     = 0.50;
    config.m_start[0]  = 89;
    config.m_end[0]    = 75;
    config.m_start[1]  = 74;
    config.m_end[1]    = 60;
    config.m_start[2]  = 59;
    config.m_end[2]    = 45;
    config.m_start[3]  = 44;
    config.m_end[3]    = 30;
    config.m_start[4]  = 29;
    config.m_end[4]    = 15;
    config.m_start[5]  = 14;
    config.m_end[5]    = 0;
    config.m_corner_coordinates[0] = CPixelArray::Coordinate( -0.1875,  0.0625);
    config.m_corner_coordinates[1] = CPixelArray::Coordinate( -0.0625, -0.0625);
    config.m_corner_coordinates[2] = CPixelArray::Coordinate( -0.1875, -0.1875);
    config.m_corner_coordinates[3] = CPixelArray::Coordinate( -0.3750, -0.1875);
    config.m_corner_coordinates[4] = CPixelArray::Coordinate( -0.5000, -0.0625);
    config.m_corner_coordinates[5] = CPixelArray::Coordinate( -0.3750,  0.0625);
    m_shapes[2] = new CPixelArray(pixels, config);

    config.m_scale     = 0.375;
    config.m_origin    = CPixelArray::Coordinate(-0.25, -0.25);
    config.m_start[0]  = 137;
    config.m_end[0]    = 130;
    config.m_start[1]  = 129;
    config.m_end[1]    = 122;
    config.m_start[2]  = 121;
    config.m_end[2]    = 114;
    config.m_start[3]  = 113;
    config.m_end[3]    = 106;
    config.m_start[4]  = 105;
    config.m_end[4]    = 98;
    config.m_start[5]  = 97;
    config.m_end[5]    = 90;
    config.m_corner_coordinates[0] = CPixelArray::Coordinate( -0.21875, -0.0000);
    config.m_corner_coordinates[1] = CPixelArray::Coordinate( -0.15625, -0.0625);
    config.m_corner_coordinates[2] = CPixelArray::Coordinate( -0.21875, -0.1250);
    config.m_corner_coordinates[3] = CPixelArray::Coordinate( -0.34375, -0.1250);
    config.m_corner_coordinates[4] = CPixelArray::Coordinate( -0.40625, -0.0625);
    config.m_corner_coordinates[5] = CPixelArray::Coordinate( -0.34375, -0.0000);
    m_shapes[3] = new CPixelArray(pixels, config);

    // copy shape coordinates to base
    for(size_t shape=0;shape<c_num_shapes;shape++)
    {
        CPixelArray* pixels = m_shapes[shape];
        for(size_t i=0;i<pixels->GetSize();i++)
        {
            SetCoordinate(pixels->GetLocation(i), pixels->GetCoordinate(i));
        }
    }
}

CDome::~CDome()
{
    for(size_t i=0;i<c_num_shapes;i++)
    {
        delete m_shapes[i];
    }
}

void CDome::ExitRoutine()
{
    if(m_routine == nullptr)
    {
        return;
    }

    delete m_routine;
    m_routine = nullptr;
}

void CDome::Continue()
{
    for(size_t i=0;i<c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    if(m_routine != nullptr)
    {
        m_routine->Continue();
    }
}

void CDome::StartRoutineSwipe()
{
    m_routine = new CRoutineSwipe(c_num_shapes, &m_shapes[0], 15, 10);
}

void CDome::StartRoutineFire()
{
    m_routine = new CRoutineFire(c_num_shapes, &m_shapes[0]);
}
