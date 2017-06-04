#include "PixelArray.h"
#include "Logging.h"
#include "Routine.h"
#include "RoutineTest.h"
#include "RoutineGlare.h"
#include "RoutineCrawl.h"
#include "RoutineSticks.h"
#include "RoutineBall.h"
#include "RoutineBalls.h"
#include "RoutineFire.h"

CMemoryPool<CPixelArray::Block, CPixelArray::Block::c_num_blocks> CPixelArray::s_data_pool;
CMemoryPool<CPixelArray, CPixelArray::c_alloc_qty>                CPixelArray::s_obj_pool;

CPixelArray::CPixelArray(const CPixelArray& rhs) :
    m_block(new(s_data_pool.alloc()) Block()),
    m_owner(true),
    m_pixels(m_block->m_pixels),
    m_length(rhs.GetSize()),
    m_locations(m_block->m_locations),
    m_coordinates(m_block->m_coordinates)
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i]   = i;
        m_coordinates[i] = rhs.GetCoordinate(i);
    }
}

CPixelArray::CPixelArray() :
    m_block(new(s_data_pool.alloc()) Block()),
    m_owner(true),
    m_pixels(m_block->m_pixels),
    m_length(GetRawSize()),
    m_locations(m_block->m_locations),
    m_coordinates(m_block->m_coordinates)
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i] = i;
    }
}

CPixelArray::CPixelArray(Config config) :
    m_block(new (s_data_pool.alloc()) Block()),
    m_owner(true),
    m_pixels(m_block->m_pixels)
{
    Init(&config);

    char logstr[256];
    sprintf(logstr, "CPixelArray::CPixelArray: Constructed parent array of length %u", GetSize());
    CLogging::log(logstr);
}

CPixelArray::CPixelArray(CPixelArray* pixels) :
    CPixelArray(pixels, pixels->GetSize(), 0, pixels->NumLegs(), 0)
{
}

CPixelArray::CPixelArray(CPixelArray* pixels, size_t len, size_t offset, size_t num_legs, size_t leg_offset) :
    m_pixels(pixels->GetRaw()),
    m_length(len),
    m_num_legs(num_legs),
    m_locations(pixels->m_locations + offset),
    m_coordinates(pixels->m_coordinates + offset)
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = pixels->m_legs[i + leg_offset];
    }

    char logstr[256];
    sprintf(logstr, "CPixelArray::CPixelArray: Constructed child array of length %u", GetSize());
    CLogging::log(logstr);
}

CPixelArray::~CPixelArray()
{
    ClearRoutines();

    if(m_owner == true)
    {
        s_data_pool.free(m_block);
        s_data_pool.free(m_block);
        for(size_t i=0;i<NumLegs();i++)
        {
            s_obj_pool.free(m_legs[i]);
        }
    }
}

void CPixelArray::Init(Config* config)
{
    m_num_legs = config->m_num_legs;

    if(NumLegs() > c_max_num_legs)
    {
        char logstr[256];
        sprintf(logstr, "CPixelArray::Init: ERROR num_legs = %u exceeds maximum of %u. Exiting",
                NumLegs(), c_max_num_legs);
        CLogging::log(logstr);
        exit(-1);
    }

    if(NumLegs() == 0)
    {
        return;
    }

    size_t length[config->m_num_legs] = {};

    m_length = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        length[i]  = abs((int)config->m_end_index[i] - (int)config->m_start_index[i]) + 1;
        m_length  += length[i];
    }

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        bool forward = config->m_start_index[i] <= config->m_end_index[i];
        m_legs[i]    = new(s_obj_pool.alloc()) CPixelArray(this, length[i], index);

        for(size_t j=0;j<length[i];j++)
        {
            m_locations[index++] = config->m_start_index[i] + (forward ? j : -j);
            m_legs[i]->SetLocation(j, config->m_start_index[i] + (forward ? j : -j));
        }
    }

    MapCoordinates(config);

    char logstr[256];
    sprintf(logstr, "CPolygon::CPolygon: Initialized shape with "
            "%u legs", NumLegs());
    CLogging::log(logstr);
}

