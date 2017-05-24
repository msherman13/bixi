#include "Dome.h"
#include "PixelArray.h"
#include "Routine2dSwipe.h"

CDome::CDome(CPixelArray* pixels)
{
    CPixelArray::Config config;

    // top right double-hex
    config.m_num_legs  = 6;
    config.m_origin    = CPixelArray::Coordinate(0.25, 0.25);
    config.m_scale     = 0.50;
    config.m_start[0]  = 197;
    config.m_end[0]    = 183;
    config.m_start[1]  = 182;
    config.m_end[1]    = 168;
    config.m_start[2]  = 167;
    config.m_end[2]    = 153;
    config.m_start[3]  = 152;
    config.m_end[3]    = 138;
    config.m_start[4]  = 227;
    config.m_end[4]    = 213;
    config.m_start[5]  = 212;
    config.m_end[5]    = 198;
    m_shapes[0] = new CPixelArray(pixels, config);

    config.m_scale     = 0.375;
    config.m_origin    = CPixelArray::Coordinate(0.25, 0.25);
    config.m_start[0]  = 259;
    config.m_end[0]    = 252;
    config.m_start[1]  = 251;
    config.m_end[1]    = 244;
    config.m_start[2]  = 243;
    config.m_end[2]    = 236;
    config.m_start[3]  = 235;
    config.m_end[3]    = 228;
    config.m_start[4]  = 275;
    config.m_end[4]    = 268;
    config.m_start[5]  = 267;
    config.m_end[5]    = 260;
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
    m_shapes[3] = new CPixelArray(pixels, config);
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
    m_routine = new CRoutine2dSwipe(c_num_shapes, &m_shapes[0], 15, 5);
}