void CPixelArray::MapCoordinates(Config* config)
{
    if(config->m_auto_coordinates == true)
    {
        AutoMapCorners(config);
    }

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        const size_t length = m_legs[i]->GetSize();
        Coordinate&  start  = config->m_start_coordinate[i];
        Coordinate&  end    = config->m_end_coordinate[i];
        const float x_step = (end.x - start.x) / length;
        const float y_step = (end.y - start.y) / length;

        for(size_t j=0;j<length;j++)
        {
            Coordinate& this_coord = m_coordinates[index++];
            this_coord.x           = start.x + j * x_step;
            this_coord.y           = start.y + j * y_step;
        }
    }
}

// assume regular polygon, map corners to coordinates
void CPixelArray::AutoMapCorners(Config* config)
{
    const bool   side_at_edge    = NumLegs() == 4 || NumLegs() == 8;
    const float center_distance = side_at_edge ?
                                   0.50 / cos(180 / NumLegs()) :
                                   0.50;

    for(size_t i=0;i<NumLegs();i++)
    {
        Coordinate& start_corner = config->m_start_coordinate[i];
        const float pi           = 3.14159265358979323846;
        start_corner.x           = cos(2 * pi * i / NumLegs()) * config->m_scale + config->m_origin.x;
        start_corner.y           = center_distance * sin(2 * pi * i / NumLegs()) * config->m_scale + config->m_origin.y;

        config->m_end_coordinate[i > 0 ? i - 1 : NumLegs() - 1] = start_corner;
    }
}

CRGB CPixelArray::GetPixel(size_t index)
{
    return m_pixels[m_locations[index]];
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    m_pixels[m_locations[index]] = rgb;
}

void CPixelArray::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

void CPixelArray::Shift(bool forward, size_t amount)
{
    for(size_t it=0;it<amount;it++)
    {   
        CRGB pixel = forward ? GetPixel(GetSize()-1) : GetPixel(0);

        for(size_t i=0;i<GetSize();i++)
        {   
            size_t index = forward ? i : GetSize() - i - 1;
            CRGB buff    = GetPixel(index);
            SetPixel(index, pixel);
            pixel        = buff;
        }   
    }   
}

void CPixelArray::Copy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        SetPixel(index, rgb);
    }   
}

void CPixelArray::SmartCopy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        
        if(rgb == CRGB(CRGB::Black))
        {
            SetPixel(index, rgb);
        }
    }   
}

void CPixelArray::ExitRoutine()
{
    if(m_routine == nullptr)
    {
        return;
    }

    char logstr[256];
    sprintf(logstr, "CPixelArray::ExitRoutine: Exiting routine");
    CLogging::log(logstr);

    delete m_routine;

    m_routine = nullptr;
}

void CPixelArray::ClearRoutines()
{
    ExitRoutine();

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->ExitRoutine();
    }   
}

void CPixelArray::StartRoutineTest()
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineTest: Starting routine");

    m_routine = new CRoutineTest(this);
}

void CPixelArray::StartRoutineSolid(CRGB rgb)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineSolid: Starting routine");

    SetAllPixels(rgb);
}

void CPixelArray::StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineGlare: Starting routine glare");

    m_routine = new CRoutineGlare(this, base_color, q, forward, period_sec);
}

void CPixelArray::StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineCrawl: Starting routine Crawl");

    m_routine = new CRoutineCrawl(this, base_color, width, start_offset, forward, period_sec);
}

void CPixelArray::StartRoutineSticks(size_t num_sticks)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineSticks: Starting routine Sticks");

    m_routine = new CRoutineSticks(this, num_sticks);
}

void CPixelArray::StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineGlareLegs: Starting routine GlareLegs");

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->StartRoutineGlare(base_color, q, forward, period_sec);
    }
}

void CPixelArray::StartRoutineBall(size_t q, uint32_t period_sec)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineBall: Starting routine Ball");

    m_routine = new CRoutineBall(this, q, period_sec);
}

void CPixelArray::StartRoutineBalls(size_t num_balls)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineBalls: Starting routine Balls");

    m_routine = new CRoutineBalls(this, num_balls);
}

void CPixelArray::StartRoutineFire()
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineFire: Starting routine Fire");

    m_routine = new CRoutineFire(this);
}

void CPixelArray::Continue()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->Continue();
    }

    if(m_routine == nullptr)
    {
        return;
    }

    m_routine->Continue();
}

CRGB* CPixelArray::GetRaw(size_t index)
{
    return &m_pixels[index];
}
